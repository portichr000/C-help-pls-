/********************************************************************************************
 **	Project: Stack
 **  Programmer: Christain Portillo
 **  Course:		cs2420
 **	Section:	001
 **	Assignment: 3
 **	Data:		July 1st, 2019
 **
 **	I Christain Portilllo have not used any code other than my own (or that in the textbook)
 **	for this project. I understand that any violation of this disclaimer will result in a 0 for the project.
 **
 ***********************************************************************************************/
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stack>
#include <cctype>
#include <cstdlib>

using namespace std;

int EvaluatePostfix(string);

bool OperandCheck(char yuh) {
	switch (yuh) {
	case '+':

		return true;

	case '-':
		return true;

	case '*':
		return true;
	case '/':
		return true;

	default:
		return false;
		break;
	}

}

int OperandOrder(char nah) {
	switch (nah) {
	case '+':

		return 3;

	case '-':
		return 4;

	case '*':
		return 1;
	case '/':
		return 2;

	default:
		return false;
		break;
	}
}

bool NumCompare(char topStack, char charNum) {
	int tmpStack, tmpNum;

	tmpStack = OperandOrder(topStack);
	tmpNum = OperandOrder(charNum);
	if (tmpNum < tmpStack) {
		return false;
	}
	else {
		return true;
	}
}

string InToPostfix(string infix);

//int EvaluatePostfix(string postfix);

int main() {
	const char dataFileName[] = "data.txt";

	ifstream fileData;
	fileData.open(dataFileName);
	if (fileData.good() == false) {
		cout << "ERROR: can't open data file: " << dataFileName << endl;

		//wait for the user to press enter to quit
		cout << endl << "Press the [Enter] key to quit...";
		cin.get();
		return -1;
	}

	while (!fileData.eof()) {
		string infixEquation;
		getline(fileData, infixEquation, '\n');
		if (infixEquation != "") {
			string postfix = InToPostfix(infixEquation + '@');
			double answer = EvaluatePostfix(postfix);

			//
			cout << "infix: " << infixEquation << endl;
			cout << "postfix: " << postfix << endl;
			cout << "answer: " << answer << endl;
			cout << endl;
		}

	}
}

string InToPostfix(string infix) {
	string print = "";

	stack <char> S;
	unsigned int i = 0;
	char character = infix[i];

	do {

		if (character == '(') {

			S.push(character);
		}
		else if (character == ' ') {

		}
		else if (isdigit(character)) {
			//Read the operand(or number) and write it to the output
			print = print + character + ' ';
		}
		else if (OperandCheck(character)) {
			//stack's top is not left parenthesis AND
			//stack's top is an operation with  equal or higher precedence
			while (S.empty() == false && S.top() != '(' && NumCompare(S.top(), character)) {

				//print the stack's top
				print = print + S.top() + ' ';
				//pop the stack's top

				S.pop();


			}
			//push the next operation symbol onto the stack
			S.push(character);
		}
		else {
			//readand discard the next input symbol(should be a right parenthesis)
			if (character == ')') {
				//print the top operationand pop it
				print = print + S.top() + ' ';
				S.pop();
			}
			//stack's top is not a left parenthesis
			while (S.top() != '(') {
				//print next symbol on stack and pop stack
				print = print + S.top() + ' ';
				S.pop();
			}
			//pop and discard the last left parenthesis
			S.pop();
		}
		character = infix[++i];
	} while (character != '@');
	{
		while (S.empty() == false) {
			print = print + S.top();
			S.pop();
		}
	}

	return print;
}

int EvaluatePostfix(string postfix) {
	//1. Initialize a stack of doubles
	stack<double> dStack;
	unsigned int i = 0;
	do {
		char character = postfix[i];
		if (character == ' ') {
			i++;
			continue;
		}
		//next input is a number
		if (isdigit(character)) {
			//Read the next inputand push it onto the stack
			dStack.push(character - '0');

		}
		else {
			//Read the next character, which is an operator symbol
			//Use top and pop to get the two numbers off the top of the stack
			double a = dStack.top();
			dStack.pop();
			double b = dStack.top();
			dStack.pop();
			double c;
			//Combine these two numbers with the operation(using the second number popped as the left operand)
			if (character == '+') {
				c = b + a;
			}
			else if (character == '-') {
				c = b - a;
			}
			else if (character == '*') {
				c = a * b;
			}
			else {
				c = b / a;
			}
			//Push the result onto the stack
			dStack.push(c);

		}

		i++;
	} while (i < postfix.length());
	//3. At this point, the stack contains one number which is the result of the expression
	double answer = dStack.top();
	return answer;
}