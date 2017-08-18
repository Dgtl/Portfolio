#include "fractionType.h"
#include <assert.h>

fractionType::fractionType(){

	this->numerator = 0;
	this->denominator = 0;

}

fractionType::fractionType(int num, int denom){

	this->numerator = num;
	this->denominator = denom;

}

void fractionType::setFraction(int num, int denom){
	this->numerator = num;
	this->denominator = denom;
}

fractionType fractionType::operator +(fractionType n){

	//int variables to hold fraction components
	int a = this->numerator;
	int b = this->denominator;
	int c = n.numerator;
	int d = n.denominator;

	//returnable type
	fractionType ret;

	//given formula

	ret.setFraction( (a * d + b * c), (b * d) );
	
	return ret;

}

fractionType fractionType::operator-(fractionType n){

	//int variables to hold fraction components
	int a = this->numerator;
	int b = this->denominator;
	int c = n.numerator;
	int d = n.denominator;

	//returnable type
	fractionType ret;

	//given formula

	ret.setFraction( (a * d - b * c), (b * d) );

	return ret;

}

fractionType fractionType::operator*(fractionType n){

	//int variables to hold fraction components
	int a = this->numerator;
	int b = this->denominator;
	int c = n.numerator;
	int d = n.denominator;

	//returnable type
	fractionType ret;

	//given formula

	ret.setFraction( (a * c), (b * d) );

	return ret;

}
fractionType fractionType::operator/(fractionType n){

	//int variables to hold fraction components
	int a = this->numerator;
	int b = this->denominator;
	int c = n.numerator;
	int d = n.denominator;

	//returnable type
	fractionType ret;

	//given formula
	assert(c != 0, "Can't divide by zero" );
	ret.setFraction( (a * d), (b * c) );

	return ret;

}
bool fractionType::operator==(fractionType n){

	if (this->numerator == n.numerator && this->denominator == n.numerator)
		return true;
	else
		return false;

}
bool fractionType::operator!=(fractionType n){

	if (this->numerator != n.numerator || this->denominator != n.numerator)
		return true;
	else
		return false;

}
bool fractionType::operator<=(fractionType n){

	//int variables to hold fraction components
	double a = this->numerator;
	double b = this->denominator;
	double c = n.numerator;
	double d = n.denominator;

	if (a/b <= c/d)
		return true;
	else
		return false;

}
bool fractionType::operator>=(fractionType n){

	//int variables to hold fraction components
	double a = this->numerator;
	double b = this->denominator;
	double c = n.numerator;
	double d = n.denominator;

	if (a / b >= c / d)
		return true;
	else
		return false;

}
bool fractionType::operator>(fractionType n){

	//int variables to hold fraction components
	double a = this->numerator;
	double b = this->denominator;
	double c = n.numerator;
	double d = n.denominator;

	if (a / b > c / d)
		return true;
	else
		return false;

}
bool fractionType::operator<(fractionType n){

	//int variables to hold fraction components
	double a = this->numerator;
	double b = this->denominator;
	double c = n.numerator;
	double d = n.denominator;

	if (a / b < c / d)
		return true;
	else
		return false;

}

//non-member overloads
std::ostream& operator<<(std::ostream& os, const fractionType obj){

	os << obj.numerator << "/" << obj.denominator;

	return os;

}

std::istream& operator>>(std::istream& is, fractionType& obj){

	std::cout << "Please enter Numerator: ";
	is >> obj.numerator;
	std::cout << "Please enter Denominator: ";
	is >> obj.denominator;
	std::cout << std::endl;

	return is;
}

