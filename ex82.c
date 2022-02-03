#include <stdio.h>
#include <stdlib.h>

void main()
{
	char *string = "1.234E-10";
	char *stop;
	double value;

	value = strtod(string, &stop);

	printf("%d개의 문자가 변환되었습니다.\n", stop - string);
	printf("문자열 [%s]를 숫자로 변환하면 %E입니다.\n", string, value);
}