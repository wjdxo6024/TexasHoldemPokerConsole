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

	sprintf(buffer, "char ���� %c", cValue);
	puts(buffer);

	sprintf(buffer, "int ���� %d", iValue);
	puts(buffer);

	sprintf(buffer, "long ���� %ld", lValue);
	puts(buffer);

	sprintf(buffer, "float ���� %f", fValue);
	puts(buffer);

	sprintf(buffer, "double ���� %e", dValue);
	puts(buffer);

	sprintf(buffer, "char* ���� %s", string);
	puts(buffer);
}