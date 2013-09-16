#include <iostream>

#include "find_word_testing.h"

#include "testing.h"
#include <spelling_dictionary.h>

using namespace spell_checker;
using namespace std;

static bool FindWord();
static bool FindWordWhenCorrectionsArePossible();
static bool FindAllCorrections();

static TestCase	cases[] = {
    {"Find word", FindWord},
    {"Find word when corrections possible", FindWordWhenCorrectionsArePossible},
    {"Find all corrections", FindAllCorrections}
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

bool FindWordWhenCorrectionsArePossible()
{
    const string target("worda");
    const string opt1("wordb");
    const string opt2("word");
    const string opt3("wordab");

    SpellingDictionary  dict;

    dict.AddWord(target);
    dict.AddWord(opt1);
    dict.AddWord(opt2);
    dict.AddWord(opt3);

    vector<string>  searchResult = dict.GetWordOptions(target, 2);

    if (searchResult.size() != 1) {
        return false;
    }

    if (searchResult[0] != target) {
        return false;
    }

    return true;
}

bool FindAllCorrections()
{
    const string target("worda");
    const string opt1("wordb");
    const string opt2("word");
    const string opt3("wordab");


    bool containOpt2 = false;
    bool containOpt3 = false;

    SpellingDictionary  dict;

    dict.AddWord(opt1);
    dict.AddWord(opt2);
    dict.AddWord(opt3);

    vector<string>  searchResult = dict.GetWordOptions(target, 2);

    // replace symbol - two operations
    if (searchResult.size() != 2) {
        return false;
    }

    for (int i=0; i < 2; i++) {
        if (searchResult[i] == opt2) {
            containOpt2 = true;
        }

        if (searchResult[i] == opt3) {
            containOpt3 = true;
        }
    }

    return containOpt2 && containOpt3;
}
