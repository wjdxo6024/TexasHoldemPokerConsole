#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

int PrintBits(int number);

int main()
{
	int numInput; // 입력받을 정수
	int digit; // 검출하고자 하는 자릿수
	int tempNumber; // 입력받은 정수의 임시 저장소
	int numberDigit; // 입력받은 값의 이진수 변환시 자릿수

	printf("정수를 입력 : ");
	scanf("%d", &numInput);

	printf("\n검출할 자릿수 입력 : ");
	scanf("%d", &digit);

	tempNumber = numInput;

	if (digit < 1) // 만약 검출할 자릿수가 0이하일 경우 첫번째 자리를 검출한다.
		digit = 1;

	numberDigit = PrintBits(tempNumber);

	if (digit > numberDigit)
		printf("\n자릿값이 비트를 초과하였습니다.");
	else
		printf("\n검출한 자리의 비트값 : %d", (tempNumber >> (digit - 1)) & 1);

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
		i = 64; // 음수일 경우 비트를 최대 64자리까지만 출력한다.
	}


	for (j = 1; j <= i; j++)
	{
		printf("%d", (number >> (i - j)) & 1);
		if ((i - j) % 4 == 0)
			printf(" ");
	}

	return i;
}