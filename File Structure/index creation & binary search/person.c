#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "person.h"
//필요한 경우 헤더 파일과 함수를 추가할 수 있음

// 과제 설명서대로 구현하는 방식은 각자 다를 수 있지만 약간의 제약을 둡니다.
// 레코드 파일이 페이지 단위로 저장 관리되기 때문에 사용자 프로그램에서 레코드 파일로부터 데이터를 읽고 쓸 때도
// 페이지 단위를 사용합니다. 따라서 아래의 두 함수가 필요합니다.
// 1. readPage(): 주어진 페이지 번호의 페이지 데이터를 프로그램 상으로 읽어와서 pagebuf에 저장한다
// 2. writePage(): 프로그램 상의 pagebuf의 데이터를 주어진 페이지 번호에 저장한다
// 레코드 파일에서 기존의 레코드를 읽거나 새로운 레코드를 쓰거나 삭제 레코드를 수정할 때나
// 위의 readPage() 함수를 호출하여 pagebuf에 저장한 후, 여기에 필요에 따라서 새로운 레코드를 저장하거나
// 삭제 레코드 관리를 위한 메타데이터를 저장합니다. 그리고 난 후 writePage() 함수를 호출하여 수정된 pagebuf를
// 레코드 파일에 저장합니다. 반드시 페이지 단위로 읽거나 써야 합니다.
//
// 주의: 데이터 페이지로부터 레코드(삭제 레코드 포함)를 읽거나 쓸 때 페이지 단위로 I/O를 처리해야 하지만,
// 헤더 레코드의 메타데이터를 저장하거나 수정하는 경우 페이지 단위로 처리하지 않고 직접 레코드 파일을 접근해서 처리한다.


int		header_page_cnt, header_record_cnt, header_del_page, header_del_record;
int		binary_cnt, is_binary_fail;

typedef struct s_idx_record_
{
	char					id[13];
	int						page_num;
	int						record_num;
}s_idx_record;

typedef struct s_record_header_info__
{
	int						offset;
	int						len;
}s_record_header_info;

//
// 페이지 번호에 해당하는 페이지를 주어진 페이지 버퍼에 읽어서 저장한다. 페이지 버퍼는 반드시 페이지 크기와 일치해야 한다.
//
void readPage(FILE *fp, char *pagebuf, int pagenum)
{
	if (fp == NULL)
		fprintf(stderr, "open error\n");
	else
	{
		fseek(fp, pagenum * PAGE_SIZE + 16, SEEK_SET); // 헤더레코드를 건너뛰고, 페이지를 읽는다.
		fread((void*)pagebuf, PAGE_SIZE, 1, fp);
	}
	return;
}

//
// 페이지 버퍼의 데이터를 주어진 페이지 번호에 해당하는 레코드 파일의 위치에 저장한다.
// 페이지 버퍼는 반드시 페이지 크기와 일치해야 한다.
//
void writePage(FILE *fp, const char *pagebuf, int pagenum)
{
	if (fp == NULL)
		fprintf(stderr, "open error\n");
	else
	{
		fseek(fp, pagenum * PAGE_SIZE + 12, SEEK_SET);
		fwrite(pagebuf, PAGE_SIZE, 1, fp);
	}
	return;
}

//
// 새로운 레코드를 저장할 때 터미널로부터 입력받은 정보를 Person 구조체에 먼저 저장하고, pack() 함수를 사용하여
// 레코드 파일에 저장할 레코드 형태를 recordbuf에 만든다.
//
void pack(char *recordbuf, const Person *p)
{
	sprintf(recordbuf, "%s#%s#%s#%s#%s#%s#", p->id, p->name, p->age, p->addr, p->phone, p->email);
	return;
}

//
// 아래의 unpack() 함수는 recordbuf에 저장되어 있는 레코드를 구조체로 변환할 때 사용한다.
//
void unpack(const char *recordbuf, Person *p) {

    char buffer[6][30] = {0};
    char *ptr;
    char *tmp = (char *) calloc(sizeof(char), strlen(recordbuf));
    strcpy(tmp, recordbuf);

    ptr = strtok(tmp, "#");
    int cnt = 0;
    while (ptr != NULL) {
        strcpy(buffer[cnt++], ptr);
        ptr = strtok(NULL, "#");
    }
    strcpy(p->id, buffer[0]);
    strcpy(p->name, buffer[1]);
    strcpy(p->age, buffer[2]);
    strcpy(p->addr, buffer[3]);
    strcpy(p->phone, buffer[4]);
    strcpy(p->email, buffer[5]);

    free(tmp);


    return;
}

//
// 새로운 레코드를 저장하는 기능을 수행하며, 터미널로부터 입력받은 필드값들을 구조체에 저장한 후 아래 함수를 호출한다.
//
void add(FILE *fp, const Person *p)
{
	return;
}

//
// 주민번호와 일치하는 레코드를 찾아서 삭제하는 기능을 수행한다.
//
void delete(FILE *fp, const char *id)
{
	return;
}


//
// 주어진 레코드 파일(recordfp)을 이용하여 심플 인덱스 파일(idxfp)을 생성한다.
//
void createIndex(FILE *idxfp, FILE *recordfp)
{
	int						idx_header_record_num; // 삭제 리스트는 제외한다.
	char					index_record_buff[21]; // 최종으로 저정할 인덱스 파일
	int						record_cnt_per_page;
	int						record_cnt_all_page = 0;
	char					page_buffer[PAGE_SIZE];

	s_record_header_info	*record_info_arr;
	s_idx_record			*idx_info_arr;
	s_idx_record			tmp;

	idx_info_arr = malloc(sizeof(s_idx_record) * header_record_cnt);

	// page 기준으로 읽어와서 인덱스 파일에 필요한 정보를 구조체 배열에 저장한다.
	for (int i = 0 ; i < header_page_cnt ; ++i)
	{
		memset(page_buffer, 0, PAGE_SIZE);
		readPage(recordfp, page_buffer, i);

		// record의 offset과 len정보를 구조체 배열에 저장한다.
		memcpy(&record_cnt_per_page, page_buffer, sizeof(int));
		record_info_arr = malloc(sizeof(s_record_header_info) * record_cnt_per_page);
		for (int j = 0 ; j < record_cnt_per_page ; j++)
		{
			memcpy(&record_info_arr[j].offset, &page_buffer[4 + j*8], sizeof(int));
			memcpy(&record_info_arr[j].len, &page_buffer[8 + j*8], sizeof(int));
		}

		//레코드의 주민등록번호, 레코드 주소를 구조체 배열에 저장한다.
		for (int j = 0 ; j < record_cnt_per_page ; j++)
		{
			memcpy(&idx_info_arr[record_cnt_all_page].id, &page_buffer[record_info_arr[j].offset + HEADER_AREA_SIZE],13);
			idx_info_arr[record_cnt_all_page].page_num = i;
			idx_info_arr[record_cnt_all_page].record_num = j;
			record_cnt_all_page++;
		}
		free(record_info_arr);
	}

	// 구조체 배열을 주민등록번호 기준으로 버블 정렬
	for (int i = 0 ; i < header_record_cnt - 1; i++)
	{
		for (int j = 0 ; j < header_record_cnt-1-i ; j++)
		{
			if (strcmp(idx_info_arr[j].id, idx_info_arr[j+1].id) > 0)
			{
				tmp = idx_info_arr[j];
				idx_info_arr[j] = idx_info_arr[j+1];
				idx_info_arr[j+1] = tmp;
			}
		}
	}

	// 정렬한 구조체 배열 내용을 인덱스 파일에 쓰기
	for (int j = 0 ; j < header_record_cnt ; j++)
	{
		if (idx_info_arr[j].id[0] == '*') // 삭제레코드는 저장하지 않는다.
			continue;
		memset(index_record_buff, 0, 21);
		memcpy(index_record_buff, &(idx_info_arr[j].id), 13);
		memcpy(&index_record_buff[13], &(idx_info_arr[j].page_num), 4);
		memcpy(&index_record_buff[17], &(idx_info_arr[j].record_num), 4);
		fwrite(index_record_buff, 21, 1, idxfp);
	}
	free(idx_info_arr);
	return;

}

//
// 주어진 심플 인덱스 파일(idxfp)을 이용하여 주민번호 키값과 일치하는 레코드의 주소, 즉 페이지 번호와 레코드 번호를 찾는다.
// 이때, 반드시 이진 검색 알고리즘을 사용하여야 한다.
//
void binarysearch(FILE *idxfp, const char *id, int *pageNum, int *recordNum)
{

	int		low = 0;
	int 	high, guess, cmp_value;
	char	id_buff[13];

	fseek(idxfp, 0, SEEK_END);
	high = ftell(idxfp)/21 - 1;
	rewind(idxfp);

	while (low <= high)
	{
		memset(id_buff, 0, 13);
		guess = (int)((low+high)/2);

		fseek(idxfp, guess * 21 ,SEEK_SET);
		fread(id_buff, 13, 1, idxfp);

		cmp_value = strncmp(id_buff, id, 13);

		if (cmp_value > 0) // guess is low
		{
			binary_cnt++;
			high = guess - 1;
		}
		else if (cmp_value < 0) // guess is high
		{
			binary_cnt++;
			low = guess + 1;
		}
		else // 찾을경우
		{
			memset(pageNum, 0, 4);
			memset(recordNum, 0, 4);
			fread(pageNum, 4, 1, idxfp);
			fread(recordNum, 4, 1, idxfp);
			is_binary_fail = 0;
			//printf("found!\npagenum : %d\trecordnum:%d\n", *pageNum, *recordNum);
			return;
		}
	}
	is_binary_fail = 1;
	return;
}


int main(int argc, char *argv[])
{
	FILE *fp;  // 레코드 파일의 파일 포인터
	FILE *idx_fp;

	char	*data_file_name, *idx_file_name;
	char	key_value[13];

	int		searching_page_num, searching_record_num;
	Person	p;
	char	page_buff[PAGE_SIZE];
	char	*record_buff;
	int		searching_offset, searching_len;


	data_file_name = (char*)calloc(sizeof(char), strlen(argv[2]));
	idx_file_name = (char*)calloc(sizeof(char), strlen(argv[3]));
	strcpy(data_file_name, argv[2]);
	strcpy(idx_file_name, argv[3]);

	// header record 읽어오기
	if (!(fp = fopen(data_file_name, "r")))
		fprintf(stderr, "file open err\n");

	fread(&header_page_cnt, 1, sizeof(int), fp);
	fread(&header_record_cnt, 1, sizeof(int), fp);
	fread(&header_del_page, 1, sizeof(int), fp);
	fread(&header_del_record, 1, sizeof(int), fp);

	rewind(fp);

	if (strcmp(argv[1], "i") == 0) // 옵션 i
	{
		idx_fp = fopen(idx_file_name, "w");
		createIndex(idx_fp, fp);
	}
	else if (strcmp(argv[1], "b") == 0) // 옵션 b
	{
		idx_fp = fopen(idx_file_name, "r");

		// key_value 읽어오기
		for (int i = 0 ; i < 13 ; i++)
			key_value[i] = argv[4][i];

		// 인덱스파일에 이진탐색 실행
		binarysearch(idx_fp, key_value, &searching_page_num, &searching_record_num);

		if (is_binary_fail == 1)
		{
			printf("#reads:%d\n", binary_cnt+1);
			printf("no person\n");
		}
		else
		{
			readPage(fp, page_buff, searching_page_num);

			// 파일에서의 해당 레코드 위치/길이 찾기
			memcpy(&searching_offset, &page_buff[4 + searching_record_num*8], 4);
			memcpy(&searching_len, &page_buff[8 + searching_record_num*8], 4);
			rewind(fp);



			// 해당 레코드 읽어오기
			record_buff = malloc(sizeof(char) * searching_len);
			memcpy(record_buff, &page_buff[HEADER_AREA_SIZE+searching_offset], searching_len);

			unpack(record_buff, &p);

			printf("#reads:%d\n", binary_cnt+1);
			printf("id=%s\n", p.id);
			printf("name=%s\n", p.name);
			printf("age=%s\n", p.age);
			printf("addr=%s\n", p.addr);
			printf("phone=%s\n", p.phone);
			printf("email=%s\n", p.email);

		}
	}
	else
	{
		fprintf(stderr, "selection error!\n");
	}
	fclose(fp);
	fclose(idx_fp);

	return 0;
}
