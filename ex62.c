#include <stdio.h>
#include <string.h>

void main()
{
	char string1[100];
	char string2[100];

	printf("첫 번째 단어를 입력하세요.!\n");
	gets(string1);

	printf("두 번째 단어를 입력하세요.!\n");
	gets(string2);

	strcat(string1, string2);

	puts(string1);
}