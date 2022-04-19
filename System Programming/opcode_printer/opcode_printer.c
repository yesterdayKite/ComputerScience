/*
 * 설  명 : 이 프로그램은 SIC/XE 머신을 위한 간단한 Assembler 프로그램의 메인루틴으로,
 * 입력된 파일의 코드 중, 명령어에 해당하는 OPCODE를 찾아 출력한다.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#include "opcode_printer.h"

void    buff_clear(char        *buff);

/* ------------------------------------------------------------ * 설명 : 사용자로 부터 어셈블리 파일을 받아서 명령어의 OPCODE를 찾아 출력한다.
 * 매계 : 실행 파일, 어셈블리 파일
 * 반환 : 성공 = 0, 실패 = < 0
 * 주의 : 현재 어셈블리 프로그램의 리스트 파일을 생성하는 루틴은 만들지 않았다.
 *           또한 중간파일을 생성하지 않는다.
 * ------------------------------------------------------------ */
int main(int args, char *arg[])
{
    if (init_my_assembler() < 0)
    {
        printf("init_my_assembler: 프로그램 초기화에 실패 했습니다.\n");
        return -1;
    }

    if (assem_pass1() < 0)
    {
        printf("assem_pass1: 패스1 과정에서 실패하였습니다.  \n");
        return -1;
    }

    make_opcode_output("output_20182630");

    /*
     * 추후 프로젝트에서 사용되는 부분
     *
    make_symtab_output("symtab_00000000");
    if (assem_pass2() < 0)
    {
        printf(" assem_pass2: 패스2 과정에서 실패하였습니다.  \n");
        return -1;
    }

    make_objectcode_output("output_00000000");
    */
    return 0;
}

/* ------------------------------------------------------------ * 설명 : 프로그램 초기화를 위한 자료구조 생성 및 파일을 읽는 함수이다.
 * 매계 : 없음
 * 반환 : 정상종료 = 0 , 에러 발생 = -1
 * 주의 : 각각의 명령어 테이블을 내부에 선언하지 않고 관리를 용이하게 하기 위해서
 *       파일 단위로 관리하여 프로그램 초기화를 통해 정보를 읽어 올 수 있도록
 *       구현하였다.
 * ------------------------------------------------------------ */
int init_my_assembler(void)
{
    int result;

    if ((result = init_inst_file("inst.data")) < 0)
        return -1;
    if ((result = init_input_file("input.txt")) < 0)
        return -1;
    return result;
}

/* ----------------------------------------------------------------------------------
 * 설명 : 머신을 위한 기계 코드목록 파일을 읽어 기계어 목록 테이블(inst_table)을
 *        생성하는 함수이다.
 * 매계 : 기계어 목록 파일
 * 반환 : 정상종료 = 0 , 에러 < 0
 * 주의 : 기계어 목록파일 형식은 자유롭게 구현한다. 예시는 다음과 같다.
 *
 *    ===============================================================================
 *           | 이름 | 형식 | 기계어 코드 | 오퍼랜드의 갯수 | NULL|
 *    ===============================================================================
 *
 * ----------------------------------------------------------------------------------
 */
int init_inst_file(char *inst_file)
{
    FILE *file;
    int errno;

    errno = 0;

    if (!(file = fopen(inst_file, "r")))
        errno = -1;

    for (int i = 0 ; i < MAX_INST ; i++)
    {
        // 한줄 씩 읽어들이면서, 공백으로 구분하여 저장한다
        inst_table[i] = calloc(1, sizeof(inst));
        if (4 != fscanf(file, "%s %c %d %d", inst_table[i]->str, &inst_table[i]->op, &inst_table[i]->format, &inst_table[i]->ops))
            break;
        else
            inst_index++;

        // STA인식오류 직접 수정 (원인불명)
        if (strcmp(inst_table[i]->str, "STA") == 0)
        {
            inst_table[i]->op = 0x0C;
            inst_table[i]->format= 34;
            inst_table[i]->ops = 1;
        }
    }
    return errno;
}

/* ----------------------------------------------------------------------------------
 * 설명 : 어셈블리 할 소스코드를 읽어 소스코드 테이블(input_data)를 생성하는 함수이다.
 * 매계 : 어셈블리할 소스파일명
 * 반환 : 정상종료 = 0 , 에러 < 0
 * 주의 : 라인단위로 저장한다.
 *
 * ----------------------------------------------------------------------------------
 */
int init_input_file(char *input_file)
{
    FILE *file;
    int errno = 0;

    char        buff[500];

    line_num = 0;

    if(!(file = fopen(input_file, "r")))        errno = -1; // Fp 오류시 error
    buff_clear(buff);

    while(fgets(buff, sizeof(buff), file) != NULL) // 한줄식 읽어들인다
    {
        //buff에 읽은 string을 input_table로 복사한다.
        input_data[line_num] = malloc(sizeof(char)*500);
        strcpy(input_data[line_num++], buff);
        buff_clear(buff);
    }
    return errno;
}

/* ----------------------------------------------------------------------------------
 * 설명 : 소스 코드를 읽어와 토큰단위로 분석하고 토큰 테이블을 작성하는 함수이다.
 *        패스 1로 부터 호출된다.
 * 매계 : 파싱을 원하는 문자열
 * 반환 : 정상종료 = 0 , 에러 < 0
 * 주의 : my_assembler 프로그램에서는 라인단위로 토큰 및 오브젝트 관리를 하고 있다.
 * ----------------------------------------------------------------------------------
 */
int token_parsing(char *str)
{
    char        c;
    int            errno;
    int            operand_num;
    char        buff[4][100] = {'\0', };
    char        *ptr;
    int         operand_cnt;

    errno = 0;
    operand_num = 0;
    operand_cnt = 0;


    token_table[token_line] = malloc(sizeof(token));

    sscanf(input_data[token_line], "%c", &c); // 해당 라인을 판단하기 위해 첫글자만 읽어들인다

    if (c == '.') // 주석인경우
    {
        token_table[token_line]->label = calloc(strlen(buff[0]), sizeof(char));
        strcpy(token_table[token_line]->label, ".");
        strcpy(token_table[token_line]->comment, input_data[token_line]);
        token_line++;
        return errno;
    }

    // 1. buffer에 읽어들이기
    if ((c == '\t') || (c == ' ')) // label 이 없을 때
        sscanf(input_data[token_line], "%s %s %s",buff[1], buff[2], buff[3]);
    else // label 이 있을 때
        sscanf(input_data[token_line], "%s %s %s %s",buff[0], buff[1], buff[2], buff[3]);

    // 2. buffer 내용을 tokenize
    if (buff[0][0] != '\0') // label 이 있을 때 label 저장
    {
        token_table[token_line]->label = calloc(strlen(buff[0]), sizeof(char));
        strcpy(token_table[token_line]->label, buff[0]);
    }
    else    token_table[token_line]->label = NULL;

    // operator 저장
    token_table[token_line]->operator = calloc(strlen(buff[1]), sizeof(char));
    if (buff[1][0] == '+')
    {
        strcpy(token_table[token_line]->operator, &buff[1][1]);
        token_table[token_line]->nixbpe = (char)1;
    }
    else    strcpy(token_table[token_line]->operator, buff[1]);

    // operand 저장
    ptr = strtok(buff[2], ",");
    while(ptr != NULL)
    {
        token_table[token_line]->operand[operand_cnt] = calloc(50, sizeof(char));
        strcpy(token_table[token_line]->operand[operand_cnt], ptr);
        ptr = strtok(NULL, ",");
        operand_cnt++;
    }
    token_table[token_line]->operand_num = operand_cnt;

    token_line++;
    return errno;

}

/* ----------------------------------------------------------------------------------
 * 설명 : 입력 문자열이 기계어 코드인지를 검사하는 함수이다.
 * 매계 : 토큰 단위로 구분된 문자열
 * 반환 : 정상종료 = 기계어 테이블 인덱스, 에러 < 0
 * 주의 :
 *
 * ----------------------------------------------------------------------------------
 */
int search_opcode(char *str)
{
    for (int i = 0 ; i < inst_index ; i++)
    {
        if (strcmp(inst_table[i]->str, str ) == 0) //inst_table내 str과 일치하는 string이 있을때
            return i; // 기계어 테이블 인덱스를 반환한다.
    }
    return -1;
}

/* ----------------------------------------------------------------------------------
* 설명 : 어셈블리 코드를 위한 패스1과정을 수행하는 함수이다.
*           패스1에서는..
*           1. 프로그램 소스를 스캔하여 해당하는 토큰단위로 분리하여 프로그램 라인별 토큰
*           테이블을 생성한다.
*
* 매계 : 없음
* 반환 : 정상 종료 = 0 , 에러 = < 0
* 주의 : 현재 초기 버전에서는 에러에 대한 검사를 하지 않고 넘어간 상태이다.
*      따라서 에러에 대한 검사 루틴을 추가해야 한다.
*
* -----------------------------------------------------------------------------------
*/
static int assem_pass1(void)
{
    /* input_data의 문자열을 한줄씩 입력 받아서
     * token_parsing()을 호출하여 token_unit에 저장
     */
    int            errno = 0;
    token_line = 0;

    for (int i = 0 ; i < line_num ; i++){
        errno = token_parsing(input_data[i]);  // 한줄씩 parsing하고, 에러가 있는지 매회 검사한다.
    }

    return errno;
}

/* ----------------------------------------------------------------------------------
* 설명 : 입력된 문자열의 이름을 가진 파일에 프로그램의 결과를 저장하는 함수이다.
*        여기서 출력되는 내용은 명령어 옆에 OPCODE가 기록된 표(과제 3번) 이다.
* 매계 : 생성할 오브젝트 파일명
* 반환 : 없음
* 주의 : 만약 인자로 NULL값이 들어온다면 프로그램의 결과를 표준출력으로 보내어
*        화면에 출력해준다.
*        또한 과제 3번에서만 쓰이는 함수이므로 이후의 프로젝트에서는 사용되지 않는다.
* -----------------------------------------------------------------------------------
*/
void make_opcode_output(char *file_name)
{
    FILE        *fp;
    int         opcode_num = -1;

    fp = fopen(file_name , "w");

    for (int i =0 ; i < token_line ; i++)
    {
        // START인 경우 출력
        if (token_table[i]->operator != NULL && strcmp(token_table[i]->operator, "START") == 0)
        {
            fprintf(fp, "%-10s%-10s%60d\n", token_table[i]->label, token_table[i]->operator, 0);
            continue;
        }

        // 주석인경우 출력
        if (token_table[i]->label != NULL && strcmp(token_table[i]->label, ".") == 0)
        {
            fprintf(fp, "%s\n", token_table[i]->comment);
            continue;
        }

        // label 출력
        if(token_table[i]->label != NULL)   fprintf(fp, "%-10s", token_table[i]->label);
        else                                fprintf(fp, "%-10s", "");

        // operator 출력
        fprintf(fp, "%-10s", token_table[i]->operator);
        // operand 출력
        for (int j = 0 ; j < token_table[i]->operand_num ; j++)
        {
            fprintf(fp, "%s",token_table[i]->operand[j]);
            if (j < token_table[i]->operand_num - 1)    fprintf(fp, ",");
        }

        // opcode 찾아서 출력
        opcode_num = search_opcode(token_table[i]->operator);
        if (opcode_num != -1)
            fprintf(fp, "%50X", inst_table[opcode_num]->op);

        fprintf(fp, "\n");
    }

    fclose(fp);
}

/* ----------------------------------------------------------------------------------
* 설명 : 입력된 문자열의 이름을 가진 파일에 프로그램의 결과를 저장하는 함수이다.
*        여기서 출력되는 내용은 SYMBOL별 주소값이 저장된 TABLE이다.
* 매계 : 생성할 오브젝트 파일명
* 반환 : 없음
* 주의 : 만약 인자로 NULL값이 들어온다면 프로그램의 결과를 표준출력으로 보내어
*        화면에 출력해준다.
*
* -----------------------------------------------------------------------------------
*/
void make_symtab_output(char *file_name)
{
    /* add your code here */
}

/* ----------------------------------------------------------------------------------
* 설명 : 어셈블리 코드를 기계어 코드로 바꾸기 위한 패스2 과정을 수행하는 함수이다.
*           패스 2에서는 프로그램을 기계어로 바꾸는 작업은 라인 단위로 수행된다.
*           다음과 같은 작업이 수행되어 진다.
*           1. 실제로 해당 어셈블리 명령어를 기계어로 바꾸는 작업을 수행한다.
* 매계 : 없음
* 반환 : 정상종료 = 0, 에러발생 = < 0
* 주의 :
* -----------------------------------------------------------------------------------
*/
static int assem_pass2(void)
{
    /* add your code here */
    return 0;
}

/* ----------------------------------------------------------------------------------
* 설명 : 입력된 문자열의 이름을 가진 파일에 프로그램의 결과를 저장하는 함수이다.
*        여기서 출력되는 내용은 object code (프로젝트 1번) 이다.
* 매계 : 생성할 오브젝트 파일명
* 반환 : 없음
* 주의 : 만약 인자로 NULL값이 들어온다면 프로그램의 결과를 표준출력으로 보내어
*        화면에 출력해준다.
*
* -----------------------------------------------------------------------------------
*/
void make_objectcode_output(char *file_name)
{
    /* add your code here */
}



/*
 *  자체제작 함수 (보고서에 사용목적 명시해둠)
 */

// * 설명 : char배열의 모든 요소를 '\0'로 초기화시킨다.
// * 매개 : 초기화시키고자 하는 string
// * 반환 : 모두 '\0'로 초기화된 string
void    buff_clear(char        *buff)
{
    int        buff_len;

    buff_len = (int)strlen(buff);

    for (int i = 0 ; i < buff_len ; i++)
        buff[i] = '\0';

    return;
}

