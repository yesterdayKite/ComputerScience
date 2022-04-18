#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#define RECORD_SIZE 250


//필요하면 header file 추가 가능

int main(int argc, char **argv)
{
	int					record_num;
	char				*file_name;
	FILE				*fp;
	struct timeval		start, end;
	double				time_cnt;
	char				buffer[RECORD_SIZE];

	file_name = argv[1];
	fp = fopen(file_name, "rb");

	fread(&record_num, 1, sizeof(int), fp);


	gettimeofday(&start, NULL);
	for (int i = 0 ; i < record_num ; i++)
	{
		fread(buffer, 1, RECORD_SIZE, fp);
	}
	gettimeofday(&end, NULL);

	time_cnt = (((double)end.tv_sec - (double)start.tv_sec)*1000000) + (((double)end.tv_usec - (double)start.tv_usec));

	printf("#records: %d elapsed_time: %d us\n", record_num ,(int)time_cnt);

	fclose(fp);

	return 0;
}
