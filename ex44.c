#include <stdio.h>

union tagVariant
{
	int i;
	float d;
};

int main()
{
	union tagVariant V;

	V.i = 0;
	V.d = 5.5;

	printf("V.i = %d\n", V.i);
	printf("V.d = %df\n", V.d);
}