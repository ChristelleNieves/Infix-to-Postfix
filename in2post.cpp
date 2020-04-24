// **********************************************************
// * Name: Christelle Nieves                                *                               *
// * Assignment: Assignment 3: Infix to Postfix Conversion  *
// * Date: February 25, 2020                                *                                 *
// **********************************************************

#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <cstdlib>
#include <list>
#include "stack.h"

using namespace std;
using namespace cop4530;

template <typename T>
Stack<T> getPostfix(T);
string getInput();
string stackToString(Stack<string>);
string evaluatePostfix(string);
string removeZeros(string);
bool hasValidParentheses(string);
bool isOperator(string);
bool isOperand(string);
int getPrecedence(string);
float stringToFloat(string);
bool isFloat(string);
void error(string);
bool isNumber(string);

int main()
{
    // Accept input from the user until they decide to quit the program.
    while (true)
    {
        // Get and store the input from the user.
        string inputString = getInput();

        if (inputString == "quit")
        {
            break;
        }

        // Report an error if we encounter mismatched parentheses.
        if (!hasValidParentheses(inputString))
        {
            error("Invalid input.");
        }
        else
        {
             // Convert the input to an infix expression
            // Testing the move assignment operator
            Stack<string> postfixStack;
            postfixStack = getPostfix(inputString);

            // Check for errors.
            if (postfixStack.top() == "error")
            {
                error("Invalid input");
            }
            else
            {
                // Just to show that the copy constructor and copy assignment operators work.
                Stack<string> postFix;
                postFix = postfixStack;

                // Demonstrating the overloaded == operator
                if (postFix == postfixStack)
                {
                    // Print the postfix expression using the stack.print function
                    cout << "Postfix: ";
                    postFix.print(cout, ' ');

                    string postfixString = stackToString(postFix);

                    // Evaluate the postfix expression and store it in a string.
                    string result = evaluatePostfix(postfixString);

                    // Print the result if there were no errors.
                    if (!(result == "error"))
                    {
                        // Print the result.
                        cout << "Result: " << result << endl;
                    }
                    else
                    {
                        error("Invalid input.");
                    } 
                }
                else if (postFix != postfixStack)
                {
                    error("Invalid input.");
                }
            }
        }
    }

    return 0;
}

// **********************************************************************
// * Function Name: getInput()                                          *
// * Description: Gets input from the user and stores it in a string.   *
// * Parameter Description: Takes in no parameters. Returns a string.   *
// * Date: Feb 21, 2020                                                 *
// * Author: Christelle Nieves                                          *
// **********************************************************************
string getInput()
{
    string inputString;

    cout << "Enter a space separated string (Enter \"quit\" to quit) ";
    getline(cin, inputString);

    return inputString;
}

// **********************************************************************
// * Function Name: isOperator()                                        *
// * Description: Returns true if a string is an operator.              *
// * Parameter Description: Takes in a string that represents a token.  *
// * Date: Feb 25, 2020                                                 *
// * Author: Christelle Nieves                                          *
// **********************************************************************
bool isOperator(string s)
{
    return s == "+" || s == "-" || s == "*" || s == "/";
}

// ******************************************************************************
// * Function Name: isOperand()                                                 *
// * Description: Returns true if a string is an operand. Operands are          *
//      either integers, floats, or variable names that begin with a letter.    *
// * Parameter Description: Takes in a string that represents a token.          *
// * Date: Feb 25, 2020                                                         *
// * Author: Christelle Nieves                                                  *
// ******************************************************************************
bool isOperand(string s)
{
    // If it only contains numbers or a decimal, return true.
    if (isNumber(s))
    {
        return true;
    }
    else
    {
        // If the first character is not a letter, return false.
        if (!isalpha(s[0]))
        {
            return false;
        }
        // If s is a letter or a float, return true.
        if ((s >= "a" && s <= "z") || (s >= "A" && s <= "Z") || isFloat(s))
        {
            return true;
        }

        // Return false in all other cases.
        return false;
    }
}

// **********************************************************************************
// * Function Name: getPrecedence()                                                 *
// * Description: Returns an integer representing the precedence of an operator.    *
// * Parameter Description: Takes in a string that represents an operator token.    *
// * Date: Feb 25, 2020                                                             *   
// * Author: Christelle Nieves                                                      *
// **********************************************************************************
int getPrecedence(string s)
{
    if (s == "+" || s == "-")
    {
        return 1;
    }
    else if (s == "*" || s == "/")
    {
        return 2;
    }
    else
    {
        return 100;
    }
}

// **********************************************
// * Function Name: stringToFloat()             *
// * Description: Converts a string to a float. *
// * Parameter Description: Takes in a string.  *
// * Date: Feb 25, 2020                         *
// * Author: Christelle Nieves                  *
// * References: This function was inspired by  *
//      Dr. Gaitros' code example.              *
// **********************************************
float stringToFloat(string s)
{
    return atof(s.c_str());
}

// **********************************************************************
// * Function Name: error()                                             *
// * Description: Displays an error message.                            *
// * Parameter Description: Takes in a string holding an error message. *
// * Date: Feb 25, 2020                                                 *   
// * Author: Christelle Nieves                                          *
// **********************************************************************
void error(string message)
{
    cout << "Error: " << message << endl;
}

// **********************************************************************************
// * Function Name: hasValidParentheses()                                           *
// * Description: Determines if a string contains accurate pairs of parentheses.    *
// * Parameter Description: Takes in a string holding an infix expression.          *
// * Date: Feb 25, 2020                                                             *
// * Author: Christelle Nieves                                                      *
// **********************************************************************************
bool hasValidParentheses(string s)
{
    int open = 0; 
    int close = 0;
    Stack<string> testStack;
    stringstream ss(s);
    string token;

    // Loop through the string, separating tokens by spaces.
    while (getline(ss, token, ' '))
    {
        // If the case we encounter an opening or closing parenthesis.
        if (token == "(" || token == ")")
        {
            if (testStack.empty() && token == ")")
            {
                return false;
            }
            // Increment the number of opening parentheses.
            if (token == "(")
            {
                open++;
            }

            // If we encounter a closing parenth, but never encountered en opening
            // parenth, we will return false.
            if (token == ")" && open < 1)
            {
                return false;
            }
            else if (token == ")" && open > 0)
            {
                // Whenever we find a closing parenth to match an opening parenth,
                // We've completed a pair, so decrement the opening parenths by one.
                open--;
            }
            // If the next token is EOF and we have an opening parenth that never closed, return false.
            if (ss.peek() == ss.eof() && open > 1)
            {
                return false;
            }
            
            // Push the token to the stack.
            testStack.push(token);
        }
    }

    // Now go through the test stack and check if all parentheses have a corresponding partner.
    int numOpening = 0;
    int numClosing = 0;

    // Loop until the test stack is empty and count the number of opening/closing parenths.
    while (!testStack.empty())
    {
        if (testStack.top() == "(")
        {
            numOpening++;
        }
        else if (testStack.top() == ")")
        {
            numClosing++;
        }

        testStack.pop();
    }

    // Check if the number of parentheses match.
    if (numOpening != numClosing)
    {
        return false;
    }

    return true;
}

// **********************************************************************************
// * Function Name: getPostfix()                                                    *
// * Description: Converts an infix expression to a postfix expression.             *
// * Parameter Description: Takes in a datatype T which holds an infix expression.  *
// * Date: Feb 25, 2020                                                             *
// * Author: Christelle Nieves                                                      *
// **********************************************************************************
template <typename T>
Stack<T> getPostfix(T s)
{
    Stack<string> error;
    Stack<string> postfix;
    Stack<string> processed;
    string token;
    Stack<string> stack;
    stringstream ss(s);

    error.push("error");

    // Loop through the entire string, separating tokens by spaces.
    while (getline(ss, token, ' '))
    {
        // If we encounter an operand, push it to the postfix stack and count it as processed.
        if (isOperand(token))
        {
            // If the next token is "(" then report an error.
            if (ss.peek() == '(')
            {
                return error;
            }

            postfix.push(token);
            processed.push(token);
        }
        // If we encounter a "("" we will push it to the stack and note it as processed.
        else if (token == "(")
        {
            stack.push(token);
            processed.push(token);
        }
        // If we encounter an operator, repeatedly add the top of the stack to the
        // postfix until an op with lower precedence is at the top, a "( is at the top, or stack is empty.
        else if (isOperator(token))
        {
            // Loop until the stack is empty.
            while (!stack.empty())
            {
                // If an operator with lower precedence is at the top, break.
                if (getPrecedence(stack.top()) < getPrecedence(token))
                {
                    break;
                }
                
                // If a "( is at the top, break.
                if (stack.top() == "(")
                {
                    break;
                }

                // Add the top of the stack to the postfix expression and pop it off the stack.
                postfix.push(stack.top());
                stack.pop();
            }
            // Note the token as processed and push it to the stack.
            processed.push(token);
            stack.push(token);
        }
        // If we encounter a ")"
        else if (token == ")")
        {
            // If the next character after a ")" is not an operand or EOF, report an error.
            if (!(ss.peek() == '+' || ss.peek() == '-' || ss.peek() == '*' || ss.peek() == '/')
                 && ss.peek() != EOF && ss.peek() != '(' && ss.peek() != 41)
            {
                return error;
            }

            // If the last token we processed was an operator, report an error.
            if (isOperator(processed.top()))
            {
                return error;
            }

            // Search for a "(" in the stack, if one is not found we will report an error.
            bool found = false;
            while (!stack.empty())
            {
                if (stack.top() == "(")
                {
                    found = true;
                    break;
                }
                
                // Add the top of the stack to the postfix expression and pop it off the stack.
                postfix.push(stack.top());
                stack.pop();
            }

            // If we never found a "(" in the stack, report an error.
            if (!found)
            {
                return error;
            }
            
            // Pop the token off the stack.
            stack.pop();
        }
        else
        {
            return error;
        }
    }

    // Add the remaining elements in the stack to the postfix expression and pop them off the stack.
    while (!stack.empty())
    {
        postfix.push(stack.top());
        stack.pop();
    }

    return postfix;
}

// **********************************************************************************
// * Function Name: evaluatePostfix()                                               *
// * Description: Evaluates a postfix expression if the expression contains         *
//      only numbers. If the expression contains any variable names, the function   *
//      returns the input string untouched.                                         *
// * Parameter Description: Takes in a string holding a postfix expression.         *
// * Date: Feb 25, 2020                                                             *
// * Author: Christelle Nieves                                                      *
// **********************************************************************************
string evaluatePostfix(string s)
{
    string error = "error";

    // Go through each character in the string and look for letters.
    for (int i = 0; i < s.length(); i++)
    {
        // Check if the character is an operator.
        if (!(s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/'))
        {
            // If we find a letter, we cannot evaluate the postfix so return the string.
            if (isalpha(s[i]))
            {
                return s;
            }
        }
    }

    // If we make it to this point we can start evaluating the expression.
    Stack<string> operands;
    Stack<string> postfix;
    stringstream ss(s);
    string token;

    // Loop through the string, separating tokens by spaces.
    while (getline(ss, token, ' '))
    {
        // Immediately push operands to the operands stack when they are encountered.
        if (isOperand(token))
        {
            operands.push(token);
        }
        else if (isOperator(token))
        {
            // If there are less than 2 operands on the stack, report an error.
            if (operands.size() < 2)
            {
                return error;
            }

            float a = 0, b = 0;

            // Set the operands we will use in the calculations.
            b = stringToFloat(operands.top());
            operands.pop();
            a = stringToFloat(operands.top());
            operands.pop();

            float res = 0;
            string result;

            // Perform the appropriate calculations on the operands.
            if (token == "+")
            {
                res = a + b;
            }
            else if (token == "-")
            {
                res = a - b;
            }
            else if (token == "*")
            {
                res = a * b;
            }
            else if (token == "/")
            {
                // Report any division by zero as an error.
                if (b == 0)
                {
                    return error;
                }

                res = a / b;
            }
            
            // Convert the result to a string and remove trailing zeros.
            result = removeZeros(std::to_string(res));

            // Push the final result to the operands stack.
            operands.push(result);
        }
    }

    string finalResult = "";

    // If we have more than 1 value in the operands stack, report an error.
    if (operands.size() > 1)
    {
        return error;
    }
    // If we have one value, set it as the final result.
    else if (operands.size() == 1)
    {
        finalResult = operands.top();
    }
    // If we have no values the answer is zero.
    else if (operands.size() == 0)
    {
        finalResult = "0";
    }

    return finalResult;
}

// **********************************************************************
// * Function Name: isFloat()                                           *
// * Description: Returns true if a string contains a decimal point.    *
// * Parameter Description: Takes in a string.                          *
// * Date: Feb 25, 2020                                                 * 
// * Author: Christelle Nieves                                          *
// **********************************************************************
bool isFloat(string s)
{
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == '.')
        {
            return true;
        }
    }

    return false;
}

// **************************************************************************************
// * Function Name: removeZeros()                                                       *
// * Description: Removes any trailing zeros from a float number.                       *
//      Returns an integer if the number only contains zeroes after the decimal point.  *
// * Parameter Description: Takes in a string that holds a float.                       *
// * Date: Feb 25, 2020                                                                 *
// * Author: Christelle Nieves                                                          *
// **************************************************************************************
string removeZeros(string s)
{
    Stack<char> st;
    list<char> l;
    string result;

    // Push all the characters in the string to a stack.
    for ( int i = 0; i < s.length(); i++)
    {
        st.push(s[i]);
    }

    // Pop off all zeros until we reach a value thats not a zero
    while (st.top() == '0')
    {
        st.pop();
    }

    // If we reach the decimal, pop it off the stack.
    if (st.top() == '.')
    {
        st.pop();
    }

    // Push stack contents into a list.
    // The purpose of this is to get the correct order when we add it to the final string.
    while (!st.empty())
    {
        l.push_front(st.top());
        st.pop();
    }

    // Now add the elements from the list to the final result string.
    while(!l.empty())
    {
        result += l.front();
        l.pop_front();
    }

    return result;
}

// **************************************************************************
// * Function Name: isNumber()                                              *
// * Description: Returns false if a string contains any character except   *
//      for digits or a decimal point.                                      *
// * Parameter Description: Takes in a string holding an operand token.     *
// * Date: Feb 25, 2020                                                     *  
// * Author: Christelle Nieves                                              *
// **************************************************************************
bool isNumber(string s)
{
    for (int i = 0; i < s.length(); i++)
    {
        if (!isdigit(s[i]) && s[i] != '.')
        {
            return false;
        }
    }

    return true;
}

// **********************************************************************
// * Function Name: stackToString()                                     *
// * Description: Converts a stack to a string and returns the string.  *
// * Parameter Description: Takes in a stack of strings.                *
// * Date: Feb 25, 2020                                                 *
// * Author: Christelle Nieves                                          *
// **********************************************************************
string stackToString(Stack<string> s)
{
    string str;
    Stack<string> temp;

    // Loop through the string and push all elements to a new stack.
    while (!s.empty())
    {
        temp.push(s.top());
        s.pop();
    }

    // Loop through the new stack and pop all elements, adding them to the string.
    while (!temp.empty())
    {
        str += temp.top();
        str += ' ';
        temp.pop();
    }

    // Return the string.
    return str;
}