#include <stdio.h>

void main()
{
	int count;
	int tmp;
	int total = 0;

	for (count = 1; count <= 3; count++)
	{
		printf("%d 번째 정수값을 입력한 후 Enter키를 누르세요.\n", count);

		scanf("%d", &tmp);

		total += tmp;

		printf("입력 값 = %d, 총 합 = %d\n", tmp, total);
	}

	printf("읽은 정수의 총 합은 %d입니다.\n", total);
}