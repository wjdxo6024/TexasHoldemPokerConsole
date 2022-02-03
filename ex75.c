#include <stdio.h>
#include <string.h>
#include <malloc.h>

void main()
{
	char string[100];
	char *pstr;

	puts("문자열을 입력한 후 Enter키를 치세요!");
	puts("아무 문자도 입력하지 않으면 프로그램은 종료됩니다!");

	do
	{
		gets(string);

		if (strlen(string) == 0) break;

		pstr = strdup(string);

		strcpy(string, "temporary string");

		printf("문자열 string : %s\n", string);
		printf("문자열 pstr : %s\n", pstr);

		free(pstr);
	} while (1);
}