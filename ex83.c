#include <stdio.h>
#include <stdlib.h>

void main()
{
	int value;
	char string[100];
	int radix;

	radix = 10;

	value = 5;
	itoa(value, string, radix);
	printf("��ȯ�� ���ڿ��� %s�Դϴ�.\n", string);

	value = -12345;
	itoa(value, string, radix);
	printf("��ȯ�� ���ڿ��� %s�Դϴ�.\n", string);
}