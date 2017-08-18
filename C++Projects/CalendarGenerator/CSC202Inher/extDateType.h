
#ifndef extDateType_H
#define extDateType_H
 
#include <string>

#include "dateType.h" 
  
using namespace std; 

class extDateType: public dateType
{
public:
    static string eMonths[12];
    void printLongDate();
    void setDate(int, int, int);
    void setMonth(int m);

    void printLongMonthYear();

    extDateType();
    extDateType(int, int, int);

private:
    string eMonth;
};

#endif