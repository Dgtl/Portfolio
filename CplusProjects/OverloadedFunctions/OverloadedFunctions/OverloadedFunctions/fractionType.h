#pragma once

/* John Jervis */

#include <iostream>

class fractionType{

	//non-member overloads
	friend std::ostream& operator<<(std::ostream& os, const fractionType obj);

	friend std::istream& operator>>(std::istream& is, fractionType& obj);

public:

	//deafult constructor
	fractionType();

	//constructor
	fractionType(int num, int denom);

	void setFraction(int num, int denom);

	fractionType fractionType::operator+(fractionType n);
	fractionType fractionType::operator-(fractionType n);
	fractionType fractionType::operator*(fractionType n);
	fractionType fractionType::operator/(fractionType n);
	bool fractionType::operator==(fractionType n);
	bool fractionType::operator!=(fractionType n);
	bool fractionType::operator<=(fractionType n);
	bool fractionType::operator>=(fractionType n);
	bool fractionType::operator>(fractionType n);
	bool fractionType::operator<(fractionType n);

private:

	int numerator;
	int denominator;

};