#include <stdio.h>
#include <stdlib.h>

void main()
{
	double value;
	char *pstr;
	int dec, sign;

	value = 3.1415926535;
	pstr = fcvt(value, 6, &dec, &sign);

	printf("��ȯ�� ���ڿ��� %s�Դϴ�.\n", pstr);
	printf("�Ҽ����� ��ġ�� %d, ��ȣ�� %d�Դϴ�.\n", dec, sign);

	value = -3.1415926535;
	pstr = fcvt(value, 8, &dec, &sign);

	printf("��ȯ�� ���ڿ��� %s�Դϴ�.\n", pstr);
	printf("�Ҽ����� ��ġ�� %d, ��ȣ�� %d�Դϴ�.\n", dec, sign);

}