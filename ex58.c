#include <stdio.h>

#define KOREA "¥Î«—πŒ±π"

char* My_strcpy(char* dest, const char* src);

void main()
{
	char string[100];

	My_strcpy(string, KOREA);

	puts(string);
}

char* My_strcpy(char* dest, const char* src)
{
	if (dest == (int)NULL || src == (int)NULL)
	{
		if (*dest != (int)NULL) *dest = (int)NULL;
		return NULL;
	}

	do
	{
		*dest++ = *src;
	} while (*src++ != (int)NULL);

	return dest;
}