#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

int PrintBits(int number);

int main()
{
	int numInput; // �Է¹��� ����
	int digit; // �����ϰ��� �ϴ� �ڸ���
	int tempNumber; // �Է¹��� ������ �ӽ� �����
	int numberDigit; // �Է¹��� ���� ������ ��ȯ�� �ڸ���

	printf("������ �Է� : ");
	scanf("%d", &numInput);

	printf("\n������ �ڸ��� �Է� : ");
	scanf("%d", &digit);

	tempNumber = numInput;

	if (digit < 1) // ���� ������ �ڸ����� 0������ ��� ù��° �ڸ��� �����Ѵ�.
		digit = 1;

	numberDigit = PrintBits(tempNumber);

	if (digit > numberDigit)
		printf("\n�ڸ����� ��Ʈ�� �ʰ��Ͽ����ϴ�.");
	else
		printf("\n������ �ڸ��� ��Ʈ�� : %d", (tempNumber >> (digit - 1)) & 1);

	return 0;
}

int PrintBits(int number)
{
	int i = 1;
	int j = 1;

	if (number >= 0)
	{
		while (pow(2, i) <= number)
		{
			i++;
		}
	}
	else
	{
		i = 64; // ������ ��� ��Ʈ�� �ִ� 64�ڸ������� ����Ѵ�.
	}


	for (j = 1; j <= i; j++)
	{
		printf("%d", (number >> (i - j)) & 1);
		if ((i - j) % 4 == 0)
			printf(" ");
	}

	return i;
}