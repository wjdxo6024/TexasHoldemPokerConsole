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
		puts("�޸𸮸� �Ҵ��� �� �����ϴ�.");
	}
	else
	{
		strcpy(pmem, MEMORY);
		puts(pmem);
		free(pmem);
	}
}