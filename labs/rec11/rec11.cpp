/* 
    rec11.cpp
    Herman Lin
*/

#include <iostream>
#include <vector>
using namespace std;

/*
  functions for use with CS2124 rec11
  -jbs
*/

// Node to be used a part of linked list
struct Node {
	Node(int data = 0, Node* next = nullptr) : data(data), next(next) {}
	int data;
	Node* next;
};

// listAddHead: adds a data item to the beginning of a [possibly empty] list
void listAddHead(Node*& headPtr, int entry) {
	headPtr = new Node(entry, headPtr);
}

// listClear: frees up all the nodes in a list
void listClear(Node*& headPtr) {
    while (headPtr) {
        Node* next = headPtr->next;
        delete headPtr;
        headPtr = next;
    }
}

// listBuild: constructs a list from a vector of data items. Note that
// you can use a curly-braced sequence.
// This may be useful for setting up test cases. Feel free to use it
// or not as you like. 
// Example of using would be:
//    Node* myList = listBuild({1, 4, 9, 16}); // builds a list of: 1 4 9 16
Node* listBuild(const vector<int>& vals) {
    Node* result = nullptr;
    for (size_t index = vals.size(); index > 0; --index) {
        listAddHead(result, vals[index-1]);
    }
    return result;
}

/* ================ */
/* HELPER FUNCTIONS */
/* ================ */
void printList(const Node* headptr) {
    while (headptr) {
        cout << headptr->data << ' ';
        headptr = headptr->next;
    }
    cout << endl;
}

Node* findLast(Node* headptr) {
    while (headptr->next) headptr = headptr->next;
    return headptr;
}
/* ================= */

/* ====================== */
/* FUNCTIONS TO IMPLEMENT */
/* ====================== */
void splice(Node* newList, Node* spliceFrom) {
    // check for nullptrs...
    // if newList is empty, don't splice
    // if spliceFrom is empty...
    if (!spliceFrom) {
        spliceFrom = newList;
    }
    else if (newList && spliceFrom) {
        // get respective end nodes
        Node* endSplice = spliceFrom->next;
        Node* endNewList = findLast(newList);

        // set the respective next nodes
        spliceFrom->next = newList;
        endNewList->next = endSplice;
    }
}

Node* isSublist(Node* sublist, Node* superlist) {
    // check for empty lists...
    if (!sublist) return superlist;
    if (!superlist) return nullptr;

    // check for matching nodes
    Node* match;
    while (superlist) {
        // cout << "OUTER checking if " << sublist->data << " = " << superlist->data << endl;
        if (superlist->data == sublist->data) {
            match = superlist;
            // superlist is now pointing at the match
            // loop through, checking for matches until the end of sublist
            Node* copyOfSub = sublist;
            Node* copyOfSuper = superlist;
            while (copyOfSub) {
                // check if reach end of superlist before sublist...
                if (!copyOfSuper) return nullptr;
                
                // cout << "INNER checking if " << copyOfSub->data << " = " << copyOfSuper->data << endl;

                // if data does not match...
                if (copyOfSuper->data != copyOfSub->data) break; // return nullptr;

                // loop through the lists...
                copyOfSuper = copyOfSuper->next;
                copyOfSub = copyOfSub->next;
            }
            // if reach end of sublist (all data matches)...
            if (!copyOfSub) return match;
        }
        superlist = superlist->next;
    }
    return nullptr;
}
/* ====================== */

int main() {
    cout << "======================Task 1=====================" << endl;
    cout << "Creating a new list 5->7->9->1 ..." << endl;
    Node* listA = listBuild({5, 7, 9, 1});
    cout << "listA: ";
    printList(listA);
    cout << "Creating a new list 6->3->2 ..." << endl;
    Node* listB = listBuild({6, 3, 2});
    cout << "listB: ";
    printList(listB);
    
    cout << "\nTesting findLast() on listA..." << endl;
    Node* lastOfA = findLast(listA);
    cout << "Last node of listA = " << lastOfA->data << endl;

    cout << "\nTesting splice()..." << endl;
    cout << "Splicing listB into listA at 7..." << endl;
    splice(listB, listA->next);
    cout << "listA after splicing: ";
    printList(listA);

    cout << "\nCreating a new empty list..." << endl;
    Node* emptyList = listBuild({});
    cout << "emptyList: ";
    printList(emptyList);

    cout << "\nSplicing the empty list into listA after 7..." << endl;
    splice(emptyList, listA->next);
    cout << "listA after splicing: ";
    printList(listA);

    cout << "\nCreating a new lists..." << endl;
    Node* willNotBeEmpty = listBuild({});
    Node* listC = listBuild({1, 2, 3});
    cout << "willNotBeEmpty: ";
    printList(willNotBeEmpty);
    cout << "listC: ";
    printList(listC);

    cout << "\nSplicing listC into emptyList..." << endl;
    splice(listC, willNotBeEmpty);
    cout << "willNotBeEmpty after splicing: ";
    printList(willNotBeEmpty);

    cout << "\nSplicing willNotBeEmpty to the end of listA..." << endl;
    lastOfA = findLast(listA);
    splice(willNotBeEmpty, lastOfA);
    cout << "listA after splicing: ";
    printList(listA);

    cout << "\nClearing Task 1 Lists..." << endl;
    // listA has been spliced with: willNotBeEmpty, listC, listB
    listClear(listA);
    // emptyList is alone
    listClear(emptyList);
    
    // cout << "\nChecking if lists have been cleared..." << endl;
    // cout << "listA: ";
    // printList(listA);
    // cout << "listB: ";
    // printList(listB);
    // cout << "emptyList: ";
    // printList(emptyList);
    // cout << "willNotBeEmpty: ";
    // printList(willNotBeEmpty);
    // cout << "listC: ";
    // printList(listC);

    cout << "=================================================" << endl;
    cout << endl;
    cout << "======================Task 2=====================" << endl;
    cout << "Creating a new list 5->7->6->3->2->9->1 ..." << endl;
    Node* bigList = listBuild({5, 7, 6, 3, 2, 9, 1});
    cout << "bigList: ";
    printList(bigList);
    cout << "Creating test cases for isSublist()..." << endl;
    Node* testA = listBuild({6, 2, 3});
    Node* testB = listBuild({2, 9, 1, 4});
    Node* testC = listBuild({7, 6, 3});
    Node* testD = listBuild({5, 7, 6, 3, 2, 9, 1});
    Node* testE = listBuild({});

    cout << "\ntestA: ";
    printList(testA);
    cout << "isSublist(testA, bigList)?" << endl;
    Node* ansA = isSublist(testA, bigList);
    cout << "ansA: ";
    printList(ansA);
    
    cout << "\ntestB: ";
    printList(testB);
    cout << "isSublist(testB, bigList)?" << endl;
    Node* ansB = isSublist(testB, bigList);
    cout << "ansB: ";
    printList(ansB);

    cout << "\ntestC: ";
    printList(testC);
    cout << "isSublist(testC, bigList)?" << endl;
    Node* ansC = isSublist(testC, bigList);
    cout << "ansC: ";
    printList(ansC);

    cout << "\ntestD: ";
    printList(testD);
    cout << "isSublist(testD, bigList)?" << endl;
    Node* ansD = isSublist(testD, bigList);
    cout << "ansD: ";
    printList(ansD);

    cout << "\ntestE: ";
    printList(testE);
    cout << "isSublist(testE, bigList)?" << endl;
    Node* ansE = isSublist(testE, bigList);
    cout << "ansE: ";
    printList(ansE);

    cout << "\ntestF" << endl;
    cout << "isSublist(bigList, testE)?" << endl;
    Node* ansF = isSublist(bigList, testE);
    cout << "ansF: ";
    printList(ansF);

    cout << "\nCreating specialList 2->2->2->2->4 ..." << endl;
    Node* specialList = listBuild({2, 2, 2, 2, 4});
    cout << "Creating a specialTestCase 2->2->2->4 ..." << endl;
    Node* specialTestCase = listBuild({2, 2, 2, 4});
    cout << "isSublist(specialTestCase, specialList)?" << endl;
    Node* ansS = isSublist(specialTestCase, specialList);
    cout << "ansS: ";
    printList(ansS);

    cout << "\nClearing Task 2 Lists..." << endl;
    listClear(bigList);
    listClear(testA);
    listClear(testB);
    listClear(testC);
    listClear(testD);
    listClear(testE);
    listClear(specialList);
    listClear(specialTestCase);
    cout << "=================================================" << endl;
}   