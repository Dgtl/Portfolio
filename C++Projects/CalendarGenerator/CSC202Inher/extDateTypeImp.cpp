
#include <iostream>
#include <string>
#include "dateType.h"
#include "extDateType.h"
 
using namespace std;
  
string extDateType::eMonths[] = {"January", "February", "March", "April", 
                    "May", "June", "July", "August", 
                    "September", "October", "November", "December"};

void extDateType::printLongDate() 
{ 
    cout << eMonth << " " << getDay() << ", " << getYear();
}

void extDateType::printLongMonthYear()
{
    cout << eMonth << " " << getYear();
}

void extDateType::setDate(int m, int d, int y)
{
    dateType::setDate(m, d, y);

    eMonth = eMonths[m - 1];
}

void extDateType::setMonth(int m)
{
    dateType::setMonth(m);
    eMonth = eMonths[m - 1];
}

extDateType::extDateType()
{
    eMonth = "January";
}

extDateType::extDateType(int m, int n, int d)
            : dateType(m, n, d)
{
    eMonth = eMonths[m - 1];
}


