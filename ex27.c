#include <stdio.h>

int main()
{
	int x = 1;
	int y = 2;
	int max;

	max = x > y ? x : y;
	printf("max = %d\n", max);

	return 0;
}