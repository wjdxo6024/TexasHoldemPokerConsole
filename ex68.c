#include <stdio.h>
#include <string.h>

#define TOKEN " "

void main()
{
	char string[100];
	char *token;

	puts("���ڿ��� �Է��� �� EnterŰ�� ġ����!");

	gets(string);

	token = strtok(string, TOKEN);
	while (token != NULL)
	{
		puts(token);

		token = strtok(NULL, TOKEN);
	}
}