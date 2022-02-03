#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#define MEMORY "MEMORY"

void main()
{
	char *pmem;

	pmem = malloc(100);

	if (pmem == NULL)
	{
		puts("메모리를 할당할 수 없습니다.");
	}
	else
	{
		strcpy(pmem, MEMORY);
		puts(pmem);
		free(pmem);
	}
}