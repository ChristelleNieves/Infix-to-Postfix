// **********************************************************
// * Name: Christelle Nieves                                *                                *
// * Assignment: Assignment 3: Infix to Postfix Conversion  *
// * Date: February 25, 2020                                *
// **********************************************************

#ifndef _STACK_HPP
#define _STACK_HPP

#include <iostream>
#include <vector>

#include "stack.h"

using namespace std;
using namespace cop4530;

// Zero parameter stack constructor.
template <typename T>
Stack<T>::Stack()
{
    // Nothing to be done here since we're using a vector.
}

// Destructor.
// Invokes the clear function to clear all elements from the stack.
template <typename T>
Stack<T>::~Stack()
{
    elements.clear();
}

// Copy constructor.
// Initializes a new stack with elements from rhs.
template <typename T>
Stack<T>::Stack(const Stack<T>& rhs)
{
    elements = rhs.elements;
}

// Copy assignment operator.
template <typename T> 
Stack<T>& Stack<T>::operator=(const Stack<T>& rhs)
{ 
    Stack<T> copy = rhs;
    elements = copy.elements;
    return *this;
}

// Move constructor.
template <typename T>
Stack<T>::Stack(Stack<T>&& rhs)
{
    elements = rhs.elements;
    rhs.clear();
}

// Move assignment operator.
template <typename T> 
Stack<T>& Stack<T>::operator=(Stack<T>&& rhs)
{
    clear();
    elements = rhs.elements;
    return *this;
}

// Clear all elements from the stack.
template <typename T>
void Stack<T>::clear()
{
    elements.clear();
}

// Return true if stack is empty, false otherwise.
template <typename T>
bool Stack<T>::empty()
{
    return elements.empty();
}

// Push an element to the stack. Copy version.
template <typename T> 
void Stack<T>::push(const T& x)
{
    T copy = x;
    elements.push_back(copy);
}

// Push an element to the stack. Move version.
template <typename T> 
void Stack<T>::push(T&& x)
{
    elements.push_back(x);
}

// Print all elements in the stack, separated by delimiter ofc.
template <typename T> 
void Stack<T>::print(std::ostream& os, char ofc) const
{
    for (int i = 0; i < elements.size(); i++)
    {
        cout << elements.at(i) << ofc;
    }
    cout << endl;
}

// Return the number of elements in the stack.
template <typename T>
int Stack<T>::size() const
{
    return elements.size();
}

// Pop the most recent added element from the stack.
template <typename T>
void Stack<T>::pop()
{
    elements.pop_back();
}

// Return the most recent element added to the stack.
template <typename T> 
T& Stack<T>::top()
{
    return elements.back();
}

// Return the most recent element added to the stack.
template <typename T>
const T& Stack<T>::top() const
{
    return elements.back();
}

// Override the << operator to invoke the print function.
template <typename T> 
std::ostream& operator<<(std::ostream& os, const Stack<T>& a)
{
    a.print(os, ' ');
}

// Return true if stack A == stack B.
template <typename T> 
bool operator==(const Stack<T>& a, const Stack<T>& b)
{
    // If the sizes are different we know they are not equal.
    if (a.size() != b.size()) return false;
    
    // If they are both empty then they are equal.
    if (a.size() == 0 && b.size() == 0) return true;

    // In all other cases, loop through and compare each element.
    for (int i = 0; i < a.size(); i++)
    {  
        // If we encounter an element that doesn't match, return false.
        if (a.elements.at(i) != b.elements.at(i)) return false;
    }

    // If we make it to this point then the stacks are equal.
    return true;
}

// Return true if stack A is not equal to stack B
template <typename T> 
bool operator!=(const Stack<T>& a, const Stack<T>& b)
{
    // Return the negation of the == operator.
    return !(a == b);
}

// Return true if stack A is less than or equal to stack B
template <typename T> 
bool operator<=(const Stack<T>& a, const Stack<T>& b)
{
    // If the stacks are the same they are equal so return true.
    if (a == b) return true;

    // If the stacks are both empty we will return false.
    if (a.size() == 0 || b.size() == 0) return false;

    // If the size of stack A is greater than the size of stack B, we will loop
    // through the entirety of stack A and compare the elements.
    if (a.size() > b.size())
    {
        for (int i = 0; i < b.size(); i++)
        {
            // Return false if we encounter an element in A that is greater than the
            // corresponding element in B.
            if (a.elements.at(i) > b.elements.at(i)) return false;
        }
    }
    // Else if the size of stack B is greater than the size of stack A, we will loop
    // through the entirety of stack B and compare the elements.
    else if (b.size() > a.size())
    {
        for (int i = 0; i < a.size(); i++)
        {
            // Return false if we encounter an element in A that is greater than the
            // corresponding element in B.
            if (a.elements.at(i) > b.elements.at(i)) return false;
        }
    }

    // If we make it to this point then A <= B.
    return true;
}

#endif
