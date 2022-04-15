#include <iostream>
#include <string>
#include "stack.h"

using namespace std;

struct Result {
    double result;
    bool error;
};

Result response;

// Check if expression was a correct format
int check_expression(string expression)
{
    char *buffer;
    buffer = new char[expression.size()+1];
    strcpy(buffer, expression.c_str());

    int llaves = 0, i = 0;
    while (i < strlen(buffer)) {
        char chr = buffer[i];

        if (chr == '(' || chr == '{' || chr == '[') {
            llaves++;
        } else if (chr == ')' || chr == '}' || chr == ']') {
            llaves--;
        }
        
        if (i == strlen(buffer) -1){
            if (chr == '+' || chr == '-' || chr == '*' || chr == '/' || chr == ' ') {
                return 1;
            }   
        }
        i++;
    }
    delete[] buffer;
    return llaves;
}

// Check if a char is a operator
bool isoperator(char arg)
{
    if(arg == '*' || arg == '/' || arg == '+' || arg == '-') return(1);
    else return(0);
}

// Check if a char is a operand 
bool isoperand(char arg)
{
    if(arg >= '0' && arg <= '9') return 1;
    if(arg >= 'a' && arg <= 'z') return 1;
    if(arg >= 'A' && arg <= 'Z') return 1;
    return 0;
}

// Set precedence status
int operatorweight(char arg)
{
    int weight = 0;
    switch(arg)
    {
    case '*':
    case '/':
        weight = 2;
        break;
    case '+':
    case '-':
        weight = 1;
        break;
    }
    return(weight);
}

// Check operator precedence
bool highprecendence(char a, char b)
{
    int weighta = operatorweight(a);
    int weightb = operatorweight(b);
    if(weighta >= weightb) return 1;
    return 0;
}

// Convert infix to postfix
string infix2postfix(string expr)
{
    Stack<char> stack;
    string postfix = "";
    for(int i = 0;i < expr.length(); i++)
    {
        if(expr[i] == '(') {
            stack.push(expr[i]);
        }
        else if(expr[i] == ')') {
            while(stack.top() != '(')
            {
                postfix += ' ';
                postfix = postfix + stack.top();
                stack.pop();
            }
            stack.pop();
        }
        else if(isoperand(expr[i])) {
            postfix += expr[i];
        }
        else if(isoperator(expr[i])) {
            postfix += ' ';
            while(!stack.empty()&& !highprecendence(expr[i],stack.top()))
            {
                postfix+= stack.top();
                stack.pop();
            }
            stack.push(expr[i]);
        }
    }
    while(!stack.empty())
    {
        postfix += ' ';
        postfix+= stack.top();
        stack.pop();
    }
    return postfix;
}

// Operate two operands in postfix format
float operation(float a , float b , char sym)
{
	float ans ;
	switch(sym)
	{
		case '+' : ans = a + b ;
			   break;
		case '-' : ans = a - b ;
			   break ;
		case '*' : ans = a*b ;
			   break ;
		case '/' : ans = a/b ;
			   break ;
		default  : break ;
	}
	return ans ;
}

// Resolve postfix expression
double resolve(string postfix_expression)
{
    Stack<double> stack;
    float  num=0 , num1=0 , num2=0;
	for(int i = 0; i < postfix_expression.length(); i++)
	{
		if(isoperand(postfix_expression[i]))
		{
			num = 0;
			while(postfix_expression[i]!=' ')
			{
				int a = postfix_expression[i++]- '0';
				num = 10*num + a ;
			}

			stack.push(num);
		}
		else if(isoperator(postfix_expression[i]))
		{
			num2 = stack.top();
			stack.pop();
			num1 = stack.top();
			stack.pop();
			num = operation(num1 , num2 , postfix_expression[i]);
			stack.push(num);
		}
		else
			continue;
	}
	
	num = stack.top();
    return num;
}

Result evaluate(string input)
{
    // 1- descomponer el input y validar
    if (check_expression(input) != 0) {
        response.error = true;
        return response;
    } else {
        response.error = false;
    }
    
    // 2- convertir de Infijo a Postfijo
    string postfix = infix2postfix(input); 

    // // 3- resolver la expresion
    response.result = resolve(postfix);

    //* Si no cumple la validacion retornar Result.error = true;
    return response;
}
