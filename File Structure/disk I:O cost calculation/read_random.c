#include <stdio.h>
#include <sys/types.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/types.h>
#define RECORD_SIZE 250

//필요하면 header file 추가 가능

#define SUFFLE_NUM	10000	// 이 값은 마음대로 수정할 수 있음.

void GenRecordSequence(int *list, int n);
void swap(int *a, int *b);
// 필요한 함수가 있으면 더 추가할 수 있음.

int main(int argc, char **argv)
{
	int *read_order_list;
	int num_of_records; // 레코드 파일에 저장되어 있는 전체 레코드의 수
	double			time_cnt;
	FILE			*fp;
	char			buffer[RECORD_SIZE];
	char			*file_name;
	int				record_num;
	struct timeval	start, end;


	file_name = argv[1];
	fp = fopen(file_name, "rb");

	fread(&num_of_records, 1, sizeof(int), fp);
	read_order_list = malloc(sizeof(int) * num_of_records);

	// 이 함수를 실행하면 'read_order_list' 배열에는 읽어야 할 레코드 번호들이 나열되어 저장됨
	GenRecordSequence(read_order_list, num_of_records);

	//
	// 'read_order_list'를 이용하여 random 하게 read 할 때 걸리는 전체 시간을 측정하는 코드 구현
	//

	gettimeofday(&start, NULL);

	for (int i = 0 ; i < num_of_records ; i++)
	{
		fseek(fp, read_order_list[i] * 250 , SEEK_SET);
		fread(buffer, RECORD_SIZE, 1, fp);
	}

	gettimeofday(&end, NULL);

	time_cnt = (((double)end.tv_sec - (double)start.tv_sec)*1000000) + (((double)end.tv_usec - (double)start.tv_usec));

	printf("#records: %d elapsed_time: %d us\n", num_of_records, (int)(time_cnt));

	return 0;
}

void GenRecordSequence(int *list, int n)
{
	int i, j, k;

	srand((unsigned int)time(0));

	for(i=0; i<n; i++)
	{
		list[i] = i;
	}

	for(i=0; i<SUFFLE_NUM; i++)
	{
		j = rand() % n;
		k = rand() % n;
		swap(&list[j], &list[k]);
	}
}

void swap(int *a, int *b)
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
