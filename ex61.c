#include <stdio.h>
#include <string.h>

#define SKY "sky"


void main()
{
	char string[100];
	int ret;

	printf("영단어를 입력한 후 Enter키를 치세요!\n");
	printf("sky를 입력하면 프로그램이 종료됩니다.\n");

	do
	{
		gets(string);

		ret = strncmp(string, SKY, 3);

		if (ret == 0)
		{
			printf("%3.3s == %s, ret = %d\n", string, SKY, ret);
			break;
		}
		else if (ret < 0) printf("%s < %s, ret = %d\n", string, SKY, ret);
		else printf("%s > %s, ret = %d\n", string, SKY, ret);
	} while (1);
}