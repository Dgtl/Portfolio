#include "fractionType.h"


using namespace std;

int main(){

	//constructor test
	fractionType ob1 = fractionType(1, 2);
	fractionType ob2 = fractionType(2, 2);
	fractionType result;

	//addition test
	result = ob1 + ob2;
	//print test
	cout << ob1 << " + " << ob2 << " = " << result << endl;

	//subtract test
	result = ob1 - ob2;
	cout << ob1 << " - " << ob2 << " = " << result << endl;

	//muliply test
	result = ob1 * ob2;
	cout << ob1 << " * " << ob2 << " = " << result << endl;

	//divide test
	result = ob1 / ob2;
	cout << ob1 << " / " << ob2 << " = " << result << endl;

	//divide assert test commented out so program doesn't display error when you're grading :D
//	fractionType ob3 = fractionType(0, 1);
//	result = ob1 / ob3;

	ob1.setFraction(1, 1);
	ob2.setFraction(1, 1);

	//boolean tests
	if (ob1 == ob2)
		cout << ob1 << " is equal to " << ob2 << endl;
	else
		cout << ob1 << " is not equal to " << ob2 << endl;

	if (ob1 != ob2)
		cout << ob1 << " is not equal to " << ob2 << endl;
	else
		cout << ob1 << " is equal to " << ob2 << endl;

	if (ob1 <= ob2)
		cout << ob1 << " is less than or equal to " << ob2 << endl;
	else
		cout << ob1 << " is not less than or equal to " << ob2 << endl;

	if (ob1 < ob2)
		cout << ob1 << " is less than " << ob2 << endl;
	else
		cout << ob1 << " is not less than " << ob2 << endl;

	if (ob1 >= ob2)
		cout << ob1 << " is greater than or equal to " << ob2 << endl;
	else
		cout << ob1 << " is not greater than or equal to " << ob2 << endl;

	if (ob1 > ob2)
		cout << ob1 << " is greater than " << ob2 << endl;
	else
		cout << ob1 << " is not greater than " << ob2 << endl;

	//instream test
	cin >> result;
	cout << "you entered: " << result << endl;


	system("pause");

	return 0;
}