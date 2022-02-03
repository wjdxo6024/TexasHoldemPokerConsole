#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int ComputeYear(int year)
{
	int result = 0;
	int i = 1970;
	for (i; i < year; i++)
	{
		if (ComputeLeapYear(i))
		{
			result += 60 * 60 * 24 * 366;
		}
		else
		{
			result += 60 * 60 * 24 * 365;
		}
	}

	return result;
}

int ComputeMonth(int month, int isLeapYear)
{
	int result = 0;
	for (int i = 1; i < month; i++)
	{
		if (i <= 7)
		{
			if (i == 2)
			{
				if (isLeapYear)
				{
					result += 60 * 60 * 24 * 29;
				}
				else
				{
					result += 60 * 60 * 24 * 28;
				}
			}
			else if (i % 2 == 0)
			{
				result += 60 * 60 * 24 * 30;
			}
			else
			{
				result += 60 * 60 * 24 * 31;
			}
		}
		else
		{
			if (i % 2 == 0)
			{
				result += 60 * 60 * 24 * 31;
			}
			else
			{
				result += 60 * 60 * 24 * 30;
			}
		}
	}

	return result;
}

int ComputeLeapYear(int year)
{
	int isLeapYear = 0;
	// ���� ���
	if ((year % 4 == 0) && (year % 100 == 0) && (year % 400 == 0)) // ���� �̴�.
	{
		isLeapYear = 1;
	}
	else if ((year % 4 == 0) && (year % 100 == 0)) // ����̴�.
	{
		isLeapYear = 0;
	}
	else if (year % 4 == 0) // �����̴�.
	{
		isLeapYear = 1;
	}
	else // ����̴�.
	{
		isLeapYear = 0;
	}

	return isLeapYear;
}

time_t ComputePurposeTime(int year, int month, int day)
{
	time_t result = 0;
	int isLeapYear = 0;

	isLeapYear = ComputeLeapYear(year);

	// �� ���
	result += ComputeYear(year);

	// �� ���
	result += ComputeMonth(month, isLeapYear);


	// �� ���
	result += (day - 1) * (60 * 60 * 24);
	return result;
}

void main()
{
	int Year, Month, Day;
	int AnniversaryDays = 0;
	time_t PurposeTime;
	struct tm* TimeInfo;
	
	printf("�� �� �� �Է� : ");
	scanf("%d %d %d", &Year, &Month, &Day);

	printf("����� �Է� : ");
	scanf("%d", &AnniversaryDays);

	if (AnniversaryDays > 1000)
		AnniversaryDays = 1000;
	else if (AnniversaryDays < -1000)
		AnniversaryDays = -1000;

	PurposeTime = ComputePurposeTime(Year, Month, Day);
	TimeInfo = localtime(&PurposeTime);

	TimeInfo->tm_mday += AnniversaryDays;
	mktime(TimeInfo);

	printf("%d�� %d�� %d�� ���� %d�� ��䳯¥�� %d�� %d�� %d�� �Դϴ�.\n",
		Year, Month, Day, AnniversaryDays, TimeInfo->tm_year + 1900, TimeInfo->tm_mon + 1, TimeInfo->tm_mday);
}