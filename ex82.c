#include <stdio.h>
#include <stdlib.h>

void main()
{
	char *string = "1.234E-10";
	char *stop;
	double value;

	value = strtod(string, &stop);

	printf("%d���� ���ڰ� ��ȯ�Ǿ����ϴ�.\n", stop - string);
	printf("���ڿ� [%s]�� ���ڷ� ��ȯ�ϸ� %E�Դϴ�.\n", string, value);
}