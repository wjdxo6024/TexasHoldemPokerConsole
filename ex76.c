#include <stdio.h>

void main()
{
	char cValue = 'a';
	int iValue = 1234567;
	long lValue = 7890123;
	float fValue = 3.141592;
	double dValue = 3.141592;
	char *string = "korea";
	char buffer[100];

	sprintf(buffer, "char 형은 %c", cValue);
	puts(buffer);

	sprintf(buffer, "int 형은 %d", iValue);
	puts(buffer);

	sprintf(buffer, "long 형은 %ld", lValue);
	puts(buffer);

	sprintf(buffer, "float 형은 %f", fValue);
	puts(buffer);

	sprintf(buffer, "double 형은 %e", dValue);
	puts(buffer);

	sprintf(buffer, "char* 형은 %s", string);
	puts(buffer);
}