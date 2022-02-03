#include <stdio.h>

int main()
{
	int x = 4;
	int y = 2;
	int z;

	z = x + y;				// 6 = 4 + 2
	printf("x + y = %d\n", z);

	z = x - y;				// 2 = 4 - 2
	printf("x - y = %d\n", z);

	z = x * y;				// 8 = 4 * 2
	printf("x * y = %d\n", z);

	z = x / y;				// 2 = 4 / 2
	printf("x / y = %d\n", z);

	z = (x + y) * (x - y);	// 12 = (4 + 2) * (4 - 2)
	printf("(x + y) * (x - y) = %d\n", z);

	z = (x * y) + (x / y);	// 10 = (4 * 2) + (4 / 2)
	printf("(x * y) + (x / y) = %d\n", z);

	z = x + y + 2004;		// 2010 = 4 + 2 + 2004
	printf("x + y + 2004 = %d\n", z);

	z = 2004 - x - y;		// 1998 = 2004 - 4 - 2
	printf("2004 - x - y = %d\n", z);

	return 0;
}