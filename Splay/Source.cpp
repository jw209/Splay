/*
*	Source program for testing the splay tree basic operations
*/

#include "Splay.h"
#include <iostream>
#include <chrono>

using namespace std;

int main()
{

    // record start time
    auto start = chrono::high_resolution_clock::now();

    Splay x;
    for (int i = 0; i < 1000000; i++) {
        x.insert(i);
    }

    cout << x.isFound(100000) << endl;

    // record end time
    auto finish = chrono::high_resolution_clock::now();

    chrono::duration<double> elapsed = finish - start;
    cout << "Elapsed time: " << elapsed.count() << " s\n";

    return 0;
}