#include "Converter.h"

void Converter::getInfix(string s){

	//cout << "Please enter expression: ";

	//cin >> _infix;

	//cout << endl;

	_infix = s;

}

void Converter::showInfix(){

	cout << "Infix Expression: " << _infix << endl;

}

void Converter::showPostfix(){
	ConvertToPostfix();
	cout << "Postfix Expression: " << _postfix << endl << endl;

}

void Converter::ConvertToPostfix(){

	char sym = NULL;
	_postfix = "";
	stackType<char> stack;
	stack.initializeStack();
	
	for (int i = 0; i < _infix.length(); i++){

		sym = _infix.at(i);

		if (sym == '('){
			
			stack.push(sym);

		}
		else if (sym == ')'){
			
			//never push ')'
			if (!stack.isEmptyStack()){

				while (stack.top() != '('){

					_postfix += stack.top(); //loop to pop append all symbols until left parenth
					stack.pop();

					if (stack.isEmptyStack())
						break;

				}
			}

			stack.pop(); //discard '('
			
		}
		else if (sym == '+' || sym == '-' || sym == '*' || sym == '/'){

			if (!stack.isEmptyStack()){

				while (stack.top() != '('){

					if (precedence(stack.top(), sym)){
						_postfix += stack.top();
						stack.pop();
					}

					if (stack.isEmptyStack())
						break;

					if (!precedence(stack.top(), sym))
						break;
				}
			}

			stack.push(sym);

		}
		else{ //must be operand at this point

			_postfix += sym;

		}
	}

	while (!stack.isEmptyStack()){ //append left over operators
		_postfix += stack.top();
		stack.pop();

		if (stack.isEmptyStack())
			break;
	}
}

bool Converter::precedence(char greater, char lesser){

	int c1 = 0;
	int c2 = 0;

	if (greater == '*' || greater == '/'){
		c1 = 1;
	}
	if (greater == '+' || greater == '-'){
		c1 = 0;
	}

	if (lesser == '*' || lesser == '/'){
		c2 = 1;
	}
	if (lesser == '+' || lesser == '-'){
		c2 = 0;
	}

	return (c1 >= c2);
}