#include "tests.h"
#include "iostream"
using namespace std;

int main() {
    int failed = 0;

    failed += cube_tests();
    failed += neural_net_tests();

    if (failed) cout << "Failed " << failed << " tests" << endl;
    else cout << "All tests passed" << endl;
}
