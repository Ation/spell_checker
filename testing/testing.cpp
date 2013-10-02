#include "testing.h"

#include <iostream>

using namespace std;

void    StartTesting(testFunction *functions, int count)
{
    bool    result = true;

    for (int i=0; i<count; i++) {
        result = result && functions[i]();
    }

    cout << "Summary: " << (result ? "all pass" : "failed") << endl;
}

bool    ExecuteTestCases(TestCase *cases, int count) {
    bool result;
    int passCount = 0;
    int failCount = 0;

    for (int i=0; i < count; i++) {

        cout << "################################" << endl;

        cout << "Starting: " << cases[i].test_name << endl;
        try {
            result = cases[i].test_function();
            cout << "Result: " << (result ? (passCount++, "PASS") : (failCount++, "FAIL")) << endl;
        } catch (...) {
            cout << "Ended with exception" << endl;
        }

        cout << "################################" << endl << endl;
    }
    cout << "Total: " << passCount << " passed; " << failCount << " failed" << endl << endl;
    return failCount == 0;
}
