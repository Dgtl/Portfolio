#include "Converter.h"

int main(){

	Converter* tc = new Converter();
	string e1 = "A+B-C";
	string e2 = "(A+B)*C";
	string e3 = "(A+B)*(C-D)";
	string e4 = "A+((B+C)*(E-F)-G)/(H-I)";
	string e5 = "A+B*(C+D)-E/F*G+H";

	tc->getInfix(e1); // example 1
	tc->showInfix();
	tc->showPostfix();

	tc->getInfix(e2); // example 2
	tc->showInfix();
	tc->showPostfix();

	tc->getInfix(e3); // example 3
	tc->showInfix();
	tc->showPostfix();

	tc->getInfix(e4); // example 4
	tc->showInfix();
	tc->showPostfix();

	tc->getInfix(e5); // example 5
	tc->showInfix();
	tc->showPostfix();

	system("pause");

	return 0;
}