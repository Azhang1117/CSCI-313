//
//  main.cpp
//  HW2_Problem_4
//
//  Created by Amy Zhang on 10/31/20.
//  Copyright © 2020 Amy Zhang. All rights reserved.
//

// Create your own stack functions to do the   following:
//   a. List all the elements in the stack
//   b. Iterate through the stack and change one of the values based on its position

#include <iostream>
#include<ctime>
#include<cstdlib>
#include <chrono>
#include<vector>
#include <cassert>
#define H_StackType
#define H_StackADT
using namespace std;

template<class Type>
class stackADT {
    
public:
    // Function declarations
    virtual bool isEmptyStack() const = 0;
    virtual bool isFullStack() const = 0;
    virtual void push(const Type& newItem) = 0;
    virtual Type top() const = 0;
    virtual void pop() = 0;;
};


template <class Type>
class stackType: public stackADT<Type>
{
public:
    const stackType<Type>& operator=(const stackType<Type>&);
    //Overload the assignment operator.
    
    void initializeStack();
    //Function to initialize the stack to an empty state.
    //Postcondition: stackTop = 0
    
    bool isEmptyStack() const;
    //Function to determine whether the stack is empty.
    //Postcondition: Returns true if the stack is empty,
    //               otherwise returns false.
    
    bool isFullStack() const;
    //Function to determine whether the stack is full.
    //Postcondition: Returns true if the stack is full,
    //               otherwise returns false.
    
    void push(const Type& newItem);
    //Function to add newItem to the stack.
    //Precondition: The stack exists and is not full.
    //Postcondition: The stack is changed and newItem
    //               is added to the top of the stack.
    
    Type top() const;
    //Function to return the top element of the stack.
    //Precondition: The stack exists and is not empty.
    //Postcondition: If the stack is empty, the program
    //               terminates; otherwise, the top element
    //               of the stack is returned.
    
    void pop();
    //Function to remove the top element of the stack.
    //Precondition: The stack exists and is not empty.
    //Postcondition: The stack is changed and the top
    //               element is removed from the stack.
    
    stackType(int stackSize = 100);
    //constructor
    //Create an array of the size stackSize to hold
    //the stack elements. The default stack size is 100.
    //Postcondition: The variable list contains the base
    //               address of the array, stackTop = 0, and
    //               maxStackSize = stackSize.
    
    stackType(const stackType<Type>& otherStack);
    //copy constructor
    
    void printStack();
    
    Type& operator[](int index);
    ~stackType();
    //destructor
    //Remove all the elements from the stack.
    //Postcondition: The array (list) holding the stack
    //               elements is deleted.
    
private:
    int maxStackSize; //variable to store the maximum stack size
    int stackTop;     //variable to point to the top of the stack
    Type *list;       //pointer to the array that holds the
    //stack elements
    
    void copyStack(const stackType<Type>& otherStack);
    //Function to make a copy of otherStack.
    //Postcondition: A copy of otherStack is created and
    //               assigned to this stack.
    
    void resizing(int capacity);
    //increase array capacity when stack is full.
};


template <class Type>
void stackType<Type>::initializeStack()
{
    stackTop = 0;
}//end initializeStack

template <class Type>
bool stackType<Type>::isEmptyStack() const
{
    return (stackTop == 0);
}//end isEmptyStack

template <class Type>
bool stackType<Type>::isFullStack() const
{
    return (stackTop == maxStackSize);
} //end isFullStack

template <class Type>
void stackType<Type>::push(const Type& newItem)
{
    if (isFullStack())
    {
        //if stack is full,double the capacity of array.
        resizing(maxStackSize * 2);
    }
    list[stackTop] = newItem;   //add newItem to the
    //top of the stack
    stackTop++; //increment stackTop
}//end push

template <class Type>
Type stackType<Type>::top() const
{
    assert(stackTop != 0);      //if stack is empty,
    //terminate the program
    return list[stackTop - 1];  //return the element of the
    //stack indicated by
    //stackTop - 1
}//end top

template <class Type>
void stackType<Type>::pop()
{
    if (!isEmptyStack())
        stackTop--;      //decrement stackTop
    else
        cout << "Cannot remove from an empty stack." << endl;
}//end pop

template <class Type>
stackType<Type>::stackType(int stackSize)
{
    if (stackSize <= 0)
    {
        cout << "Size of the array to hold the stack must "
        << "be positive." << endl;
        cout << "Creating an array of size 100." << endl;
        
        maxStackSize = 100;
    }
    else
        maxStackSize = stackSize;   //set the stack size to
    //the value specified by
    //the parameter stackSize
    
    stackTop = 0;                   //set stackTop to 0
    list = new Type[maxStackSize];  //create the array to
    //hold the stack elements
}//end constructor

template <class Type>
stackType<Type>::~stackType() //destructor
{
    delete [] list; //deallocate the memory occupied
    //by the array
}//end destructor

template <class Type>
// copy function
void stackType<Type>::copyStack(const stackType<Type>& otherStack)
{
    delete [] list;
    maxStackSize = otherStack.maxStackSize;
    stackTop = otherStack.stackTop;
    
    list = new Type[maxStackSize];
    
    //copy otherStack into this stack
    for (int j = 0; j < stackTop; j++)
        list[j] = otherStack.list[j];
} //end copyStack

template<class Type>
// Increase array capacity when stack is full.
void stackType<Type>::resizing(int capacity) {
    // Hold the original memory.
    Type* oldData = list;
    
    maxStackSize = capacity; // Change the max stack size.
    
    list = new Type[maxStackSize]; // Get new memory for new array.
    
    // Copy old data into new array.
    for (int j = 0; j < stackTop; j++)
        list[j] = oldData[j];
    
    // Release original memory.
    delete[] oldData;
}

// copy constructor
template <class Type>
stackType<Type>::stackType(const stackType<Type>& otherStack)
{
    list = nullptr;
    
    copyStack(otherStack);
}//end copy constructor


template <class Type>
const stackType<Type>& stackType<Type>::operator=
(const stackType<Type>& otherStack)
{
    if (this != &otherStack) //avoid self-copy
        copyStack(otherStack);
    
    return *this;
} //end operator=

// list all the elements in the stack
template <class Type>
void stackType<Type>::printStack(){
    // Initialize index -> pointing to the value at the very top of the stack.
    int index = stackTop-1;
    // Use while loop to print each value from top to bottom.
    while(index >= 0){
        cout << list[index] << " ";
        // Decrease index by 1 to print values below.
        index--;
    }
    cout << endl;
}

// Iterate through the stack and change one of the values based on its position
template <class Type>
Type& stackType<Type>::operator[](int index){
    // Check if index is out of bound
    if(index < 0 || index >= stackTop){
        throw string("Index out of bounds");
    }
    return list[stackTop - index - 1];
}

// pushOperations : total value added to stack
// popOperations : remove the total value from the stack
// rounds: the amount of rounds for performing pushOperations and popOperations.
void stackOperations(stackADT<int> & stack, int pushOperations, int popOperations, int rounds) {
    for (int i = 0; i < rounds; i++) {
        // Add values to the stack.
        for (int i = 0; i < pushOperations; i++) {
            stack.push(i);
        }
        // Remove values from the stack.
        for (int i = 0; i < popOperations; i++) {
            stack.pop();
        }
    }
}


int main(){
    // Create an empty array based stack.
    stackType<int> arrayStack;
    // Add values to arrayStack
    for (int i = 0; i < 10; i++) {
        arrayStack.push(i);
    }
    
    cout << "a." << " List all the elements in the stack." << endl;
    // Print all the elements in the stack
    arrayStack.printStack();
    cout << endl;
    
    cout << "b." << " Iterate through the stack and change one of the values based on its position." << endl;
    // Print stack
    for(int i = 0; i < 10; i++){
        cout << arrayStack[i] << " ";
    }
    cout << endl;
    // Use operator[] -> change the value at index 8 to 11
    arrayStack[8] = 17;
    // Use operator[] -> change the value at index 1 to 100
    // arrayStack[1] = 19;
    // Use operator[] -> print stack with the updated values
    for(int i = 0; i < 10; i++){
        cout << arrayStack[i] << " ";
    }
    cout << endl;
}

