#define _CRT_NONSTDC_NO_WARNINGS
#include <stdio.h>
#include <conio.h>

#define ENTER 13

void main()
{
	int ch;

	printf("�ƽ�Ű �ڵ带 ��ȯ�� Ű�� ��������...\n");
	printf("Enter Ű�� ������ ���α׷��� ����˴ϴ�.\n");

	do
	{
		ch = getch();

		printf("���� : (%c), �ƽ�Ű �ڵ� = (%d) \n", ch, ch);
	} while (ch != ENTER);
}