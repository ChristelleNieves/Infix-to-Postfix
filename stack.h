// **********************************************************
// * Name: Christelle Nieves                                *                               *
// * Assignment: Assignment 3: Infix to Postfix Conversion  *
// * Date: February 25, 2020                                *
// **********************************************************

#ifndef _STACK_H
#define _STACK_H

#include <iostream>
#include <utility>
#include <vector>

namespace cop4530
{
    // Define the Stack class.
    template <typename T> 
    class Stack 
    {
        public: 
             // Stack constructors and operators.
            Stack();    // Zero parameter constructor
            ~Stack();   // Destructor
            Stack(const Stack<T>&); // Copy constructor
            Stack(Stack<T>&&);  // Move constructor
            Stack<T>& operator=(const Stack<T>&);   // Copy assignment op
            Stack<T>& operator=(Stack<T>&&);    // Move assignment op

            // Stack member functions.
            bool empty();   // Returns true if stack is empty, false otherwise.
            void clear();   // Delete all elements in the stack.
            void push(const T& x);  // Adds x to the stack. COPY VERSION.
            void push(T&& x);   // Adds x to the stack. MOVE VERSION.
            void pop(); // Removes & discards the most recently added element of the stack.
            T& top();   // Returns a reference to the most recently added element of the stack as a modifiable lvalue.
            const T& top() const;   // Accessor. Same as above but returns a const reference.
            int size() const;   // Returns the number of elements in the stack.
            void print(std::ostream& os, char ofc = ' ') const; // Prints the elements of the stack separated by ofc.

            // Stack attributes.
            std::vector<T> elements;
    };

    // Non-member functions.
    template <typename T>
    std::ostream& operator<<(std::ostream& os, const Stack<T>& a);  // Invokes the print function.

    template <typename T>
    bool operator==(const Stack<T>&, const Stack<T>&);  // Returns true if both stacks are equal, otherwise false.

    template <typename T>
    bool operator!=(const Stack<T>&, const Stack<T>&);  // Opposite of ==

    template <typename T>
    bool operator<=(const Stack<T>& a, const Stack<T>& b);  // Returns true if every element in A is <= the corresponding
        // element in stack B.

     #include "stack.hpp"
}

#endif