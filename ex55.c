#include <stdio.h>
int count(char* str);


void main()
{
	char string[100];
	char *ret;

	ret = gets(string);

	if (ret != NULL)
	{
		printf("���� 'a'�� ������ %d���Դϴ�.", count(string));
	}
}

int count(char *str)
{
	int cnt = 0;
	while (*str != (int)NULL)
	{
		if (*str++ == 'a') cnt++;
	}

	return cnt;
}