#include <stdio.h>
#include <string.h>

#define SKY "sky"


void main()
{
	char string[200];

	printf("������ �Է��� �� EnterŰ�� ġ����!\n");
	printf("�ƹ��͵� �Է����� ������ ���α׷��� ����˴ϴ�.\n");

	do
	{
		gets(string);

		if (strlen(string) == 0)
		{
			break;
		}

		printf("���ڿ��� ���̴� %d�Դϴ�.\n", strlen(string));
		
	} while (1);
}