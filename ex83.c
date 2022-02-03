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
	printf("변환된 문자열은 %s입니다.\n", string);

	value = -12345;
	itoa(value, string, radix);
	printf("변환된 문자열은 %s입니다.\n", string);
}