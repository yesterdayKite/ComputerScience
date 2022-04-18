# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include "person.h"

char		 *file_name;
int			 cnt_entire_record;
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

//
// 페이지 번호에 해당하는 페이지를 주어진 페이지 버퍼에 읽어서 저장한다. 페이지 버퍼는 반드시 페이지 크기와 일치해야 한다.
//
void readPage(FILE *fp, char *pagebuf, int pagenum)
{
	if (fp == NULL) 		printf("error");
	else
	{
		fseek(fp, pagenum * PAGE_SIZE, SEEK_SET);
		fread((void *)pagebuf, PAGE_SIZE, 1, fp);
	}
	return;
}

//
// 페이지 버퍼의 데이터를 주어진 페이지 번호에 해당하는 레코드 파일의 위치에 저장한다.
// 페이지 버퍼는 반드시 페이지 크기와 일치해야 한다.
//
void writePage(FILE *fp, const char *pagebuf, int pagenum)
{
	if (fp == NULL) 		printf("error");
	else
	{
		fseek(fp, pagenum * PAGE_SIZE, SEEK_SET);
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
void unpack(const char *recordbuf, Person *p)
{
	char *del_ptr;
	char recordbuf_copy[300] = {0};
	memcpy(recordbuf_copy, recordbuf, strlen(recordbuf));

	del_ptr = strtok(recordbuf_copy, "#");
	sprintf(p->id, "%s", del_ptr);

	del_ptr = strtok(NULL, "#");
	sprintf(p->name, "%s", del_ptr);

	del_ptr = strtok(NULL, "#");
	sprintf(p->age, "%s", del_ptr);

	del_ptr = strtok(NULL, "#");
	sprintf(p->addr, "%s", del_ptr);

	del_ptr = strtok(NULL, "#");
	sprintf(p->phone, "%s", del_ptr);

	del_ptr = strtok(NULL, "#");
	sprintf(p->email, "%s", del_ptr);

	return;
}

//
// 새로운 레코드를 저장하는 기능을 수행하며, 터미널로부터 입력받은 필드값들을 구조체에 저장한 후 아래 함수를 호출한다.
//
void add(FILE *fp, const Person *p)
{
	int			update;
	int			del_page = -1;
	int			del_record = -1;
	int			insert_pageNum = -1;
	int			insert_record_num = -1;
	int			cnt_entire_page_num = 1;

	char		pagebuf[PAGE_SIZE];
	char		headerBuffer[PAGE_SIZE];
	char		recordbuf[MAX_RECORD_SIZE];
	char		remainingData[PAGE_SIZE];

	memset(headerBuffer, '\0', PAGE_SIZE);

	readPage(fp, headerBuffer, 0); // 헤더를 읽어온다.
	rewind(fp);

    cnt_entire_page_num = headerBuffer[0];
    cnt_entire_record = headerBuffer[4];
    del_page = headerBuffer[8];
    del_record = headerBuffer[12];

    if (del_page == -1) // 삭제되는 레코드가 없을때
	{
        memset(recordbuf, '\0', MAX_RECORD_SIZE);
        pack(recordbuf, p);
        if (cnt_entire_record == ((cnt_entire_page_num - 1) * (PAGE_SIZE / MAX_RECORD_SIZE))) //레코드 저장할 공간 없는 경우
		{
            insert_pageNum = cnt_entire_page_num;
            insert_record_num = 0;
            cnt_entire_page_num++;
            memset(pagebuf, '\0', PAGE_SIZE);
            strcpy(pagebuf, recordbuf);
            writePage(fp, pagebuf, insert_pageNum);
            cnt_entire_record++;
        } else if (((cnt_entire_page_num - 1) * (PAGE_SIZE / MAX_RECORD_SIZE)) > cnt_entire_record) //레코드 저장할 공간 남아있는 경우
		{
            insert_pageNum = cnt_entire_page_num - 1;
            insert_record_num = cnt_entire_record % (PAGE_SIZE / MAX_RECORD_SIZE);

            memset(pagebuf, '\0', PAGE_SIZE);
            readPage(fp, pagebuf, insert_pageNum);
            strcpy(pagebuf + MAX_RECORD_SIZE * insert_record_num, recordbuf);
            writePage(fp, pagebuf, insert_pageNum);
            cnt_entire_record++;
		}
		else
		{
			printf("error\n");
			return;
		}
	}
	else //삭제된 레코드에 새로운 레코드 저장
	{
		insert_record_num = del_record;
		insert_pageNum = del_page;

		memset(recordbuf,'\0', MAX_RECORD_SIZE);
		pack(recordbuf, p);

		memset(pagebuf, '\0', PAGE_SIZE);
		readPage(fp, pagebuf, insert_pageNum);

		del_record = pagebuf[insert_record_num * MAX_RECORD_SIZE + 5];
		del_page = pagebuf[insert_record_num * MAX_RECORD_SIZE + 1];


		memcpy(pagebuf + insert_record_num * MAX_RECORD_SIZE, recordbuf, MAX_RECORD_SIZE);

		writePage(fp, pagebuf, insert_pageNum);

    }

	//헤더레코드 업데이트
	update = cnt_entire_record;

	memset(pagebuf, '\0', PAGE_SIZE);
	memcpy(pagebuf, &cnt_entire_page_num, sizeof(int));
	memcpy(&pagebuf[4], &update, sizeof(int));
	memcpy(&pagebuf[8], &del_page, sizeof(int));
	memcpy(&pagebuf[12], &del_record, sizeof(int));

	rewind(fp);
	writePage(fp, pagebuf, 0);

	return;
}

//
// 주민번호와 일치하는 레코드를 찾아서 삭제하는 기능을 수행한다.
//
void delete(FILE *fp, const char *id)
{

	char	record_buffer[MAX_RECORD_SIZE];
	char 	page_buffer[PAGE_SIZE];
	char	headerBuffer[PAGE_SIZE];

	int		entirePageN;
	int		previous_del_page;
	int		previous_del_record;
	int		res_page;
	int		res_record;
	int		update;

	memset(headerBuffer, '\0', PAGE_SIZE);
	rewind(fp);
	readPage(fp, headerBuffer, 0); //헤더읽어오기

	entirePageN = headerBuffer[0];
    cnt_entire_record = headerBuffer[4];
    previous_del_page = headerBuffer[8];
    previous_del_record = headerBuffer[12];

	for (int i = 1 ; i < entirePageN ; ++i)
	{
		memset(page_buffer, '\0', PAGE_SIZE);
		readPage(fp, page_buffer, i);

		for (int j = 0 ; j < (PAGE_SIZE / MAX_RECORD_SIZE) ; ++j)
		{
			memset(record_buffer, '\0', MAX_RECORD_SIZE);
			memcpy(record_buffer, page_buffer + j * MAX_RECORD_SIZE, MAX_RECORD_SIZE);

			if (record_buffer[0] == '*')
			{
				if (i == entirePageN - 1)
				{
					printf("해당 주민번호가 존재하지 않습니다.\n");
					return;
				}
				continue;
			}

			Person person_buff;
			unpack(record_buffer, &person_buff);

			if (strcmp(person_buff.id, id) == 0) //삭제할 레코드 발견 했을 시
			{
				res_record = j;
				res_page = i;

                memcpy(&page_buffer[res_record * MAX_RECORD_SIZE], "*", sizeof(char));
                memcpy(&page_buffer[res_record * MAX_RECORD_SIZE + 1], &previous_del_page, sizeof(int));
                memcpy(&page_buffer[res_record * MAX_RECORD_SIZE + 5], &previous_del_record, sizeof(int));
                previous_del_page = res_page;
                previous_del_record = res_record;

                writePage(fp, page_buffer, res_page);

				//헤더페이지 업데이트
				update = cnt_entire_record;
				memset(page_buffer, '\0', PAGE_SIZE);
				memcpy(page_buffer, &entirePageN, sizeof(int));
				memcpy(&page_buffer[4], &update, sizeof(int));
				memcpy(&page_buffer[8], &previous_del_page, sizeof(int));
				memcpy(&page_buffer[12], &previous_del_record, sizeof(int));

				writePage(fp, page_buffer, 0);

				return;
			}
		}
	}
	printf("\n해당 주민번호가 존재하지 않습니다.\n"); //찾는 주민번호 없음
	return;
}

/*
*	자체구현함수
* 	기능 : string의 앞 뒤로 있는 #을 제거한 string을 리턴한다
*	인자 : #을 앞뒤로 trim 하고자 하는 string
*   리턴 : trim 된 string
*/

char*	my_trim(char	*str)
{
	int		len = strlen(str);
	char	*trimed_str = malloc(sizeof(char)*(len-1));

	for (int i = 0 ; i < len-2 ; ++i)
		trimed_str[i] = str[i+1];

	trimed_str[len-1] = '\0';

	return trimed_str;
}


int main(int argc, char *argv[])
{
	int 		entire_page_num = 1;
	int			update;
	int			delPage = -1;
	int			delRecord = -1;
	char 		headerBuffer[PAGE_SIZE];


    FILE *fp;
    Person person;

    file_name = (char *) malloc(sizeof(char) * strlen(argv[2]));
    strcpy(file_name, argv[2]);

	if (strcmp(argv[1], "a") == 0) // 추가
	{
        if (0 != access(file_name, F_OK)) //파일에 처음 데이터를 쓰는 경우일 때
		{
            fp = fopen(file_name, "w+");
            if (fp == NULL)
			{
				printf("fp error\n");
				return 1;
			}

			update = cnt_entire_record;

			memset(headerBuffer, '\0', PAGE_SIZE);
			memcpy(headerBuffer, &entire_page_num, sizeof(int));
			memcpy(&headerBuffer[4], &update, sizeof(int));
			memcpy(&headerBuffer[8], &delPage, sizeof(int));
			memcpy(&headerBuffer[12], &delRecord, sizeof(int));

            rewind(fp);
            writePage(fp, headerBuffer, 0);
            fclose(fp);
        }

        //이미 데이터가 쓰여있을 때
        fp = fopen(file_name, "r+");

        strcpy(person.id, argv[3]);
        strcpy(person.name, argv[4]);
        strcpy(person.age, argv[5]);
        strcpy(person.addr, argv[6]);
        strcpy(person.phone, argv[7]);
        strcpy(person.email, argv[8]);

        add(fp, &person);
        fclose(fp);

    }
	else if (strcmp(argv[1], "d") == 0) // 삭제
	{
		if (0 != access(file_name, F_OK))
		{
			printf("존재하지 않는 사람입니다.\n");
			return 1;
		}
		else
		{
			fp = fopen(file_name, "r+");
			delete(fp, argv[3]);
		}
	}
	else {
		printf("잘못된 옵션입니다.\n");
		return 1;
	}
	return 0;
}
