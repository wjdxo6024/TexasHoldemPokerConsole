#include <stdio.h>
#include <stdlib.h>

void main()
{
	char *string = "0xFF";
	char *stop;
	int  radix;
	long  value;

	radix = 16;

	value = strtol(string, &stop, radix);

	printf("%d���� ���ڰ� ��ȯ�Ǿ����ϴ�.\n", stop - string);
	printf("16���� %s�� ���ڷ� ��ȯ�ϸ� %ld�Դϴ�.\n", string, value);
}