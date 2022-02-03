#include <stdio.h>

int main()
{
	int i;
	int j;

	for (i = 1; i <= 100; i++)
	{
		for (j = 1; j <= 9; j++)
		{
			printf("%d * %d = %2d\n", i, j, i * j);
			if (i == 9 && j == 9) goto ku_ku_end;
		}
	}

ku_ku_end:;

	return 0;
}