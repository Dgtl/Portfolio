  
#include <iostream>
#include "dateType.h"
  
using namespace std;

void dateType::setDate(int month, int day, int year)
{
	if (year >= 1)
		dYear = year;
	else 
		dYear = 1900;
	 
	if (1 <= month && month <= 12)
		dMonth = month;
	else
		dMonth = 1;

	switch (dMonth)
	{
	case 1: 
	case 3: 
	case 5: 
	case 7:
	case 8: 
	case 10: 
	case 12: 
		if (1 <= day && day <= 31)
			dDay = day;
		else
			dDay = 1;
			break;
	case 4: 
	case 6: 
	case 9: 
	case 11: 
		if (1 <= day && day <= 30)
			dDay = day;
		else
			dDay = 1;
			break;
	case 2: 
		if (isLeapYear())
		{
			if (1 <= day && day <= 29)
				dDay = day;
			else
				dDay = 1;
		}
		else
		{
			if (1 <= day && day <= 28)
				dDay = day;
			else
			dDay = 1;
		}
	}
}

void dateType::setMonth(int  m)
{
	dMonth = m;
}

void dateType::setDay(int d)
{
	dDay = d;
}

void dateType::setYear(int y)
{
	dYear = y;
}


void dateType::print() const
{
	cout << dMonth << "-" << dDay << "-" << dYear;
}

int dateType::getMonth()  const
{
	return dMonth;
}

int dateType::getDay()  const
{
	return dDay;
}

int dateType::getYear()  const
{
	return dYear;
}

int dateType::getDaysInMonth()
{
	int noOfDays;

	switch (dMonth)
	{
	case 1: 
	case 3: 
	case 5: 
	case 7: 
	case 8: 
	case 10: 
	case 12: 
		noOfDays = 31;
		break;
	case 4: 
	case 6: 
	case 9: 
	case 11:  
		noOfDays = 30;
		break;
	case 2: 
		if (isLeapYear())
			noOfDays = 29;
		else
			noOfDays = 28;
	}

	return noOfDays;
}

bool dateType::isLeapYear()
{
	if (((dYear % 4 == 0) && (dYear % 100 != 0)) || dYear % 400 == 0)
		return true;
	else
		return false;
}

dateType::dateType(int month, int day, int year) 
{ 
	setDate(month, day, year);
}

int dateType::numberOfDaysPassed()
{
	int monthArr[13] = {0, 31, 28, 31, 30, 31, 30, 
						31, 31, 30, 31, 30, 31};

	int sumDays = 0;
	int i;

	for (i = 1; i < dMonth; i++)
		sumDays = sumDays + monthArr[i];

	if (isLeapYear() && dMonth > 2)
		sumDays = sumDays + dDay + 1;
	else
		sumDays = sumDays + dDay;

	return sumDays;
}

int dateType::numberOfDaysLeft()
{
	if (isLeapYear())
		return 366 - numberOfDaysPassed();
	else
		return 365 - numberOfDaysPassed();
}

void dateType::incrementDate(int nDays)
{
	int monthArr[13] = {0, 31, 28, 31, 30, 31, 30, 
					   31, 31, 30, 31, 30, 31};
	int daysLeftInMonth;

	daysLeftInMonth = monthArr[dMonth] - dDay;

	if (daysLeftInMonth >= nDays)
		dDay = dDay + nDays;
	else
	{
		dDay = 1;
		dMonth++;
		nDays = nDays - (daysLeftInMonth + 1);

		while (nDays > 0)
			if (nDays >= monthArr[dMonth])
			{
				nDays = nDays - monthArr[dMonth];

				if ((dMonth == 2) && isLeapYear())
					nDays--;
			   
				dMonth++;
				if (dMonth > 12)
				{
					dMonth = 1;
					dYear++;
				}

			}
			else
			{
				dDay = dDay+nDays;
				nDays = 0;
			}
	}
}

