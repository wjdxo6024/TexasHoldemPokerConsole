#include <stdio.h>

int hapf(int value);

int main()
{
	printf("1부터 10까지의 합은 %d\n", hapf(10));
	printf("1부터 100까지의 합은 %d\n", hapf(100));
	printf("1부터 1000까지의 합은 %d\n", hapf(1000));
	return 0;
}

int hapf(int value)
{
	int i;
	int hap = 0;
	for (i = 1; i <= value; i = i + 1)
	{
		hap = hap + i;
	}

	return hap;
}