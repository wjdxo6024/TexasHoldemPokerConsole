#include <stdio.h>

int main()
{
	float d;
	double d1;
	double d2;

	d = 3.141592;
	d1 = 1234567890;
	d2 = 'c';

	printf("실수형 변수 d의 값은 %E\n", d);
	printf("실수형 변수 d1의 값은 %E\n", d1);
	printf("실수형 변수 d2의 값은 %E\n", d2);
	return 0;
}