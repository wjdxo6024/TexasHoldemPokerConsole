#include <stdio.h>
#include <string.h>

void main()
{
	char s1[100] = "123";
	char s2[100] = "123";

	strcpy(&s1[4], "abc");
	strcpy(&s2[4], "efg");

	if (strcmp(s1, s2) == 0)
	{
		puts("strcmp : ������ ���� ��ġ�մϴ�.");
	}

	if (memcmp(s1, s2, 7) == 0)
	{
		puts("memcmp : ������ ���� ��ġ�մϴ�.");
	}
	else
	{
		puts("memcmp : ������ ���� ��ġ���� �ʽ��ϴ�.");
	}
}