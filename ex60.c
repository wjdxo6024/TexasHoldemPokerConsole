#include <stdio.h>

#define SKY "sky"

int My_strcmp(const char* string1, const char* string2);

void main()
{
	char string[100];
	int ret;

	printf("���ܾ �Է��� �� EnterŰ�� ġ����!\n");
	printf("sky�� �Է��ϸ� ���α׷��� ����˴ϴ�.\n");

	do
	{
		gets(string);

		ret = My_strcmp(string, SKY);

		if (ret == 0)
		{
			printf("%s == %s, ret = %d\n", string, SKY, ret);
			break;
		}
		else if (ret < 0) printf("%s < %s, ret = %d\n", string, SKY, ret);
		else printf("%s > %s, ret = %d\n", string, SKY, ret);
	} while (1);
}

int My_strcmp(const char* string1, const char* string2)
{
	if (*string1 == (int)NULL && *string2 == (int)NULL) return 0;

	while (*string1 != (int)NULL)
	{
		if (*string2 == (int)NULL) return 1;

		if (*string1 == *string2)
		{
			string1++;
			string2++;
			continue;
		}

		if (*string1 < *string2) return -1;
		else return 1;
	}

	if (*string2 != (int)NULL) return -1;

	return 0;
}