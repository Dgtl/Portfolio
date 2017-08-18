
#ifndef dateType_H
#define dateType_H
   
class dateType 
{
public: 
	void setDate(int, int, int);
	void setMonth(int);
	void setDay(int);
	void setYear(int);
	
	void print() const;

	int numberOfDaysPassed();	

	int numberOfDaysLeft();

	void incrementDate(int nDays);

	int getMonth() const;
	int getDay() const;
	int getYear() const;

	int getDaysInMonth();

	bool isLeapYear();

	dateType(int = 1, int = 1, int = 1900);

private:
	int dMonth;
	int dDay;
	int dYear;
};

#endif