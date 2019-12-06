// rec13.cpp
// Herman Lin

#include <iostream>
#include <fstream>
#include <vector>      // task 1
#include <list>        // task 2
#include <algorithm>   // task 3
#include <string>      // task 21
#include <set>         // task 22
#include <map>         // task 23
using namespace std;

/* FUNCTION FOR TASK 9 */
void printListIter(const list<int>& lst) {
    // for (list<int>::iterator iter = lst.begin(); iter != lst.end(); ++iter)...
    //  -- does not work because we are working with a const list<int>&
    for (list<int>::const_iterator iter = lst.begin(); iter != lst.end(); ++iter) {
        cout << *iter << ' ';
    }
    cout << endl;
}

/* FUNCTION FOR TASK 10 */
void printListRanged(const list<int>& lst) {
    for (int i : lst) cout << i << ' ';
    cout << endl;
}

/* FUNCTION FOR TASK 11 */
void printEveryOther(const list<int>& lst) {
    for (auto iter = lst.begin(); iter != lst.end(); ++iter) {
        cout << *iter << ' ';
        ++iter;
    }
    cout << endl;
}

/* FUNCTION FOR TASK 12 */
list<int>::const_iterator findItem(const list<int>& lst, int val) {
    for (list<int>::const_iterator iter = lst.begin(); iter != lst.end(); ++iter) {
        if (*iter == val) return iter;
    }
    return lst.end();
}

/* FUNCTION FOR TASK 13 */
auto findItemAuto(const list<int>& lst, int val) {
    for (auto iter = lst.begin(); iter != lst.end(); ++iter) {
        if (*iter == val) return iter;
    }
    return lst.end();
}

/* FUNCTION FOR TASK 15 */
bool isEven(int val) { return val % 2 == 0; }

/* CLASS FOR TASK 16 */
class Task16 {
public:
    bool operator() (int val) { return val % 2 == 0; }
};

/* FUNCTION FOR TASK 19 */
list<int>::const_iterator ourFind(list<int>::iterator bgn, list<int>::iterator end, int val) {
    cout << "this is MY find function, not yours >:(" << endl;
    for (list<int>::const_iterator iter = bgn; iter != end; ++iter) {
        if (*iter == val) return iter;
    }
    return end;
}

/* FUNCTION TEMPLATE FOR TASK 20 */
template <typename T, typename U>
T ourFind(T bgn, T end, U val) {
    cout << "this is MY find function template, not yours >>:(" << endl;
    for (T iter = bgn; iter != end; ++iter) if (*iter == val) return iter;
    return end;
}

int main() {
    // 1. Create a vector with some values and display using ranged for
    cout << "Task 1:\n";
    vector<int> task1 = {0,5,2,2,3,1,6,4};
    for (int i : task1) cout << i << ' ';
    cout << "\n=======\n";

    // 2. Initalize a list as a copy of values from the vector
    cout << "Task 2:\n";
    list<int> task2(task1.begin(), task1.end());
    for (int i : task2) cout << i << ' ';
    cout << "\n=======\n";

    // 3. Sort the original vector.  Display both the vector and the list
    cout << "Task 3:\n";
    sort(task1.begin(), task1.end());
    cout << "Vector: ";
    for (int i : task1) cout << i << ' ';
    cout << "\nList: ";
    for (int i : task2) cout << i << ' ';
    cout << "\n=======\n";

    // 4. print every other element of the vector.
    cout << "Task 4:\n";
    for (size_t i = 0; i < task1.size(); i += 2) cout << task1[i] << ' ';
    cout << "\n=======\n";

    // 5. Attempt to print every other element of the list using the
    //    same technique.
    cout << "Task 5:\n";
    // for (size_t i = 0; i < task2.size(); i += 2) cout << task2[i] << ' ';
    cout << "does not work because list does not have an operator[]";
    cout << "\n=======\n";

    // //
    // // Iterators
    // //

    // 6. Repeat task 4 using iterators.  Do not use auto;
    cout << "Task 6:\n";
    for (vector<int>::iterator iter = task1.begin(); iter != task1.end(); iter += 2) cout << *iter << ' ';
    cout << "\n=======\n";

    // 7. Repeat the previous task using the list.  Again, do not use auto.
    //    Note that you cannot use the same simple mechanism to bump
    //    the iterator as in task 6.
    cout << "Task 7:\n";
    // for (list<int>::iterator iter = task2.begin(); iter != task2.end(); iter += 2) cout << *iter << ' ';
    // -- does not work because list does not have an operator+=
    for (list<int>::iterator iter = task2.begin(); iter != task2.end(); ++iter) {
        cout << *iter << ' ';
        ++iter;
    }
    cout << "\n=======\n";

    // 8. Sorting a list
    cout << "Task 8:\n";
    cout << "Before List::sort(): ";
    for (int i : task2) cout << i << ' ';
    cout << "\nAfter List::sort(): ";
    task2.sort();
    for (int i : task2) cout << i << ' ';
    cout << "\n=======\n";

    // 9. Calling the function to print the list
    cout << "Task 9:\n";
    printListIter(task2);
    cout << "=======\n";

    // 10. Calling the function that prints the list, using ranged-for
    cout << "Task 10:\n";
    printListRanged(task2);
    cout << "=======\n";

    // //
    // // Auto
    // //

    // 11. Calling the function that, using auto, prints alterate
    // items in the list
    cout << "Task 11:\n";
    printEveryOther(task2);
    cout << "=======\n";

    
    // 12.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 12:\n";
    cout << "List: ";
    printListRanged(task2);
    cout << "Searching list for 3...: ";
    list<int>::const_iterator three = findItem(task2, 3);
    cout << *three << endl;
    cout << "Searching list for 10...: ";
    list<int>::const_iterator ten = findItem(task2, 10);
    cout << *ten << endl;
    cout << "=======\n";

    // 13.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 13:\n";
    cout << "List: ";
    printListRanged(task2);
    cout << "Searching list for 4...: ";
    list<int>::const_iterator four = findItemAuto(task2, 4);
    cout << *four << endl;
    cout << "Searching list for 11...: ";
    list<int>::const_iterator eleven = findItemAuto(task2, 11);
    cout << *eleven << endl;
    cout << "=======\n";

    // //
    // // Generic Algorithms
    // //

    // 14. Generic algorithms: find
    cout << "Task 14:\n";
    cout << "List: ";
    printListRanged(task2);
    cout << "Using algorithm::find() to search for 5...: ";
    list<int>::iterator five = find(task2.begin(), task2.end(), 5);
    cout << *five << endl;
    cout << "=======\n";

    // 15. Generic algorithms: find_if
    cout << "Task 15:\n";
    cout << "Vector: ";
    for (int i : task1) cout << i << ' ';
    cout << endl;
    cout << "List: ";
    printListRanged(task2);
    cout << "Using algorithm::find_if(isEven) on vector...: ";
    vector<int>::iterator evenV = find_if(task1.begin(), task1.end(), isEven);
    cout << *evenV << endl;
    cout << "Using algorithm::find_if(isEven) on list...: ";
    list<int>::iterator evenL = find_if(task2.begin(), task2.end(), isEven);
    cout << *evenL << endl;
    cout << "=======\n";

    // 16. Functor
    cout << "Task 16:\n";
    Task16 task16;
    cout << "List: ";
    printListRanged(task2);
    cout << "Using a functor with algorithm::find_if(isEven) on list...: ";
    list<int>::iterator evenL2 = find_if(task2.begin(), task2.end(), task16);
    list<int>::iterator evenL3 = find_if(task2.begin(), task2.end(), Task16());
    cout << *evenL2 << " or " << *evenL3 << endl;
    cout << "=======\n";
    
    // 17. Lambda
    cout << "Task 17:\n";
    cout << "List: ";
    printListRanged(task2);
    cout << "Using a lambda expression with algorithm::find_if(isEven) on list...: ";
    list<int>::iterator evenL4 = 
        find_if(task2.begin(), task2.end(), [] (int val) { return val % 2 == 0; });
    cout << *evenL4 << endl;
    cout << "=======\n";

    // 18. Generic algorithms: copy to an array
    cout << "Task 18:\n";
    int locArr [8];
    copy(task1.begin(), task1.end(), locArr);
    for (int i : locArr) cout << i << ' ';
    cout << "\nUsing algorithm::find() on locArr to find 3...: ";
    int* three2 = find(locArr, locArr + 8, 3);
    cout << *three2 << endl;
    cout << "=======\n";

    // //
    // // Templated Functions
    // //

    // 19. Implement find as a function for lists
    cout << "Task 19:\n";
    cout << "List: ";
    printListRanged(task2);
    cout << "Testing ourFind() for 3...: " << endl;
    list<int>::const_iterator three3 = ourFind(task2.begin(), task2.end(), 3);
    cout << "Found: " << *three3 << endl;
    cout << "=======\n";
    
    // 20. Implement find as a templated function
    cout << "Task 20:\n";
    cout << "Vector: ";
    for (int i : task1) cout << i << ' ';
    cout << endl;
    cout << "List: ";
    printListRanged(task2);
    cout << "Testing ourFind() for 3 on vector...: " << endl;
    vector<int>::const_iterator three4 = ourFind(task1.begin(), task1.end(), 3);
    cout << "Found: " << *three4 << endl;
    cout << "Testing ourFind() for 3 on list...: " << endl;
    list<int>::const_iterator three5 = ourFind(task2.begin(), task2.end(), 3);
    cout << "Found: " << *three5 << endl;
    cout << "=======\n";

    // //
    // // Associative collections
    // //

    ifstream file;
    string word;

    // 21. Using a vector of strings, print a line showing the number
    //     of distinct words and the words themselves.
    cout << "Task 21:\n";
    file.open("pooh-nopunc.txt");
    vector<string> wordsFound;
    while (file >> word) {
        if (find(wordsFound.begin(), wordsFound.end(), word) == wordsFound.end()) {
            wordsFound.push_back(word);
        }
    }
    cout << "Number of Unique Words Found: " << wordsFound.size() << endl;
    cout << "wordsFound: " << endl;
    for (const string& wrd : wordsFound) cout << wrd << ' ';
    file.close();
    cout << "\n=======\n";

    // 22. Repeating previous step, but using the set
    cout << "Task 22:\n";
    file.open("pooh-nopunc.txt");
    set<string> setOfWordsFound;
    while (file >> word) setOfWordsFound.insert(word);
    cout << "Number of Unique Words Found: " << setOfWordsFound.size() << endl;
    cout << "setOfWordsFound: " << endl;
    for (const string& wrd : setOfWordsFound) cout << wrd << ' ';
    file.close();
    cout << "\n=======\n";

    // 23. Word co-occurence using map
    cout << "Task 23:\n";
    file.open("pooh-nopunc.txt");
    int position = 0;
    map<string, vector<int>> wordMap;
    while (file >> word) {
        wordMap[word].push_back(position);
        ++position;
    }
    cout << "Number of Unique Words Found: " << wordMap.size() << endl;
    cout << "wordMap: " << endl;
    for (const auto& pair : wordMap) {
        cout << pair.first << ": < ";
        for (int i : pair.second) cout << i << ' ';
        cout << '>' << endl;
    }

    file.close();

    cout << "=======\n";
}
