/* 
    rec14.cpp
    Herman Lin
*/

#include <iostream>
#include <vector>
#include <exception>
using namespace std;

struct Node {
    Node (int data = 0, Node* next = nullptr) : data(data), next(next) {}
    int data;
    Node* next;
};

struct TNode {
  TNode(int data = 0, TNode *left = nullptr, TNode *right = nullptr)
    : data(data), left(left), right(right) {}
  int data;
  TNode *left, *right;
};

/* ================ */
/* ==== TASK 1 ==== */
/* ================ */
bool evenNumOnes (int num) {
    // base cases
    if (num == 0) return true;
    if (num == 1) return false;

    return (!((num % 2) == evenNumOnes(num / 2)));
}

/* ================ */
/* ==== TASK 2 ==== */
/* ================ */
Node* sumLists (Node* aList, Node* bList) {
    // check for empty lists
    if (!aList && !bList) return nullptr;
    // if aList is not empty
    if (!bList) {
        Node* result = new Node(aList->data, sumLists(aList->next, bList));
        return result;
    }
    // if bList is not empty
    if (!aList) {
        Node* result = new Node(bList->data, sumLists(aList, bList->next));
        return result;
    }
    // if both lists are not empty
    Node* result = new Node(aList->data + bList->data, sumLists(aList->next, bList->next));
    return result;
}

/* Helpers for Task 2 */
// add element to a possibly empty list
void listAddHead(Node*& headPtr, int entry) {
	headPtr = new Node(entry, headPtr);
}
// create a list
Node* listBuild(const vector<int>& vals) {
    Node* result = nullptr;
    for (size_t index = vals.size(); index > 0; --index) {
        listAddHead(result, vals[index-1]);
    }
    return result;
}
// print a list
void printList(const Node* headptr) {
    while (headptr) {
        cout << headptr->data << ' ';
        headptr = headptr->next;
    }
    cout << endl;
}

/* ================ */
/* ==== TASK 3 ==== */
/* ================ */
int max(TNode* root) {
    // if the root is empty
    if (!root) throw invalid_argument("Empty Tree");

    // base case (only one node)
    if (!root->left && !root->right) return root->data;

    int maxTree = root->data;
    int maxLeft = root->data;
    int maxRight = root->data;
    // find max of left tree
    if (root->left) maxLeft = max(root->left);
    // find max of right tree
    if (root->right) maxRight = max(root->right);
    // return max of left or right tree or the root
    if (maxLeft > maxTree) maxTree = maxLeft;
    if (maxRight > maxTree) maxTree = maxRight;
    return maxTree;
}

/* ================ */
/* ==== TASK 4 ==== */
/* ================ */
bool palindrome (char str[], int length) {
    // base case (one letter)
    if (length == 1) return true;
    // base case (two letters)
    if (length == 2) {
        if (str[0] == str[1]) return true;
        return false;
    }
    return ((str[0] == str[length - 1]) && palindrome(&str[1], length - 2));
}

/* ================ */
/* ==== TASK 5 ==== */
/* ================ */
int hanoi (int numDisks, char start, char target, char spare) {
    // if there are no disks
    if (!numDisks) return 0;
    return 1 + 2*hanoi(numDisks - 1, start, target, spare);
}

/* ================ */
/* ==== TASK 6 ==== */
/* ================ */
void mystery(int n) { 
   if (n > 1) { 
      cout << 'a'; 
      mystery(n/2); 
      cout << 'b'; 
      mystery(n/2); 
   } 
   cout << 'c'; 
}

int main() {
    cout << "TASK 1 TEST CASES" << endl;
    /* TASK 1 TEST CASES */
    cout << boolalpha;
    cout << evenNumOnes(15) << endl; // T
    cout << boolalpha;
    cout << evenNumOnes(16) << endl; // F
    cout << boolalpha;
    cout << evenNumOnes(5) << endl; // T
    cout << boolalpha;
    cout << evenNumOnes(11) << endl; // F
    cout << "====================" << endl;

    cout << "TASK 2 TEST CASES" << endl;
    /* TASK 2 TEST CASES */
    Node* aL = listBuild({1, 2});
    Node* bL = listBuild({3, 4});
    Node* cL = sumLists(aL, bL);
    printList(cL); // should print {4, 6}
    Node* dL = listBuild({1, 3});
    Node* eL = listBuild({2});
    Node* fL = sumLists(dL, eL);
    printList(fL); // should print {3, 3}
    Node* gL = listBuild({1});
    Node* hL = listBuild({2, 3});
    Node* iL = sumLists(gL, hL);
    printList(iL); // should print {3, 3}
    cout << "====================" << endl;

    cout << "TASK 3 TEST CASES" << endl;
    /* TASK 3 TEST CASES */
    TNode a(1), b(2), c(4), d(8, &a, &b), e(16, &c), f(32, &d, &e);
    cout << max(&f) << endl;
    TNode g(4), h(6), i(8), j(2, &h, &i), k(1, &g, &j);
    cout << max(&k) << endl;
    cout << "====================" << endl;

    cout << "TASK 4 TEST CASES" << endl;
    /* TASK 4 TEST CASES */
    char s[] = "racecar";
    if (palindrome(s, 7)) cout << "Yes" << endl;
    else cout << "No" << endl;
    char t[] = "noon";
    if (palindrome(t, 4)) cout << "Yes" << endl;
    else cout << "No" << endl;
    char u[] = "abcde";
    if (palindrome(u, 5)) cout << "Yes" << endl;
    else cout << "No" << endl;

    cout << "TASK 5 TEST CASES" << endl;
    /* TASK 5 TEST CASES */
    cout << hanoi(1, 'a', 'b', 'c') << endl; // 1
    cout << hanoi(2, 'a', 'b', 'c') << endl; // 3
    cout << hanoi(3, 'a', 'b', 'c') << endl; // 7
    cout << hanoi(4, 'a', 'b', 'c') << endl; // 15
    cout << hanoi(5, 'a', 'b', 'c') << endl; // 31
    cout << hanoi(6, 'a', 'b', 'c') << endl; // 63
    cout << hanoi(7, 'a', 'b', 'c') << endl; // 127
    cout << hanoi(8, 'a', 'b', 'c') << endl; // 255
    cout << hanoi(9, 'a', 'b', 'c') << endl; // 511
    cout << hanoi(10, 'a', 'b', 'c') << endl; // 1023
    cout << "====================" << endl;

    cout << "TASK 6 TEST CASES" << endl;
    /* TASK 6 TEST CASES */
    for (int i = 0; i < 11; ++i) {
        mystery(i);
        cout << endl;
    }
    cout << "====================" << endl;    
}

  
  
