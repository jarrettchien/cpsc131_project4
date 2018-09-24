#include "ExpressionConverter.h"
#include <stack>
#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <sstream>
#include <algorithm>
#include <stdlib.h> 

// Write all your functions here
ArithNode::ArithNode()
{
	// Default constructor for ArithNode
}

bool HigherPrecedence(char leftOperator, char rightOperator);
string Infix2RPN(string infix_)
//Used as reference for code:http://faculty.cs.niu.edu/~hutchins/csci241/eval.htm
{
	string temp;
	string token;
	stack<char> operatorStack;
	stack<char> operandStack;
	string str = infix_;

	for (int i = 0; i < str.length(); i++)
	{

		if (isdigit(str[i]))
			operandStack.push(str[i]);
		// If str[i] is a number, it is an operand and we push it to the corresponding stack
		if (str[i] == '(')
		{
			operatorStack.push(str[i]);
			// Push left parenthesis onto the stack of operators
		}
		//Check
		if (str[i] == ')')
		{

			while (!operatorStack.empty() && operatorStack.top() != '(')
			{
				// If we have a right parenthesis, the stack is not empty, and the top is not a left parenthesis
				// We add a space for delimiter purposes; then, move the top of the operator stack onto operand stack
				operandStack.push(' ');
				operandStack.push(operatorStack.top());
				// Remove top of operator stack after copying it to operator stack
				operatorStack.pop();
			}
			/*temp = operatorStack.top();

			cout << "remove to other stack: " << temp << endl;*/
			operatorStack.pop();
		}
		//Check
		if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
		{
			// If str[i] is an operator and the operator stack is empty/top is (
			if (operatorStack.empty() || operatorStack.top() == '(')
			{
				// Add space for delimiter and push operator to operator stack
				operandStack.push(' ');
				operatorStack.push(str[i]);
				/*cout << "Pushed: " << str[i] << endl;*/
			}
			else
			{
				// Otherwise, if we have an operator while stack does not have a ( on top, we check the precedence of operator
				while (!operatorStack.empty() && operatorStack.top() != '(' && HigherPrecedence(operatorStack.top(), str[i]))
				{
					/*temp = operatorStack.top();
					cout << "Pushes top operator to operand: then pop " << temp << endl;*/
					// We copy from operator to operand stack with a delimiter and pop top of operator stack
					operandStack.push(operatorStack.top());
					operandStack.push(' ');
					operatorStack.pop();
				}
				// Once top of operator stack becomes (, we reach this point
				// Add a delimiter to operand stack and push the operator onto the operator stack
				operandStack.push(' ');
				operatorStack.push(str[i]);

			}
		}
	}

	while (!operatorStack.empty())
	{
		// If anything remains in operator stack after iterating through the string
		// Add delimiter and push to operand stack while popping operator stack
		operandStack.push(' ');
		operandStack.push(operatorStack.top());
		operatorStack.pop();
	}
	while (!operandStack.empty())
	{
		// We generate the postfix here
		// Append the token string with top of operand stack until it is empty
		// After operand stack is empty, we will have RPN, but backwards
		token += operandStack.top();
		operandStack.pop();
	}
	// Corrects postfix notation to proper order
	reverse(token.begin(), token.end());
	return token;
}

int EvaluateRPN(string postfix_)
//Used as reference for code:http://faculty.cs.niu.edu/~hutchins/csci241/eval.htm
{
	stack<int> postStack;
	string postfix = postfix_;
	string test;
	int result, A = 1, B = 1, value = 1;
	
	// We use stringstream to get the numbers and operators
	istringstream getOperand(postfix);

	// Runs while characters fron postfix can be read into word
	for (string word; getOperand >> word;)
	{
		test = word;
		//cout << "Test: " << test << endl;
		stringstream geek(test);
		// geek converts the string to and integer
		// tried atoi and tried stoi

		//cout << "Value2: " << value << endl;
		if (geek >> value)
		{

			// If the value in geek can be put in to the integer variable value, we pust it into the stack
			postStack.push(value);

		}
		//cout << "Value: " << value << endl;
		if (word == "+" || word == "-" || word == "*" || word == "/")
		{
			// If we have an operator, have A hold value of top of stack and pop
			// Then have B hold value of the top of stack after we just popped and pop again
			// We use A and B to perform mathematical operations
			A = postStack.top();
			postStack.pop();
			B = postStack.top();
			postStack.pop();

			// Perform operations based on the what the operator is
			if (word == "+")
			{
				result = B + A;
				cout << "Adding " << B << " and " << A << endl;
			}
			if (word == "-")
			{
				result = B - A;
				cout << "Subtracting " << B << " and " << A << endl;
			}
			if (word == "*")
			{
				result = B * A;
				cout << "Multiplying " << B << " and " << A << endl;
			}
			if (word == "/")
			{
				result = B / A;
				cout << "Dividing " << B << " and " << A << endl;
			}
			postStack.push(result);
			// Results are pushed to stack and may be used for further operations
		}

	}


	return result;
}

int EvaluateInfix(string infix_)
{
	// Calls functions to convert infix to postfix and evaluates expression
	string postfix = Infix2RPN(infix_);
	int result = EvaluateRPN(postfix);

	cout << "EvaluateInfix: " << postfix << endl;

	return result;
}
string RPN2Infix(string postfix)
{
	stack<string> postStack2;
	string op1, op2;
	string postfix2 = postfix;
	string test2;
	string finalanswer;
	string C, D;

	int value = 1;
	// Essentially the same as EvaluateInfix. We use stringstream to get the numbers and operators

	istringstream getOperand2(postfix);

	for (string word2; getOperand2 >> word2;)
	{
		test2 = word2;

		stringstream geek(test2);
		//tried atoi
		//tried stoi

		//cout << "Value2: " << value << endl;
		if (geek >> value)
		{

			// Push to stack if geek is a valid integer
			postStack2.push(test2);

		}
		if (word2 == "+" || word2 == "-" || word2 == "*" || word2 == "/")
		{
			// C and D hold values of top 2 in the stack. We use them and perform required operation
			C = postStack2.top();
			postStack2.pop();
			D = postStack2.top();
			postStack2.pop();


			if (word2 == "+")
			{
				//result = C + D;
				cout << "Adding " << C << " and " << D << endl;
				finalanswer = "(" + D + word2 + C + ")";//forms 20_30//test2=0;
				postStack2.push(finalanswer);
			}
			if (word2 == "-")
			{
				//result = C - D;
				cout << "Subtracting " << C << " and " << D << endl;
				finalanswer = "(" + D + word2 + C + ")";
				postStack2.push(finalanswer);
			}
			if (word2 == "*")
			{
				//result = C * D;
				cout << "Multiplying " << C << " and " << D << endl;
				finalanswer = "(" + D + word2 + C + ")";//Opened a parenthese 10*C which is 
				postStack2.push(finalanswer);
			}
			if (word2 == "/")
			{
				//result = C / D;
				cout << "Dividing " << C << " and " << D << endl;
				finalanswer = "(" + D + word2 + C + ")";
				postStack2.push(finalanswer);

			}
			//postStack2.push(test2);
		}

	}

	return finalanswer;
}

string RPN2InfixWithSpace(string postfix)
{
	stack<string> postStack2;
	string op1, op2;
	string postfix2 = postfix;
	string test2;
	string finalanswer;
	string C, D;

	int value = 1;

	istringstream getOperand2(postfix);

	for (string word2; getOperand2 >> word2;)
	{
		test2 = word2;

		stringstream geek(test2);
		//tried atoi
		//tried stoi

		//cout << "Value2: " << value << endl;
		if (geek >> value)
		{

			//cout << "Converted: " << value << endl;
			postStack2.push(test2);

		}
		if (word2 == "+" || word2 == "-" || word2 == "*" || word2 == "/")
		{
			C = postStack2.top();
			postStack2.pop();
			D = postStack2.top();
			postStack2.pop();


			if (word2 == "+")
			{
				//result = C + D;
				cout << "Adding " << C << " and " << D << endl;
				finalanswer = "( " + D + " " + word2 + " " + C + " )";//forms 20_30//test2=0;
				postStack2.push(finalanswer);
			}
			if (word2 == "-")
			{
				//result = C - D;
				cout << "Subtracting " << C << " and " << D << endl;
				finalanswer = "( " + D + " " + word2 + " " + C + " )";
				postStack2.push(finalanswer);
			}
			if (word2 == "*")
			{
				//result = C * D;
				cout << "Multiplying " << C << " and " << D << endl;
				finalanswer = "( " + D + " " + word2 + " " + C + " )";//Opened a parenthese 10*C which is 
				postStack2.push(finalanswer);
			}
			if (word2 == "/")
			{
				//result = C / D;
				cout << "Dividing " << C << " and " << D << endl;
				finalanswer = "( " + D + " " + word2 + " " + C + " )";
				postStack2.push(finalanswer);

			}
			//postStack2.push(test2);
		}

	}

	return finalanswer;
}

ArithNode *createOperandNode(int num)
{
	ArithNode *temp = new ArithNode;
	temp->isOperator = false;
	temp->left = 0;
	temp->right = 0;
	temp->operand = num;
	return temp;
}
ArithNode *createOperatorNode(string s)
{
	ArithNode *temp = new ArithNode;
	temp->isOperator = true;
	temp->left = 0;
	temp->right = 0;
	temp->binaryOperator = s[0];
	return temp;
}
ArithNode *Infix2ExpressionTree(string infix_)
{
	string infix = infix_;
	stack<ArithNode *> Operand;
	stack<ArithNode *> ExpressionTree;
	ArithNode *n = nullptr, *n1 = nullptr, *n2 = nullptr, *n3 = nullptr;
	int right, left;

	string op1, op2;
	string infix2 = infix;
	string test2;
	string finalanswer;
	string C, D;
	int numberOfParenthesis = 0;
	int value = 1;

	// Use stringstream to get numbers and operators
	istringstream getOperand2(infix);
	for (string word2; getOperand2 >> word2;)
	{
		test2 = word2;

		stringstream geek(test2);

		// For left parenthesis, we increment numberOFPArenthesis
		if (word2 == "(")
		{
			numberOfParenthesis += 1;
		}
		// For Right parenthesis, we have n1 be the left child and n2 be the right child of new node
		else if (word2 == ")")
		{
			n1 = Operand.top();
			Operand.pop();
			n2 = Operand.top();
			Operand.pop();
			Operand.push(createNode1(n2, n1, ExpressionTree.top()->binaryOperator));
			ExpressionTree.pop();
			// Create new node with n2 and n1 as children and the value of int on top of ExpressionTree stack
			// Decrement numberOfParenthesis
			numberOfParenthesis -= 1;
		}

		else if (word2 == "+" || word2 == "-" || word2 == "*" || word2 == "/")
		{
			// If we have an operator, create a new node with the operater and push to stack
			n = createOperatorNode(word2);
			
			ExpressionTree.push(n);
		}
		
		else if (geek >> value)
		{
			if (numberOfParenthesis > 0)
			{
				// If we have a digit and parenthesis remaining, push the value onto operand stack
				n = createOperandNode(value);
				Operand.push(n);
			}
			else
			{
				if (Operand.size() == 1)
				{
					if (ExpressionTree.size() == 1)
					{
						// If size of both stacks are 1, there create a new node with ExpressionTree value and operand stack and value as children 
						Operand.push(createNode1(Operand.top(), createOperandNode(value), ExpressionTree.top()->binaryOperator));
					}
				}
				else
				{
					// Otherwise, just push to operand stack
					Operand.push(createOperandNode(value));
				}
			}

		}
	}

	// Resolve operations
	while (Operand.size() > 1)
	{
		ArithNode *  rightChild = Operand.top();
		Operand.pop();
		ArithNode * leftChild = Operand.top();
		Operand.pop();
		Operand.push(createNode1(leftChild, rightChild, ExpressionTree.top()->binaryOperator));
		ExpressionTree.pop();
	}

	// Pop root from operand
	n = Operand.top();
	Operand.pop();

	return n;
}
ArithNode *RPN2ExpressionTree(string rpn)
{
	string infix = RPN2InfixWithSpace(rpn);
	ArithNode *tree = Infix2ExpressionTree(infix);
	return tree;
}
//Used Code from :https://stackoverflow.com/questions/12684086/convert-from-an-infix-expression-to-postfix-c-using-stacks for Higher Precedence
// HigherPrecedence determines the order operators should be pushed; ^ has highest, followed by * /, then + -
// + - cases are handled as remaining cases since all other operators are checked in if statements
bool HigherPrecedence(char leftOperator, char rightOperator)
{
	if (leftOperator == '^') {
		return true;
	}
	else if (rightOperator == '^') {
		return false;
	}
	else if (leftOperator == '*' || leftOperator == '/' || leftOperator == '%') {
		return true;
	}
	else if (rightOperator == '*' || rightOperator == '/' || rightOperator == '%') {
		return false;
	}

	return true;
}
ArithNode *createNode(ArithNode *leftChild, ArithNode *rightChild, int parent)
{
	ArithNode *temp = new ArithNode;
	temp->left = leftChild;
	temp->right = rightChild;
	temp->operand = parent; // Assuming operand is root

	return temp;
}
ArithNode *createNode1(ArithNode *leftChild, ArithNode *rightChild, char binaryOperator)
{
	ArithNode *temp = new ArithNode;
	temp->left = leftChild;
	temp->right = rightChild;
	//temp->operand = binaryOperator; // Assuming operand is root
	temp->operand = binaryOperator;
	temp->binaryOperator = binaryOperator; // Assuming operand is root
	temp->isOperator = true;

	return temp;
}
