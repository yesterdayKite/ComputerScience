// 주의사항
// 1. blockmap.h에 정의되어 있는 상수 변수를 우선적으로 사용해야 함
// 2. blockmap.h에 정의되어 있지 않을 경우 본인이 이 파일에서 만들어서 사용하면 됨
// 3. 필요한 data structure가 필요하면 이 파일에서 정의해서 쓰기 바람(blockmap.h에 추가하면 안됨)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include "blockmap.h"
// 필요한 경우 헤더 파일을 추가하시오.

int				table[BLOCKS_PER_DEVICE] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
int				free_block_idx = BLOCKS_PER_DEVICE - 1;
int				mapping_alloc_idx = 0;

int 	dd_read(int ppn, char *pagebuf);
int	 	dd_write(int ppn, char *pagebuf);
int 	dd_erase(int pbn);
void 	ftl_open();
void	ftl_write(int lsn, char *sectorbuf);
void 	ftl_read(int lsn, char *sectorbuf);
void 	ftl_print();

//
// flash memory를 처음 사용할 때 필요한 초기화 작업, 예를 들면 address mapping table에 대한
// 초기화 등의 작업을 수행한다. 따라서, 첫 번째 ftl_write() 또는 ftl_read()가 호출되기 전에
// file system에 의해 반드시 먼저 호출이 되어야 한다.
//
void ftl_open()
{
	int			is_table_empty = TRUE;
	int			lbn;
	int			psn;
	char		*page_buff = calloc(PAGE_SIZE, sizeof(char));


	//address mapping table을 세팅한다
	for (int i = 0 ; i < BLOCKS_PER_DEVICE ; i++) // 모든 블락의 첫번째 페이지를 읽는다.
	{
		dd_read(i * BLOCK_SIZE, page_buff);

		if (page_buff[512] != '\0') // spare area가 비어있지 않을때, lbn이 있다.
		{
			memcpy(&lbn, &page_buff[512], 4); // lbn 스캔
			table[lbn] = i; // pbn 입력
			for (int i = 0 ; i < PAGE_SIZE ; i++) // 버퍼 비우기
				page_buff[i] = '\0';
		}
	}

	free(page_buff);

	return;
}


//
// 이 함수를 호출하는 쪽(file system)에서 이미 sectorbuf가 가리키는 곳에 512B의 메모리가 할당되어 있어야 함
// (즉, 이 함수에서 메모리를 할당 받으면 안됨)
//
void ftl_read(int lsn, char *sectorbuf)
{
	int			lbn;
	int			offset;
	int			ppn;
	char		*page_buff = calloc(PAGE_SIZE, sizeof(char));

	lbn = lsn / PAGES_PER_BLOCK;
	offset = lsn % PAGES_PER_BLOCK;
	ppn = (table[lbn] * PAGES_PER_BLOCK) + offset;

	dd_read(ppn, page_buff);
	strncpy(sectorbuf, page_buff, SECTOR_SIZE);

	free(page_buff);

	return;

}


//
// 이 함수를 호출하는 쪽(file system)에서 이미 sectorbuf가 가리키는 곳에 512B의 메모리가 할당되어 있어야 함
// (즉, 이 함수에서 메모리를 할당 받으면 안됨)
//
void ftl_write(int lsn, char *sectorbuf)
{
	char			*page_buff = calloc(PAGE_SIZE, sizeof(char));
	char			*check_buff = calloc(PAGE_SIZE, sizeof(char));
	char			swap_buff[PAGES_PER_BLOCK][PAGE_SIZE];

	int				lbn;
	int				offset;
	int				ppn;


	lbn = lsn / PAGES_PER_BLOCK;
	offset =  lsn % PAGES_PER_BLOCK;
	ppn = (table[lbn] * PAGES_PER_BLOCK) + offset;

	strncpy(page_buff, sectorbuf, SECTOR_SIZE);
	memcpy(&page_buff[512], &lbn, 4); // spare 의 앞 4바이트에 lbn  저장
	memcpy(&page_buff[516], &lsn, 4); // 다음 4바이트에 lsn 저장


	if (table[lbn] == -1 ) // pbn이 할당되어있지 않은 상태
	{
		table[lbn] = mapping_alloc_idx++;
		dd_write(ppn, page_buff);
	}
	else // pbn이 할당되어있는 상태임.
	{
		dd_read(ppn, check_buff);

		if (check_buff[SECTOR_SIZE] == '\0')  // 처음 쓰는 데이터일때
			dd_write(ppn, page_buff);
		else // 업데이트 필요할 때
		{
			// 페이지 단위로 읽어와서 swap_buff에 저장한다.
			for ( int i = 0 ; i < PAGES_PER_BLOCK ; ++i)
			{
				if (i == offset)		continue;
				dd_read(ppn + i - offset, swap_buff[i]);
			}

			// 기존 block을 삭제하고
			dd_erase(table[lbn]);

			// free block 을 업데이트한다.
			table[lbn] = free_block_idx;
			free_block_idx = lbn;

			// 업데이트 된 정보를 기록한다.
			ppn = (table[lbn] * PAGES_PER_BLOCK) + offset;

			for (int i = 0 ; i < PAGES_PER_BLOCK ; ++i)
			{
				if (i == offset)		continue;
				dd_write(ppn - offset + i, swap_buff[i]);
			}
			dd_write(ppn, page_buff);
		}
	}

	free(page_buff);
	free(check_buff);

	return;
}

void ftl_print()
{
	printf("lbn pbn\n");
	for(int i = 0 ; i < BLOCKS_PER_DEVICE ; ++i)
		printf("%2d   %2d\n", i, table[i]);
	printf("free block's pbn = %d\n", free_block_idx); // 업데이트된 freeblock num이 출력된다.
	return;
}
