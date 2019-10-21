/*========
rec02.cpp
Herman Lin
========*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

/*================
Hydrocarbon Struct
- name: contains a vector of hydrocarbon names
- numOfCarbons: number of carbons in the chemical formula
- numOfHydrogens: number of hydrogens in the chemical formula
================*/
struct Hydrocarbon {
    vector<string> name;
    int numOfCarbons;
    int numOfHydrogens;
};

//Prototypes
void openFile(ifstream& stream);
void fillHydrocarbonVec(ifstream& listOfHC, vector<Hydrocarbon>& hydrocarbons);
void insertHC(vector<Hydrocarbon>& Hydrocarbons, const string& name, int numOfC, int numOfH);
void insertHCHelper(vector<Hydrocarbon>& Hydrocarbons, const string& name, int numOfC, int numOfH);
void sortHydrocarbons(vector<Hydrocarbon>& hydrocarbons);
void printHydrocarbons(const vector<Hydrocarbon>& hydrocarbons);
string printHydrocarbonNames(const vector<string>& names);

int main() {
    ifstream fileOfHydrocarbons;
    vector<Hydrocarbon> Hydrocarbons;

    openFile(fileOfHydrocarbons);
    fillHydrocarbonVec(fileOfHydrocarbons, Hydrocarbons);
    cout << "\nBefore Sorting..." << endl;
    printHydrocarbons(Hydrocarbons);

    cout << "\nAfter Sorting..." << endl;
    sortHydrocarbons(Hydrocarbons);
    printHydrocarbons(Hydrocarbons);
}

/*==================
File Opener Function
- Read for a specific file to open from the ifstream 
==================*/
void openFile(ifstream& stream) {
    bool fileNotFound = true;
    while (fileNotFound) {
        stream.clear();

        //Request a file to read and store it in variable file_name
        string file_name;
        cout << "Enter a file name: " << endl;
        cin >> file_name;

        //Check if the file exists and open the file. If it doesn't exist, return an error message
        stream.open(file_name);
        if (!stream) {
            cerr << "Could not open the file '" << file_name << "'" << endl;
            stream.clear();
        }
        else { //Exit while loop
            fileNotFound = false;
        }
    }
}

/*====================
Vector Filler Function
- Read the ifstream and fill the vector with hydrocarbons appropriately
====================*/
void fillHydrocarbonVec(ifstream& fileOfHCs, vector<Hydrocarbon>& Hydrocarbons) {
    string name;
    char charSkip;
    int numOfC, numOfH;

    while (fileOfHCs >> name >> charSkip >> numOfC >> charSkip >> numOfH) {
        insertHC(Hydrocarbons, name, numOfC, numOfH);
    }
}

/*====================
Vector Insert Helper Function
- Finds if the same chemical formula is already in a vector of Hydrocarbons.
If there is an instance, add just the name
Else, add an new Hydrocarbon
====================*/
void insertHC(vector<Hydrocarbon>& Hydrocarbons, const string& name, int numOfC, int numOfH) {
    bool chemFormulaFound = false;
    for (Hydrocarbon& hydrocarbon : Hydrocarbons) {
        if (numOfC == hydrocarbon.numOfCarbons && numOfH == hydrocarbon.numOfHydrogens) {
            hydrocarbon.name.push_back(name);
            chemFormulaFound = true;
            break;
        } 
    }
    if (!chemFormulaFound) {
        insertHCHelper(Hydrocarbons, name, numOfC, numOfH);
    }
}

/*===========================
Vector Insert Function
- Inserts Hydrocarbons into a vector of Hydrocarbons
===========================*/
void insertHCHelper(vector<Hydrocarbon>& Hydrocarbons, const string& name, int numOfC, int numOfH) {
    Hydrocarbon newHydrocarbon;
    newHydrocarbon.name.push_back(name);
    newHydrocarbon.numOfCarbons = numOfC;
    newHydrocarbon.numOfHydrogens = numOfH;

    Hydrocarbons.push_back(newHydrocarbon);
}

/*==========================
Hydrocarbon Sorting Function
- Sort the vector containing hydrocarbons using bubble sort
==========================*/
void sortHydrocarbons(vector<Hydrocarbon>& Hydrocarbons) {
    for (size_t i = 0; i < Hydrocarbons.size(); i++) {
        for (size_t j = 0; j < Hydrocarbons.size() - 1; j++) {
            if (Hydrocarbons[j].numOfCarbons == Hydrocarbons[j + 1].numOfCarbons) {
                if (Hydrocarbons[j].numOfHydrogens > Hydrocarbons[j + 1].numOfHydrogens) {
                    Hydrocarbon tempHydrocarbon = Hydrocarbons[j];
                    Hydrocarbons[j] = Hydrocarbons[j + 1];
                    Hydrocarbons[j + 1] = tempHydrocarbon;
                }
            }
            else if (Hydrocarbons[j].numOfCarbons > Hydrocarbons[j + 1].numOfCarbons) {
                Hydrocarbon tempHydrocarbon = Hydrocarbons[j];
                Hydrocarbons[j] = Hydrocarbons[j + 1];
                Hydrocarbons[j + 1] = tempHydrocarbon;
            }
        }
    }
}

/*====================================
Vector of Hydrocarbons Print Functions
- Print the hydrocarbon vector
====================================*/
void printHydrocarbons(const vector<Hydrocarbon>& Hydrocarbons) {
    for (const Hydrocarbon& hydrocarbon: Hydrocarbons) {
        cout << 'C' << hydrocarbon.numOfCarbons << 'H' << hydrocarbon.numOfHydrogens 
        << " " << printHydrocarbonNames(hydrocarbon.name) << endl;
    }
}

//Print the vector of names in the Hydrocarbon struct
string printHydrocarbonNames(const vector<string>& names) {
    string hydrocarbonNames;
    for (const string& name : names) {
        hydrocarbonNames.append(name + " ");
    }
    return hydrocarbonNames;
}