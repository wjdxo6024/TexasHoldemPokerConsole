#include <stdio.h>

int main()
{
	int saram_A = 0;
	int saram_B = 0;
	int* pointer;
	int* psaram;

	pointer = &saram_A;
	*pointer = 1;
	printf("%d, %d\n", saram_A, *pointer);

	psaram = &saram_A;
	*psaram = 2;
	printf("%d, %d, %d\n", saram_A, *pointer, *psaram);

	pointer = &saram_B;
	*psaram = 3;
	printf("%d, %d, %d\n", saram_A, saram_B, *pointer);

	psaram = &saram_B;
	*psaram = 4;
	printf("%d, %d, %d, %d\n", saram_A, saram_B, *pointer, *psaram);

	return 0;
}