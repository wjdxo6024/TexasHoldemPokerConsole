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
		puts("�޸𸮸� �Ҵ��� �� �����ϴ�.");
	}
	else
	{
		printf("�Ҵ�� �޸� ���̴� %d����Ʈ�Դϴ�.\n", _msize(pmem));

		pmem = realloc(pmem, 200);

		if (pmem == NULL)
		{
			puts("�޸𸮸� �Ҵ��� �� �����ϴ�.");
		}
		else
		{
			printf("���Ҵ�� �޸� ���̴� %d����Ʈ�Դϴ�.\n", _msize(pmem));

		}
		free(pmem);
	}
}