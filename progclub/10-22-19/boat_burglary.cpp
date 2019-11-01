/* Rachid lives on a boat, and owns only a few items, n to be precise. He takes big care of his items, and measured the weight of each of them with high precision. Item i weights Wi micrograms. One night a thief visits his boat and steels some items. Rachid notices that the next morning, because the boat is lighter, and he could measure from the water level that this difference is D micrograms. He would like to know how many items are missing, just by examining these weights, and asks you for help.

Input
The first line of the input consists of the number of test cases, T. T test cases follow. Each case consists of two lines, the first one containing two integers N and D, separated by a space. Then second line contains n integers, representing the weights of all items, separated by space.

The input satisfies the following limits.

1≤T≤20
1≤N≤30
0≤D≤3*1010
0≤Wi≤109

Output
For each test case output one line containing "Case #x: y", where x is the case number (starting from 1). If the number of missing items could be determined, then y is this number. If there are several answers to the problem y is the string "AMBIGIOUS" and if there is no answer y is the string "IMPOSSIBLE" (quotes added for clarity and are not part of the output).

Example
Input:
4
5 10
2 3 6 9 5
5 20
1 4 2 3 15
5 20
1 4 5 15 27
5 16
1 2 4 8 32

Output:
Case #1: 3
Case #2: 3
Case #3: AMBIGIOUS
Case #4: IMPOSSIBLE	 */

/* 
Sort vector
eliminate larger values
foo(# of e, sum, vector) 

Meet in the Middle Algorithm
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;



int main() {

}