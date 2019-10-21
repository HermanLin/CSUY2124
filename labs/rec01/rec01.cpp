/*========
rec01.cpp
Herman Lin
========*/

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main() {

    //Request a file to read and store it in variable file_name
    string file_name;
    cout << "Enter a file name: " << endl;
    cin >> file_name;

    //Check if the file exists and open the file. If it doesn't exist, return an error message
    ifstream file(file_name);
    if (!file) {
        cerr << "Could not open the file '" << file_name << "'" << endl;
        exit(1);
    }

    //string variable 'line' to store lines of a file
    string line;

    //Read the file line by line and print each line to the console
    while (getline(file, line)) {
        cout << line << endl;
    }

    //Close the file being read and reopen to reset the filestream
    file.close();
    file.open(file_name);

    //string variable 'word' to store words of a file 
    string word;
    //int variable 'word_count' to incrememnt as each word is passed 
    int word_count = 0;

    //Read the file token by token and increment 'word_count' by one every loop
    while (file >> word) {
        word_count++;
    }

    //Close the file being read
    file.close();

    //Print out the number of words in the file to the console
    cout << "\n'" << file_name << "' contains " << word_count << " words." << endl;
    return 0;
}