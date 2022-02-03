#include <stdio.h>
#include <stdlib.h>

void main()
{
	double value;
	char buffer[100];

	value = 3.14e10;
	gcvt(value, 3, buffer);

	printf("변환된 문자열은 %s입니다.\n", buffer);

	value = -3.14e10;
	gcvt(value, 3, buffer);

	printf("변환된 문자열은 %s입니다.\n", buffer);
}