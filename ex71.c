#include <stdio.h>
#include <string.h>

void main()
{
	char string[100];

	puts("���ڿ��� �Է��� �� EnterŰ�� ġ����!");
	puts("�ƹ� ���ڵ� �Է����� ������ ���α׷��� ����˴ϴ�!");

	do
	{
		gets(string);

		if (strlen(string) == 0) break;

		strnset(string, '*', 5);
		puts(string);
	} while (1);
}