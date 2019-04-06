//
//  main.cpp
//  ControlWork03.04.19
//
//  Created by Даниил Мишкин on 03/04/2019.
//  Copyright © 2019 Даниил Мишкин. All rights reserved.
//

#include <iostream>

using namespace std;

const int stringSize = 256;

typedef char*(*Rule)(char*);

char* inputString();
int inputLenth();
char* code(char*);
void task(char*, int, Rule);
void stringReplace(char* , char* , char* );
int substringPosition(char*, char*, int);

int main(int argc, const char * argv[]) {
    char* string = inputString();
    
    int n = inputLenth();
    
    task(string, n, code);
    
    cout << string << endl;
    
    return 0;
}


char* inputString() {
    char* string = new char[stringSize];
    
    cout << "Input your string: ";
    cin.getline(string, stringSize);
    
    return string;
}

int inputLenth() {
    int n;
    cout << "Input lenth of word: ";
    cin >> n;
    
    return n;
}

char* code(char* word) {
    char* codedWord = new char[stringSize];
    
    const char* symbolsUp = "ZYXWVUTSRQPONMLKJIHGFEDCBA";
    const char* symbolsDown = "zyxwvutsrqponmlkjihgfedcba";
    
    int length = 0;
    
    for (int i = 0; i < strlen(word); i++) {
        
        for (int j = 0; j < strlen(symbolsUp); j++) {
            
            if (word[i] == symbolsUp[j] || word[i] == symbolsDown[j]) {
                
                codedWord[length] = '{';
                length++;
                
                if (j > 9) {
                    
                    codedWord[length] = 48 + (j+1) / 10;
                    length++;
                }
                
                codedWord[length] = 48 + (j+1) % 10;
                length++;
                
                codedWord[length] = '}';
                length++;
            }
        }
    }
    
    codedWord[length] = '\0';
    
    return codedWord;
}

void task(char* string, int count, Rule Rule) {
    char* str = new char[stringSize];
    strcpy(str, string);
    char* newString = strtok(str, " ,.!?");
    while (newString != NULL) {
        
        if (strlen(newString) == count) {
            
            stringReplace(string, newString, Rule(newString));
        }
        
        newString = strtok(NULL, " ,.-!?");
    }
    
    delete[] newString;
    delete[] str;
}


void stringReplace(char* str, char* substing, char* replace) {
    char* newString = new char[stringSize];
    
    int newLength = strlen(replace),
    oldLength = strlen(substing),
    sLength = strlen(str),
    start = 0,
    oldStart = 0,
    count = 0,
    difference = newLength - oldLength;
    
    int index = substringPosition(str, substing, start);
    
    for (int i = 0; i < index; i++) {
        newString[i] = str[i];
    }
    
    while (index != -1) {
        for (int j = index + count * (difference), i = 0; j < index + newLength + count * (difference); j++, i++) {
            newString[j] = replace[i];
        }
        start = index + newLength;
        
        int newIndex = substringPosition(str, substing, start);
        
        while (newIndex != -1) {
            for (int i = index + newLength + count * (difference), j = index + oldLength; j < newIndex; i++, j++) {
                newString[i] = str[j];
            }
            
            break;
        }
        
        while (newIndex == -1) {
            for (int i = index + newLength + count * (difference), j = index + oldLength; j < sLength; i++, j++) {
                newString[i] = str[j];
            }
            
            break;
        }
        
        index = substringPosition(str, substing, start);
        count++;
    }
    
    newString[strlen(str) + difference] = '\0';
    strcpy(str, newString);
}

int substringPosition(char* str, char* substring, int start) {
    
    int n = strlen(str);
    int m = strlen(substring);
    
    if (m > n) {
        
        return -1;
    }
    
    int count = 0,
    index = -1;
    
    for (int i = start; i < n; i++) {
        
        for (int j = 0; j < m; j++) {
            
            if (substring[j] == str[i + count]) {
                
                index = i;
                count++;
                if (j == m - 1) {
                    
                    return index;
                }
            } else {
                
                index = -1;
                count = 0;
                break;
            }
        }
    }
    return index;
}
