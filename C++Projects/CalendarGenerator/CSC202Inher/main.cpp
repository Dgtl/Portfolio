#include "calendarType.h"
#include <iostream>

using namespace std;

int main()
{
	int month;
	int year;
	int SENTINEL = -9999;
	int userSent = 0;

	while (userSent != SENTINEL)
	{

		cout << "Please enter a month: ";
		cin >> month;
		cout << "\n";

		cout << "Please enter a year: ";
		cin >> year;
		cout << "\n";

		calendarType cal(month, year);  //for 2014, first day for each month, 
		//6 is sunday 
		//9 is monday 
		//4 tuesday 
		//10 wednesday 
		//5 is thursday 
		//8 is friday 
		//11 is saturday

		cal.printCalendar();

		cout << "If you would like to continue, type 0 and hit enter. " << "\n" << "If you would like to quit, type -9999 and hit enter. ";
		cin >> userSent;
		cout << "\n";

	}

	system("pause");

	return 0;
}