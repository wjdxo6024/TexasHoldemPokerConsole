#include <stdio.h>
#include <ctype.h>

void main()
{
	char *string = "This is Korea!\t\n";
	int cnt = 0;

	while (*string)
	{
		if (isspace(*string))
		{
			cnt++;
		}

		string++;
	}

	printf("����, �� �׸��� ���๮���� ���� %d�Դϴ�.", cnt);
}