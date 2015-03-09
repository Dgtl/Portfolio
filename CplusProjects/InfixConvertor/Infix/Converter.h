#pragma once

#include "myStack.h"
#include <iostream>
#include <string>

using namespace std;


class Converter{

public:
	/*reads user infix expression.*/
	void getInfix(string s);

	/*prints user infix*/
	void showInfix();

	/*prints postfix conversion of user infix*/
	void showPostfix();

private:

	string _infix;
	string _postfix;

	/*called by showPostfix() to convert infix
	Initialize pfx to an empty expression and also initialize the stack.
	Get the next symbol, sym, from infx.
	If sym is an operand, append sym to pfx.
	If sym is (, push sym into the stack.
	If  sym is  ), pop and append all of the symbols from the stack until the most recent left parentheses. Pop and discard the left parentheses.
	If sym is an operator:
	Pop and append all of the operators from the stack to pfx that are above the most recent left parentheses and have precedence greater than or equal to sym.
	Push sym onto the stack.
	After processing infx, some operators might be left in the stack. Pop and append to pfx everything from the stack*/
	void ConvertToPostfix();

	/*called by ConvertToPostfix() to properly fill stack*/
	bool precedence(char greater, char lesser);
};