#include <stdio.h>
#include <string.h>

#define SKY "sky"


void main()
{
	char string[200];

	printf("문장을 입력한 후 Enter키를 치세요!\n");
	printf("아무것도 입력하지 않으면 프로그램이 종료됩니다.\n");

	do
	{
		gets(string);

		if (strlen(string) == 0)
		{
			break;
		}

		printf("문자열의 길이는 %d입니다.\n", strlen(string));
		
	} while (1);
}