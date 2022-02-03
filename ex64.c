#include <stdio.h>
#include <string.h>

#define SKY  "sky"

void main()
{
	char string[100];
	char *ret;

	puts("문자열을 입력한 후  Enter키를 치세요!");
	puts("문자열 중에 sky가 포함되어 있으면, 프로그램은 종료됩니다.");

	do
	{
		gets(string);

		ret = strstr(string, SKY);

		if (ret == NULL)
		{
			puts("문자열 중에 sky가 없습니다.");
		}
		else
		{
			printf("%d 위치에서 sky 문자열을 찾았습니다.", ret - string);
			break;
		}
	} while (1);
}