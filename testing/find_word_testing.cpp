#include <iostream>

#include "find_word_testing.h"

#include "testing.h"
#include <spelling_dictionary.h>

using namespace spell_checker;
using namespace std;

static bool FindWord();

static TestCase	cases[] = {
    {"Find word", FindWord}
};

void
StartAddWordTesting() {
    bool result;
    int passCount = 0;
    int failCount = 0;

    for (int i=0; i<sizeof(cases)/sizeof(*cases); i++) {

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
}


bool FindWord()
{
    SpellingDictionary  dict;

    const string str("word");

    dict.AddWord(str);

    vector<string>  searchResult = dict.GetWordOptions(str, 2);
    if (searchResult.size() != 1) {
        return false;
    }

    if (searchResult[0] != str) {
        return false;
    }

    return true;
}
