//
//  HW2_Problem_3.cpp
//
//
//  Created by Amy Zhang on 11/1/20.
//

// 3. Test a stack's speed (with millions of operations) as to which is faster: an array based stack or a linked list based stack.

// ANS: Array based stack is FASTER!

#include <iostream>
#include<ctime>
#include<cstdlib>
#include <chrono>
#include<vector>
#include <cassert>
#define H_StackType
#define H_StackADT
using std::chrono::system_clock;
using std::chrono::steady_clock;
using std::chrono::duration_cast;
using std::chrono::seconds;
using std::chrono::milliseconds;
using namespace std;

template<class Type>
class stackADT {
    
public:
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
//increase array capacity when stack is full.
void stackType<Type>::resizing(int capacity) {
    //hold the original memory;
    Type* oldData = list;
    
    maxStackSize = capacity;//change the  max stack size.
    
    list = new Type[maxStackSize];// get new memory for new array.
    
    //copy old data into new array
    for (int j = 0; j < stackTop; j++)
        list[j] = oldData[j];
    
    //release original memory
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
const stackType<Type>& stackType<Type>::operator=(const stackType<Type>& otherStack)
{
    if (this != &otherStack) //avoid self-copy
        copyStack(otherStack);
    
    return *this;
} //end operator=

// Used for timing
template <typename Func>

long long TimeFunc(Func f)
{
    auto begin = steady_clock::now();
    f();
    auto end = steady_clock::now();
    
    return duration_cast<milliseconds>(end - begin).count();
}

// pushOperations : total values added to stack
// popOperations : remove the total values from the stack
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

// LINKED LIST STACK TYPE
//Definition of the node
template <class Type>
struct nodeType
{
    Type info;
    nodeType<Type> *link;
};

template <class Type>
class linkedStackType: public stackADT<Type>
{
public:
    const linkedStackType<Type>& operator=
    (const linkedStackType<Type>&);
    //Overload the assignment operator.
    
    bool isEmptyStack() const;
    //Function to determine whether the stack is empty.
    //Postcondition: Returns true if the stack is empty;
    //               otherwise returns false.
    
    bool isFullStack() const;
    //Function to determine whether the stack is full.
    //Postcondition: Returns false.
    
    void initializeStack();
    //Function to initialize the stack to an empty state.
    //Postcondition: The stack elements are removed;
    //               stackTop = nullptr;
    
    void push(const Type& newItem);
    //Function to add newItem to the stack.
    //Precondition: The stack exists and is not full.
    //Postcondition: The stack is changed and newItem
    //               is added to the top of the stack.
    
    Type top() const;
    //Function to return the top element of the stack.
    //Precondition: The stack exists and is not empty.
    //Postcondition: If the stack is empty, the program
    //               terminates; otherwise, the top
    //               element of the stack is returned.
    
    void pop();
    //Function to remove the top element of the stack.
    //Precondition: The stack exists and is not empty.
    //Postcondition: The stack is changed and the top
    //               element is removed from the stack.
    
    linkedStackType();
    //Default constructor
    //Postcondition: stackTop = nullptr;
    
    linkedStackType(const linkedStackType<Type>& otherStack);
    //Copy constructor
    
    ~linkedStackType();
    //Destructor
    //Postcondition: All the elements of the stack are
    //               removed from the stack.
    
private:
    nodeType<Type> *stackTop; //pointer to the stack
    
    void copyStack(const linkedStackType<Type>& otherStack);
    //Function to make a copy of otherStack.
    //Postcondition: A copy of otherStack is created and
    //               assigned to this stack.
};


//Default constructor
template <class Type>
linkedStackType<Type>::linkedStackType()
{
    stackTop = nullptr;
}

template <class Type>
bool linkedStackType<Type>::isEmptyStack() const
{
    return(stackTop == nullptr);
} //end isEmptyStack

template <class Type>
bool linkedStackType<Type>:: isFullStack() const
{
    return false;
} //end isFullStack

template <class Type>
void linkedStackType<Type>:: initializeStack()
{
    nodeType<Type> *temp; //pointer to delete the node
    
    while (stackTop != nullptr)  //while there are elements in
        //the stack
    {
        temp = stackTop;    //set temp to point to the
        //current node
        stackTop = stackTop->link;  //advance stackTop to the
        //next node
        delete temp;    //deallocate memory occupied by temp
    }
} //end initializeStack


template <class Type>
void linkedStackType<Type>::push(const Type& newElement)
{
    nodeType<Type> *newNode;  //pointer to create the new node
    
    newNode = new nodeType<Type>; //create the node
    
    newNode->info = newElement; //store newElement in the node
    newNode->link = stackTop; //insert newNode before stackTop
    stackTop = newNode;       //set stackTop to point to the
    //top node
} //end push


template <class Type>
Type linkedStackType<Type>::top() const
{
    assert(stackTop != nullptr); //if stack is empty,
    //terminate the program
    return stackTop->info;    //return the top element
}//end top

template <class Type>
void linkedStackType<Type>::pop()
{
    nodeType<Type> *temp;   //pointer to deallocate memory
    
    if (stackTop != nullptr)
    {
        temp = stackTop;  //set temp to point to the top node
        
        stackTop = stackTop->link;  //advance stackTop to the
        //next node
        delete temp;    //delete the top node
    }
    else
        cout << "Cannot remove from an empty stack." << endl;
}//end pop

template <class Type>
void linkedStackType<Type>::copyStack(const linkedStackType<Type>& otherStack)
{
    nodeType<Type> *newNode, *current, *last;
    
    if (stackTop != nullptr) //if stack is nonempty, make it empty
        initializeStack();
    
    if (otherStack.stackTop == nullptr)
        stackTop = nullptr;
    else
    {
        current = otherStack.stackTop;  //set current to point
        //to the stack to be copied
        
        //copy the stackTop element of the stack
        stackTop = new nodeType<Type>;  //create the node
        
        stackTop->info = current->info; //copy the info
        stackTop->link = nullptr;  //set the link field of the
        //node to nullptr
        last = stackTop;        //set last to point to the node
        current = current->link;    //set current to point to
        //the next node
        
        //copy the remaining stack
        while (current != nullptr)
        {
            newNode = new nodeType<Type>;
            
            newNode->info = current->info;
            newNode->link = nullptr;
            last->link = newNode;
            last = newNode;
            current = current->link;
        }//end while
    }//end else
} //end copyStack

//copy constructor
template <class Type>
linkedStackType<Type>::linkedStackType(const linkedStackType<Type>& otherStack)
{
    stackTop = nullptr;
    copyStack(otherStack);
}//end copy constructor

//destructor
template <class Type>
linkedStackType<Type>::~linkedStackType()
{
    initializeStack();
}//end destructor

// Overloading the assignment operator
template <class Type>
const linkedStackType<Type>& linkedStackType<Type>::operator=(const linkedStackType<Type>& otherStack)
{
    if (this != &otherStack) //avoid self-copy
        copyStack(otherStack);
    
    return *this;
}//end operator=


int main() {
    // pushOperations : total of values added to stack
    // popOperations : remove the total of values from the stack
    // rounds: the total rounds of pushOperation and popOperation of the stack.
    const int pushOperationTotal = 50000;
    const int popOperationTotal = 50000;
    const int rounds = 100;
    
    // Declare an array based stack
    stackType<int> arrStack;
    // stackOperationTimes variable will store the time needed to complete the stackOperation function for array based stack.
    long long stackOperationTimes = TimeFunc([&]() {stackOperations(arrStack, pushOperationTotal, popOperationTotal,rounds); });
    // Print the time that it takes to complete array stack operations.
    cout << "Array Based Stack Operations Time: " << stackOperationTimes << endl;
    
    // Declare a linked list based stack
    linkedStackType<int> listStack;
    // stackOperationTimes variable will store the time needed to complete the stackOperation function for linked list based stack.
    stackOperationTimes = TimeFunc([&]() {stackOperations(listStack, pushOperationTotal, popOperationTotal,rounds); });
    // Print the time that it takes to complete link list stack operations.
    cout << "Linked List Based Stack Operations Time: " << stackOperationTimes << endl;
}










