#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

void main()
{
	int i;
	char *pmem;

	pmem = malloc(100);

	if (pmem == NULL)
	{
		puts("메모리를 할당할 수 없습니다.");
	}
	else
	{
		printf("할당된 메모리 길이는 %d바이트입니다.\n", _msize(pmem));

		pmem = realloc(pmem, 200);

		if (pmem == NULL)
		{
			puts("메모리를 할당할 수 없습니다.");
		}
		else
		{
			printf("재할당된 메모리 길이는 %d바이트입니다.\n", _msize(pmem));

		}
		free(pmem);
	}
}