/*
delete_from_left.cpp
Herman Lin

Finds the least number of moves needed to make two strings equal
through removing the left most character(s)
*/

#include <iostream>
#include <string>
using namespace std;

void delFromLeft(const string& stringA, const string& stringB);

int main() {
    string stringA, stringB;

    getline(cin, stringA);
    getline(cin, stringB);

    delFromLeft(stringA, stringB);
}

void delFromLeft(const string& stringA, const string& stringB) { 
    /*
    int aLen = stringA.length();
    int bLen = stringB.length();
    //if either of the strings are empty
    if (!aLen || !bLen) {
        if (!aLen && !bLen) {
            cout << 0 << endl;
        } else if (!aLen) {
            cout << bLen << endl;
        } else {
            cout << aLen << endl;
        }
    }
    //if the ends of the strings are not the same, return the sum of the string of the length
    else if (stringA[aLen - 1] != stringB[bLen - 1]) {
        cout << aLen + bLen << endl;
    }
    else {
        string bigWord;
        string smallWord;
        int bigWordLen, smallWordLen;
        if (aLen > bLen) {
            bigWord = stringA;
            bigWordLen = aLen;
            smallWord = stringB;
            smallWordLen = bLen;
        } else {
            bigWord = stringB;
            bigWordLen = bLen;
            smallWord = stringA;
            smallWordLen = aLen;
        }
         
        //find how far along the strings you need to travel to get the same string
        int backCount = 0;
        while (smallWord[smallWordLen - 1] == bigWord[bigWordLen - 1]) {
            backCount++;
            smallWordLen--;
            bigWordLen--;
        }
        int removeFromA = aLen - backCount;
        int removeFromB = bLen - backCount;
        cout << removeFromA + removeFromB << endl;
    }
    */

    /*
    loop from the back
    count how many char is the same
    subtract
    */
    int alen = stringA.length();
    int blen = stringB.length();
    for (int i = 1; i <= min(alen, blen); i++) {
        char ca = stringA[alen - i];
        char cb = stringB[blen - i];
    
    
    
    }
}