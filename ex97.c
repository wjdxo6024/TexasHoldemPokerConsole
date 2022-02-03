#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

void main()
{
	char *pmem;

	printf("sizeof(int)의 길이는 %d입니다.\n", sizeof(int));

	pmem = calloc(100, sizeof(int));

	if (pmem == NULL)
	{
		puts("메모리를 할당할 수 없습니다.");
	}
	else
	{
		puts("정수형 변수 100개를 저장할 버퍼가 할당되었습니다.");

		free(pmem);
	}
}