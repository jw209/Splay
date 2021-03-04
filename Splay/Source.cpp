/*
*	Source program for testing the splay tree basic operations
*/

#include "Splay.h"
#include <iostream>

using namespace std;

int main()
{
    Splay x;
    for (int i = 0; i < 1000000; i++) {
        x.insert(i);
    }

    cout << x.isFound(-1042) << endl;

    return 0;
}