#include <stdio.h>
#include <string.h>

#define FIND_CHAR  'h'

void main()
{
	char string[100];
	char *ret;

	puts("���ڿ��� �Է��� ��  EnterŰ�� ġ����!");
	puts("���ڿ� �߿� 'h'�� ���ԵǾ� ������, ���α׷��� ����˴ϴ�.");

	do
	{
		gets(string);

		ret = strchr(string, FIND_CHAR);

		if (ret == NULL)
		{
			puts("���ڿ� �߿� 'h'�� �����ϴ�.");
		}
		else
		{
			printf("%d ��ġ���� 'h' ���ڸ� ã�ҽ��ϴ�.", ret - string);
			break;
		}
	} while (1);
}