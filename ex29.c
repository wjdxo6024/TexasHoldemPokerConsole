#include <stdio.h>

int main()
{
	unsigned char ch = 255, mask = 0x7F;

	printf("%d\n", ch);	// 255
	printf("%d\n", ch & mask); // 127
	printf("%d\n", (char)~ch); // 0
	printf("%d\n", ch ^ ch); // 0
	printf("%d\n", ch >> 1); // 127
	printf("%d\n", mask << 1); // 254
	return 0;
}