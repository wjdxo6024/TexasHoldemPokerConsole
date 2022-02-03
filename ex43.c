#include <stdio.h>

struct tagSungJuk
{
	int kor;
	int eng;
	int math;
};

int main()
{
	struct tagSungJuk SJ;

	SJ.kor = 100;
	SJ.eng = 95;
	SJ.math = 99;

	printf("รัวี = %d", SJ.kor + SJ.eng + SJ.math);
}