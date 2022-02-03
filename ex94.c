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

	printf("공백, 탭 그리고 개행문자의 수는 %d입니다.", cnt);
}