#include <stdio.h>

int main()
{
	int x = 5;
	int y = 2;

	if (x > 0 && x < 10)
	{
		printf("0 > x < 10 \n");
	}

	if (x < 0 || y == 2)
	{
		printf("x�� 0���� �۰ų�, y�� 2�Դϴ�.\n");
	}

	if (!(x > y))
	{
		printf("x�� y���� ũ�� �ʽ��ϴ�.\n");
	}
	return 0;
}