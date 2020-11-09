//
//  main.cpp
//  HW2_Problem 6
//
//  Created by Amy Zhang on 11/1/20.
//  Copyright © 2020 Amy Zhang. All rights reserved.
//

// 6. Use a stack to pass in a string and reverse each word in the string. For instance, if you have the string “​When Chuck Norris falls in water, Chuck Norris doesn't get wet. Water gets Chuck Norris.​” It should now say, “​nehW kcuhC sirroN sllaf ni retaw, ...​” That is, it should take in one string and be a function (or multiple functions) that use a stack (or multiple stacks) to reverse each word in the sentence. Create a text file that you input of Chuck Norris jokes and have the program reverse each of the jokes. [Here is some help if you want ot teg detracts: https://www.techiedelight.com/reverse-string-without-using-recursion/

#include <iostream>
#include <stack>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cctype>
#include <sstream>
using namespace std;

// reverse function will reverse words.
string reverse(string str, int size){
    
    // Create an empty stack to store characters.
    stack<char> s;
    // Push elements from input str into stack "s". s will contain all the words store in str and input str will be empty.
    for(int i = 0; i < size - 1; i++){
        s.push(str[i]);
    }
    
    // Check if the last character is a punctuation. If not, push it into stack, otherwise skip it.
    // e.x. -> str is "word.", after reversing, it should be "drow." instead of ".drow", therefore, if last character is punctuation, we don't push it into stack.)
    // Use ispunct function to check if last character is a punctuation
    // size - 1 is the index of the last character.
    if (!ispunct(str[size - 1])) {
        s.push(str[size - 1]);
    }
    
    // In while loop, ++k will be 0, and we want index to start from 0.
    int k = - 1;
    // Goes through the stack and pop each element until it's empty, will assign the values from top to bottom of stack back to input str.
    while(!s.empty()){
        // Assign the top most element to the first index of input str.
        str[++k] = s.top();
        // Remove top element.
        s.pop();
    }
    return str;
}


int main() {
    // Creating an ifstream object to read in text.
    ifstream inputFile;
    string line;
    // Opens the file in order to read it
    inputFile.open("Chuck Norris Jokes.txt");
    
    // Check if file is open. If not open, it probably means that the file is not found.
    if (inputFile.is_open()) {
        // Outer while loop: read each line in the file and store into variable line.
        while (getline(inputFile, line)) {
            // Use stringstream to tokenize each word.
            stringstream wordStream(line);
            // Declare a string variable word to store words.
            string word;
            // Inner while loop: read each word in the line and store into variable word.
            while (getline(wordStream, word,' ')) {
                // size stores the length of each word
                int size = word.length();
                // Call reverse function to reverse each word in the line, and then print it.
                cout << reverse(word, size) << " ";
            }
            cout << endl;
        }
        // Close the file
        inputFile.close();
    }
    else {
        // File not open, it's likely that the file is not found.
        cout << "File not found or Not able to open file" << endl;
    }
}
