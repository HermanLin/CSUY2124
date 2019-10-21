#include <iostream>
#include <vector>
using namespace std;


int main() {

    bool can = true;
    int numRect, w, h;
    vector<int> heights;

    cin >> numRect >> w >> h;
    if (w > h) { heights.push_back(w); }
    else { heights.push_back(h); }

    for (size_t i = 1; i < numRect; i++) {
        cin >> w >> h;
        int prevH = heights[i-1];
        int big = max(w, h);
        int small = min(w, h);

        if (big > prevH) {
            if (small > prevH) {
                can = false;
                break;
            }
            else { heights.push_back(small); }
        }
        else { heights.push_back(big); }
    }

    if (can) { cout << "YES"; }
    else { cout << "NO"; }
}