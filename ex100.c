#include <stdio.h>
#include <string.h>

struct tagM1
{
	int x;
	int y;
	char buffer[30];
};

void main()
{
	struct tagM1 x1, x2;

	x1.x = 5;
	x1.y = 10;
	strcpy(x1.buffer, "memory copy");

	memcpy(&x2, &x1, sizeof(x1));

	puts(x2.buffer);
}