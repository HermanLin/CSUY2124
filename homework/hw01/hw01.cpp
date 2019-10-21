/*====================================================
hw01.cpp
Herman Lin

This file contains code that will be used to decrypt
encrypted files. The encrypted files are, for simplicity
named "encrypted.txt", encrypted using the Caesar cypher
algorithm and have their lines reversed, so that the
last line appears first in the file.

We will use the Caesar cypher to reverse the encryption 
and print the encrypted message in the correct order.
===================================================*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

char decryptChar(char character, int step);
void decryptString(string& encryptedString, int step);

/*===========
Main Function
===========*/
int main() {
	//Attempt to read file "encrypted.txt"; return an error if the file is not found
	ifstream encryptedFile("encrypted.txt");
	if (!encryptedFile) {
		cerr << "cannot find encrypted file 'encrypted.txt'";
		exit(1);
	}
	
	//create a string variable for the file's lines
	string line;
	//create a vector to store all the lines read from the file
	vector<string> fileLines;

	//get the first line of the file which contains the number of steps needed to decrypt
	getline(encryptedFile, line);
	//store the number in cypher_step
	int cypherStep = stoi(line);
	
	//iterate through the file line by line, adding each line to the fileLines vector
	while (getline(encryptedFile, line)) {
		fileLines.push_back(line);
	}

	//iterate through fileLines backwards to decrypt the file in the correct order
	int lastIndex = (int)fileLines.size() - 1; //ensure that the output will be an int
	for (int vectorIndex = lastIndex; vectorIndex >= 0; vectorIndex--) {
		decryptString(fileLines[vectorIndex], cypherStep);
		cout << fileLines[vectorIndex] << endl;
	}
	
	//close the file
	encryptedFile.close();
	return 0;
}

/*==========================
Character Decrypter Function
- Takes a character and an integer step to decrypt with
the Caesar cypher algorithm and returns the unencrypted character
==========================*/
char decryptChar(char character, int step) {
	
	//create a return variable
	char decryptedChar;

	//if the character is not a lowercase letter, return it
	if (character < 'a' || character > 'z' || step == 0) {
		return character;
	}
	//if character is less than 'a' after decrypting, go back to 'z'
	else if (character - 'a' < step) {
		int overflow = step - (character - 'a') - 1;
		decryptedChar = 'z' - overflow;
	}
	//base case: rotate the character 'step' steps
	else {
		decryptedChar = character - step;
	}

	//return decrypted character
	return decryptedChar;
}

/*=======================
String Decrypter Function
-  Modifies an encrypted string, changing it into its unencrypted form
=======================*/
void decryptString(string& encryptedString, int step) { //pass by reference
	for (char& character : encryptedString) {
		character = decryptChar(character, step);
	}
}