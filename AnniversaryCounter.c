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
	// 윤년 계산
	if ((year % 4 == 0) && (year % 100 == 0) && (year % 400 == 0)) // 윤년 이다.
	{
		isLeapYear = 1;
	}
	else if ((year % 4 == 0) && (year % 100 == 0)) // 평년이다.
	{
		isLeapYear = 0;
	}
	else if (year % 4 == 0) // 윤년이다.
	{
		isLeapYear = 1;
	}
	else // 평년이다.
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

	// 년 계산
	result += ComputeYear(year);

	// 월 계산
	result += ComputeMonth(month, isLeapYear);


	// 일 계산
	result += (day - 1) * (60 * 60 * 24);
	return result;
}

void main()
{
	int Year, Month, Day;
	int AnniversaryDays = 0;
	time_t PurposeTime;
	struct tm* TimeInfo;
	
	printf("년 월 일 입력 : ");
	scanf("%d %d %d", &Year, &Month, &Day);

	printf("기념일 입력 : ");
	scanf("%d", &AnniversaryDays);

	if (AnniversaryDays > 1000)
		AnniversaryDays = 1000;
	else if (AnniversaryDays < -1000)
		AnniversaryDays = -1000;

	PurposeTime = ComputePurposeTime(Year, Month, Day);
	TimeInfo = localtime(&PurposeTime);

	TimeInfo->tm_mday += AnniversaryDays;
	mktime(TimeInfo);

	printf("%d년 %d월 %d일 기준 %d일 기념날짜는 %d년 %d월 %d일 입니다.\n",
		Year, Month, Day, AnniversaryDays, TimeInfo->tm_year + 1900, TimeInfo->tm_mon + 1, TimeInfo->tm_mday);
}