#include <iostream>
#include "fast_list.h"

using namespace std;

int main() {
    fast_list<int> fl = {1, 2, 3, 4, 5};
    auto a = ++fl.begin();
    auto b = ++++++fl.begin();
    fl.erase(a, b);
    for(int n : fl)
        cout << n << endl;
    return 0;
}