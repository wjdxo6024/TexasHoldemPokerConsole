#include <stdio.h>
#include <math.h>
#include <string.h>

int IsReverse(char* string)
{
	int i = 0;
	int stringLength = strlen(string);
	int stringCenter = stringLength / 2;

	for (i = 0; i < stringCenter; i++)
	{
		if (*(string + i) != *(string + (stringLength - 1 - i)))
		{
			return 0;
		}
	}

	return 1;
}

int main()
{
	char Input[100];
	char Temp[100];

	do
	{
		gets(Input);

		if (strlen(Input) == 0)
		{
			break;
		}

		strcpy(Temp, Input);

		if (IsReverse(strlwr(Input)))
		{
			printf("%s�� ȸ���Դϴ�.\n", Temp);
		}
		else
		{
			printf("%s�� ȸ���� �ƴմϴ�.\n", Temp);
		}

	} while (1);


	return 0;
}