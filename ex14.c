#include <stdio.h>

int main()
{
	int b;
	int j;
	
	b = 10 > 5;
	j = 10 > 20;

	printf("���� ���� b�� ���� %d\n", b);
	printf("���� ���� j�� ���� %d\n", j);

	if (b)
	{
		printf("10 > 5�� ���� ���Դϴ�.\n");
	}
	else
	{
		printf("10 > 5�� ���� �����Դϴ�.\n");
	}

	if (j)
	{
		printf("10 > 20�� ���� ���Դϴ�.\n");
	}
	else
	{
		printf("10 > 20�� ���� �����Դϴ�.\n");
	}

	if (-1)
	{
		printf("-1�� ���Դϴ�.\n");
	}
	else
	{
		printf("-1�� �����Դϴ�.\n");
	}

	return 0;
}