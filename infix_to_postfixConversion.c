#include<stdio.h>
#include<stdbool.h>                  //header files
#include<strings.h>
#define size 100                     

char postFix[size];
char stack[size];                          //stacks of character type 
int top = -1, operatorTop = -1;            //pointers for stacks

void                        
pushOp (char x)
{

  if (operatorTop >= size)
    {
      puts ("Stack is Full.\n");                      //push method for second stack
    }
  else
    {
      stack[++operatorTop] = x;
    }

}

void
pushPostFix (char x)
{
  if (top >= size)
    {
      puts ("Stack is Full.\n");                    //push method for first stack
    }
  else
    {
      postFix[++top] = x;
    }
}

char
popOp ()
{
  char x = '\0';
  if (operatorTop == -1)
    {
      puts ("Stack is Empty\n");
    }                                        //pop method for second stack

  else
    {
      x = stack[operatorTop--];
      return x;
    }

}

char
popPostfix ()
{

  char x = '\0';
  if (top == -1)
    {
      puts ("Stack is Empty.\n");              //pop method for first stack
    }
  else
    {
      x = postFix[top--];
      return x;
    }

}

bool
isOperand (char x)
{

  if (x >= '0' && x <= '9')
    {
      return true;                          //function to check validity of operand
    }
  return false;
}

bool
isOperator (char x)
{

  if (x == '+' || x == '-' || x == '*' || x == '/' || x == '^')
    {                                                                       //function to check valid operator
      return true;
    }
  return false;
}

int
priority (char x)
{

  if (x == '+' || x == '-')
    {
      return 1;
    }
  if (x == '*' || x == '/')                               //function for precedance
    {
      return 2;
    }
  if (x == '^')
    {
      return 3;
    }
}

bool
checkMatchingBrackets (char x, char y)
{

  if ((x == '(' && y == ')') ||
      (x == '[' && y == ']') || (x == '{' && y == '}'))                      //function to check valid brackets 
    {
      return true;
    }
  return false;
}

bool
checkOpeningBrackets (char x)
{

  if (x == '(' || x == '[' || x == '{')
    {                                                                //function to check opening brackets
      return true;
    }
  return false;
}

bool
checkClosingBrackets (char x)
{

  if (x == ')' || x == ']' || x == '}')                //function to check closing brackets
    {
      return true;
    }
  return false;
}

int
main ()
{
  char infix[size];
  int i = 0;                                                   //variable initializing
  bool flag = true;

  printf ("Enter Expression: ");
  gets (infix);                                                     //getting input
  while (infix[i] != '\0' && flag)
    {
      if (checkOpeningBrackets (infix[i]))                        //checking the validity of each expression
	pushOp (infix[i]);
      if (isOperand (infix[i]))
	pushPostFix (infix[i]);
      if (isOperator (infix[i]))
	{
	  if ((isOperator (stack[operatorTop])
	       && priority (infix[i]) <= priority (stack[operatorTop])))
	    {
	      while (isOperator (stack[operatorTop]))
		pushPostFix (popOp ());
	      pushOp (infix[i]);
	    }
	  pushOp (infix[i]);
	}
      if (checkClosingBrackets (infix[i]))
	{
	  while (!checkMatchingBrackets (stack[operatorTop], infix[i]))
	    {
	      if (isOperator (stack[operatorTop]))
		pushPostFix (popOp ());
	      if ((stack[operatorTop] == '\0')
		  || (checkOpeningBrackets (stack[operatorTop])
		      && !checkMatchingBrackets (stack[operatorTop],
						 infix[i])))
		{
		  flag = false;
		  break;
		}
	    }
	  popOp ();
	}
      i++;

    }

  if (stack[operatorTop] != '\0')
    {
      while (isOperator (stack[operatorTop])){
       pushPostFix (popOp ());
      }
      if (checkOpeningBrackets (stack[operatorTop])){
         	flag = false;
      }
    }

  if (flag)
    {
      printf ("Infix Notation: %s\n", infix);
      printf ("Post Fix Notation: %s\n", postFix);                     //printing the results if balance equation
      printf ("Balanced Expression.\n");

    }

  else
    {
      printf ("Expression is not balanced\n");                            //printing the results if invalid expression
    }

  return 0;
}

