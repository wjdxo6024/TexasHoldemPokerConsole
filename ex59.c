#include <stdio.h>
#include <stdlib.h>

#define SKY "sky"

void main()
{
	char string[100];
	int ret;

	printf("���ܾ �Է��� �� EnterŰ�� ġ����!\n");
	printf("sky�� �Է��ϸ� ���α׷��� ����˴ϴ�.\n");

	do
	{
		gets(string);

		ret = strcmp(string, SKY);

		if (ret == 0)
		{
			printf("%s == %s, ret = %d\n", string, SKY, ret);
			break;
		}
		else if (ret < 0) printf("%s < %s, ret = %d\n", string, SKY, ret);
		else printf("%s > %s, ret = %d\n", string, SKY, ret);
	} while (1);
}