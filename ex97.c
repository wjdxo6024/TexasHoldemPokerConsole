#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

void main()
{
	char *pmem;

	printf("sizeof(int)�� ���̴� %d�Դϴ�.\n", sizeof(int));

	pmem = calloc(100, sizeof(int));

	if (pmem == NULL)
	{
		puts("�޸𸮸� �Ҵ��� �� �����ϴ�.");
	}
	else
	{
		puts("������ ���� 100���� ������ ���۰� �Ҵ�Ǿ����ϴ�.");

		free(pmem);
	}
}