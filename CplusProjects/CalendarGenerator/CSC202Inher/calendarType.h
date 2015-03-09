/*
 * This class will create a calendar printout for any month and year after
 * January 1, 1500.
 */
#ifndef calendarType_h
#define calendarType_h
 
#include "dateType.h" 
#include "extdateType.h"
#include "dayType.h"
#include <iostream>
  
class calendarType
{
public:
	void setMonth(int m);
	void setYear(int y);

	int getMonth();
	int getYear();

	void printCalendar();

	calendarType();
	calendarType(int m, int y);

private:

	// Note that member functions can also be private which means only functions
	// within this class can call them.
	dayType firstDayOfMonth();   
	void printTitle();
	void printDates();

	// Composition rather than inheritance, although firstDate is a derived class
	// from the base class dateType.
	extDateType firstDate;
	dayType  firstDay;

};


#endif