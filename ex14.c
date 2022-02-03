#include <stdio.h>

int main()
{
	int b;
	int j;
	
	b = 10 > 5;
	j = 10 > 20;

	printf("논리형 변수 b의 값은 %d\n", b);
	printf("논리형 변수 j의 값은 %d\n", j);

	if (b)
	{
		printf("10 > 5의 식은 참입니다.\n");
	}
	else
	{
		printf("10 > 5의 식은 거짓입니다.\n");
	}

	if (j)
	{
		printf("10 > 20의 식은 참입니다.\n");
	}
	else
	{
		printf("10 > 20의 식은 거짓입니다.\n");
	}

	if (-1)
	{
		printf("-1은 참입니다.\n");
	}
	else
	{
		printf("-1은 거짓입니다.\n");
	}

	return 0;
}