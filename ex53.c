#include <stdio.h>

void main()
{
	int count;
	int tmp;
	int total = 0;

	for (count = 1; count <= 3; count++)
	{
		printf("%d ��° �������� �Է��� �� EnterŰ�� ��������.\n", count);

		scanf("%d", &tmp);

		total += tmp;

		printf("�Է� �� = %d, �� �� = %d\n", tmp, total);
	}

	printf("���� ������ �� ���� %d�Դϴ�.\n", total);
}