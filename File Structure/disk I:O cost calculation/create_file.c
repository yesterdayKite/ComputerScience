#include <stdio.h>
#include <stdlib.h>

#define RECORD_SIZE 250

typedef struct		_Student
{
	char		first_name[50];
	char		last_name[50];
	char		major[50];
	char		phone_num[50];
	char		student_num[50];
}					Student;


Student**			init_dummy_data(void)
{
	int				rand_int;
	Student			**student_list;

	Student			dum1 = { .first_name = "Jeyeon", .last_name = "Ae", .major = "computer", .phone_num = "1234-5678", .student_num = "20182630"};
	Student			dum2 = { .first_name = "Mark", .last_name = "Lee", .major = "software", .phone_num = "4736-4816", .student_num = "20192630"};
	Student			dum3 = { .first_name = "Chenle", .last_name = "Jjong", .major = "Econonmics", .phone_num = "2844-0986", .student_num = "20202630"};
	Student			dum4 = { .first_name = "Johnny", .last_name = "Suh", .major = "Electronic_engeenering", .phone_num = "3844-8736", .student_num = "20212630"};
	Student			dum5 = { .first_name = "Chitapon", .last_name = "Lichaiyaphonecool", .major = "Modern Art", .phone_num = "4432-4739", .student_num = "20222630"};

	student_list = malloc(sizeof(Student*) * 5);
	student_list[0] = &dum1;
	student_list[1] = &dum2;
	student_list[2] = &dum3;
	student_list[3] = &dum4;
	student_list[4] = &dum5;

	return student_list;
}

void				write_file(FILE	*fp, int record_num, Student **dummy_data)
{
	int			rand_int;

	fwrite(&record_num, 1, sizeof(int), fp);
	for (int i = 0 ; i < record_num ; i++)
	{
		rand_int = rand() % 5;
		fwrite(dummy_data[rand_int]->first_name, 1, RECORD_SIZE, fp);
		fwrite(dummy_data[rand_int]->last_name, 1, RECORD_SIZE, fp);
		fwrite(dummy_data[rand_int]->major, 1, RECORD_SIZE, fp);
		fwrite(dummy_data[rand_int]->phone_num, 1, RECORD_SIZE, fp);
		fwrite(dummy_data[rand_int]->student_num, 1, RECORD_SIZE, fp);
	}

	return;
}

int 				main(int argc, char **argv)
{
	int			record_num;
	char		*file_name;
	FILE		*fp;
	Student		**dummy_data;

	record_num = atoi(argv[1]);
	file_name = argv[2];
	dummy_data = init_dummy_data();


	fp = fopen(file_name, "wb");

	write_file(fp, record_num, dummy_data);

	fclose (fp);
	free(dummy_data);
	return 0;
}
