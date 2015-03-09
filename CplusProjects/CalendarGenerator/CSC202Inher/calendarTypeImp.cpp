#include "calendarType.h"

//defaults constructor to January 1, 1500
calendarType::calendarType()
{
	setMonth(1);
	setYear(1500);
}

//sets input month and year
calendarType::calendarType(int m, int y)
{
	setMonth(m);
	setYear(y);
}

void calendarType::setMonth(int m)
{
	firstDate.setMonth(m);
}

void calendarType::setYear(int y)
{
	firstDate.setYear(y);
}

int calendarType::getMonth()
{
	return firstDate.getMonth();
}

int calendarType::getYear()
{
	return firstDate.getYear();
}

void calendarType::printCalendar()
{
	printTitle();
	printDates();
}


//private
void calendarType::printTitle()
{
	firstDate.printLongMonthYear();

	cout << "\n";

	for (int i = 0; i != 8; i++)
	{
		string shortName = firstDay.weekDays[i].substr(0, 3);


		cout << "    " << shortName; //4 spaces
	}
}

void calendarType::printDates()
{

	int i = 0;
	dayType day = firstDayOfMonth();


	if (day.getDay() == "Sunday")
	{

		while (firstDate.getDay() < firstDate.getDaysInMonth())
		{
			i = 0;
			cout << "\n";


			while (i < 7)
			{
				if (firstDate.getDay() <= 9)
					cout << "    " << "  " << firstDate.getDay(); //4 spaces + 2 for the day letters
				else
					cout << "    " << " " << firstDate.getDay(); //4 spaces + 1 for two digit day


				if (firstDate.getDay() < firstDate.getDaysInMonth())
				{
					firstDate.incrementDate(1);
				}

				i++;
			}
		}
		cout << "\n\n";
	}


	if (day.getDay() == "Monday")

	{
		// day specific loop

		cout << "\n";

		for (int k = 0; k < 1; k++) //k boolean literal gets +1 per day of the week
		{
			cout << "    " << "   "; //to move one column right. Additional space in second quotes.
		}

		while (i < 6) //the literal is decremented as day of week moves further right in columns 
		{
			if (firstDate.getDay() <= 9)
				cout << "    " << "  " << firstDate.getDay(); //4 spaces + 2 for the day letters
			else
				cout << "    " << " " << firstDate.getDay(); //4 spaces + 1 for two digit day


			if (firstDate.getDay() < firstDate.getDaysInMonth())
			{
				firstDate.incrementDate(1);
			}

			i++;
		}

		//copypaste loop
		while (firstDate.getDay() < firstDate.getDaysInMonth())
		{
			i = 0;
			cout << "\n";


			while (i < 7)
			{
				if (firstDate.getDay() <= 9)
					cout << "    " << "  " << firstDate.getDay(); //4 spaces + 2 for the day letters
				else
					cout << "    " << " " << firstDate.getDay(); //4 spaces + 1 for two digit day


				if (firstDate.getDay() < firstDate.getDaysInMonth())
				{
					firstDate.incrementDate(1);
				}

				i++;
			}
		}
		cout << "\n\n";

	}

	if (day.getDay() == "Tuesday")

	{

		// day specific loop

		cout << "\n";

			for (int k = 0; k < 2; k++) //k boolean literal gets +1 per day of the week
			{
			cout << "    " << "   "; //to move one column right. Additional space in second quotes.
			}

		while (i < 5) //the literal is decremented as day of week moves further right in columns 
		{
			if (firstDate.getDay() <= 9)
				cout << "    " << "  " << firstDate.getDay(); //4 spaces + 2 for the day letters
			else
				cout << "    " << " " << firstDate.getDay(); //4 spaces + 1 for two digit day


			if (firstDate.getDay() < firstDate.getDaysInMonth())
			{
				firstDate.incrementDate(1);
			}

			i++;
		}

		//copypaste loop
		while (firstDate.getDay() < firstDate.getDaysInMonth())
		{
			i = 0;
			cout << "\n";


			while (i < 7)
			{
				if (firstDate.getDay() <= 9)
					cout << "    " << "  " << firstDate.getDay(); //4 spaces + 2 for the day letters
				else
					cout << "    " << " " << firstDate.getDay(); //4 spaces + 1 for two digit day


				if (firstDate.getDay() < firstDate.getDaysInMonth())
				{
					firstDate.incrementDate(1);
				}

				i++;
			}
		}
		cout << "\n\n";

	}

	if (day.getDay() == "Wednesday")

	{

		// day specific loop

		cout << "\n";

		for (int k = 0; k < 3; k++) //k boolean literal gets +1 per day of the week
		{
			cout << "    " << "   "; //to move one column right. Additional space in second quotes.
		}

		while (i < 4) //the literal is decremented as day of week moves further right in columns 
		{
			if (firstDate.getDay() <= 9)
				cout << "    " << "  " << firstDate.getDay(); //4 spaces + 2 for the day letters
			else
				cout << "    " << " " << firstDate.getDay(); //4 spaces + 1 for two digit day


			if (firstDate.getDay() < firstDate.getDaysInMonth())
			{
				firstDate.incrementDate(1);
			}

			i++;
		}

		//copypaste loop
		while (firstDate.getDay() < firstDate.getDaysInMonth())
		{
			i = 0;
			cout << "\n";


			while (i < 7)
			{
				if (firstDate.getDay() <= 9)
					cout << "    " << "  " << firstDate.getDay(); //4 spaces + 2 for the day letters
				else
					cout << "    " << " " << firstDate.getDay(); //4 spaces + 1 for two digit day


				if (firstDate.getDay() < firstDate.getDaysInMonth())
				{
					firstDate.incrementDate(1);
				}

				i++;
			}
		}
		cout << "\n\n";

	}

	if (day.getDay() == "Thursday")

	{

		// day specific loop

		cout << "\n";

		for (int k = 0; k < 4; k++) //k boolean literal gets +1 per day of the week
		{
			cout << "    " << "   "; //to move one column right. Additional space in second quotes.
		}

		while (i < 3) //the literal is decremented as day of week moves further right in columns 
		{
			if (firstDate.getDay() <= 9)
				cout << "    " << "  " << firstDate.getDay(); //4 spaces + 2 for the day letters
			else
				cout << "    " << " " << firstDate.getDay(); //4 spaces + 1 for two digit day


			if (firstDate.getDay() < firstDate.getDaysInMonth())
			{
				firstDate.incrementDate(1);
			}

			i++;
		}

		//copypaste loop
		while (firstDate.getDay() < firstDate.getDaysInMonth())
		{
			i = 0;
			cout << "\n";


			while (i < 7)
			{
				if (firstDate.getDay() <= 9)
					cout << "    " << "  " << firstDate.getDay(); //4 spaces + 2 for the day letters
				else
					cout << "    " << " " << firstDate.getDay(); //4 spaces + 1 for two digit day


				if (firstDate.getDay() < firstDate.getDaysInMonth())
				{
					firstDate.incrementDate(1);
				}

				i++;
			}
		}
		cout << "\n\n";

	}

	if (day.getDay() == "Friday")

	{

		// day specific loop

		cout << "\n";

		for (int k = 0; k < 5; k++) //k boolean literal gets +1 per day of the week
		{
			cout << "    " << "   "; //to move one column right. Additional space in second quotes.
		}

		while (i < 2) //the literal is decremented as day of week moves further right in columns 
		{
			if (firstDate.getDay() <= 9)
				cout << "    " << "  " << firstDate.getDay(); //4 spaces + 2 for the day letters
			else
				cout << "    " << " " << firstDate.getDay(); //4 spaces + 1 for two digit day


			if (firstDate.getDay() < firstDate.getDaysInMonth())
			{
				firstDate.incrementDate(1);
			}

			i++;
		}

		//copypaste loop
		while (firstDate.getDay() < firstDate.getDaysInMonth())
		{
			i = 0;
			cout << "\n";


			while (i < 7)
			{
				if (firstDate.getDay() <= 9)
					cout << "    " << "  " << firstDate.getDay(); //4 spaces + 2 for the day letters
				else
					cout << "    " << " " << firstDate.getDay(); //4 spaces + 1 for two digit day


				if (firstDate.getDay() < firstDate.getDaysInMonth())
				{
					firstDate.incrementDate(1);
				}

				i++;
			}
		}
		cout << "\n\n";

	}

	if (day.getDay() == "Saturday")

	{

		// day specific loop

		cout << "\n";

		for (int k = 0; k < 6; k++) //k boolean literal gets +1 per day of the week
		{
			cout << "    " << "   "; //to move one column right. Additional space in second quotes.
		}

		while (i < 1) //the literal is decremented as day of week moves further right in columns 
		{
			if (firstDate.getDay() <= 9)
				cout << "    " << "  " << firstDate.getDay(); //4 spaces + 2 for the day letters
			else
				cout << "    " << " " << firstDate.getDay(); //4 spaces + 1 for two digit day


			if (firstDate.getDay() < firstDate.getDaysInMonth())
			{
				firstDate.incrementDate(1);
			}

			i++;
		}

		//copypaste loop
		while (firstDate.getDay() < firstDate.getDaysInMonth())
		{
			i = 0;
			cout << "\n";


			while (i < 7)
			{
				if (firstDate.getDay() <= 9)
					cout << "    " << "  " << firstDate.getDay(); //4 spaces + 2 for the day letters
				else
					cout << "    " << " " << firstDate.getDay(); //4 spaces + 1 for two digit day


				if (firstDate.getDay() < firstDate.getDaysInMonth())
				{
					firstDate.incrementDate(1);
				}

				i++;
			}
		}
		cout << "\n\n";

	}

}

dayType calendarType::firstDayOfMonth()
{
	dayType day;
	int countResult;
	int y = getYear();
	int m = getMonth();
	int d = 1;

	if (firstDate.getMonth() == 1 && firstDate.getYear() == 1500)
	{
		day.setDay(firstDay.weekDays[1]);
	}
	else
	{
		static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
		y -= m < 3;
		countResult = (y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7;

		day.setDay(firstDay.weekDays[countResult]);
	}

	return day;
}
