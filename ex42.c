#include <stdio.h>

int length(char* pstr);

int main()
{
	int len = length("abcde");
	printf("±Ê¿Ã = %d", len);
}

int length(char* pstr)
{
	int len = 0;

	while (*pstr != NULL)
	{
		pstr++;
		len++;
	}

	return len;
}