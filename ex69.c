#include <stdio.h>
#include <string.h>

#define TOKEN " "

void main()
{
	char string[100];
	char *pos;

	puts("���ڿ��� �Է��� �� EnterŰ�� ġ����!");

	gets(string);

	pos = strpbrk(string, TOKEN);
	while (pos != NULL)
	{
		puts(pos++);

		pos = strpbrk(pos, TOKEN);
	}
}