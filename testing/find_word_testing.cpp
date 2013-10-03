#include <iostream>

#include "find_word_testing.h"

#include "testing.h"
#include <spelling_dictionary.h>
#include <latin_traits.h>

using namespace spell_checker;
using namespace std;

static bool FindWord();
static bool FindWordWhenCorrectionsArePossible();
static bool FindAllCorrections();

static bool InsertionsInBegining();
static bool InsertionsInTheMidle();
static bool InsertionsInTheEnd();

static bool RemovalsInTheBegining();
static bool RemovalsInTheMidle();
static bool RemovalsInTheEnd();

static TestCase	cases[] = {
    {"Find word", FindWord},
    {"Find word when corrections possible", FindWordWhenCorrectionsArePossible},
    {"Find all corrections", FindAllCorrections},
    {"Find with insertions in the begining", InsertionsInBegining},
    {"Find with insertions in the middle", InsertionsInTheMidle},
    {"Find with insertions in the end", InsertionsInTheEnd},
    {"Find with removals in the begining", RemovalsInTheBegining},
    {"Find with removals in the midle", RemovalsInTheMidle},
    {"Find with removals in the end", RemovalsInTheEnd}
};

bool
StartAddWordTesting() {
    return ExecuteTestCases(cases, sizeof(cases)/sizeof(*cases));
}


bool FindWord()
{
    SpellingDictionary<LatinTraist>  dict;

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

    SpellingDictionary<LatinTraist>  dict;

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

    SpellingDictionary<LatinTraist>  dict;

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


bool InsertionsInBegining() {
    const string target = "asd";
    const string word1 = "aasd";
    const string word2 = "basd";
    const string word3 = "abasd";
    const string word4 = "asddd";
    const string word5 = "csd";

    bool    containWord1 = false;
    bool    containWord2 = false;

    SpellingDictionary<LatinTraist>  dict;

    dict.AddWord(word1);
    dict.AddWord(word2);
    dict.AddWord(word3);
    dict.AddWord(word4);
    dict.AddWord(word5);

    vector<string>  searchResult = dict.GetWordOptions(target, 1);

    if (searchResult.size() != 2) {
        return false;
    }

    for (vector<string>::iterator i = searchResult.begin(); i != searchResult.end(); ++i) {
        if ((*i) == word1) {
            containWord1 = true;
        }

        if ((*i) == word2) {
            containWord2 = true;
        }
    }

    return containWord1 && containWord2;
}

bool InsertionsInTheMidle() {
    const string target = "asd";
    const string word1 = "aasd";
    const string word2 = "assd";
    const string word3 = "abasd";
    const string word4 = "asddd";
    const string word5 = "csd";

    bool    containWord1 = false;
    bool    containWord2 = false;

    SpellingDictionary<LatinTraist>  dict;

    dict.AddWord(word1);
    dict.AddWord(word2);
    dict.AddWord(word3);
    dict.AddWord(word4);
    dict.AddWord(word5);

    vector<string>  searchResult = dict.GetWordOptions(target, 1);

    if (searchResult.size() != 2) {
        return false;
    }

    for (vector<string>::iterator i = searchResult.begin(); i != searchResult.end(); ++i) {
        if ((*i) == word1) {
            containWord1 = true;
        }

        if ((*i) == word2) {
            containWord2 = true;
        }
    }

    return containWord1 && containWord2;
}

bool InsertionsInTheEnd() {
    const string target = "asd";
    const string word1 = "asdd";
    const string word2 = "asda";
    const string word3 = "abasd";
    const string word4 = "asddd";
    const string word5 = "csd";

    bool    containWord1 = false;
    bool    containWord2 = false;

    SpellingDictionary<LatinTraist>  dict;

    dict.AddWord(word1);
    dict.AddWord(word2);
    dict.AddWord(word3);
    dict.AddWord(word4);
    dict.AddWord(word5);

    vector<string>  searchResult = dict.GetWordOptions(target, 1);

    if (searchResult.size() != 2) {
        return false;
    }

    for (vector<string>::iterator i = searchResult.begin(); i != searchResult.end(); ++i) {
        if ((*i) == word1) {
            containWord1 = true;
        }

        if ((*i) == word2) {
            containWord2 = true;
        }
    }

    return containWord1 && containWord2;
}

bool RemovalsInTheBegining()
{
    const string target = "aasd";
    const string word1 = "asd";
    const string word2 = "asda";
    const string word3 = "absad";
    const string word4 = "asddd";
    const string word5 = "csd";

    bool    containWord1 = false;

    SpellingDictionary<LatinTraist>  dict;

    dict.AddWord(word1);
    dict.AddWord(word2);
    dict.AddWord(word3);
    dict.AddWord(word4);
    dict.AddWord(word5);

    vector<string>  searchResult = dict.GetWordOptions(target, 1);

    if (searchResult.size() != 1) {
        return false;
    }

    containWord1 = searchResult[0] == word1;

    return containWord1;
}

bool RemovalsInTheMidle() {
    const string target = "absd";
    const string word1 = "asd";
    const string word2 = "asda";
    const string word3 = "abasd";
    const string word4 = "asddd";
    const string word5 = "csd";

    bool    containWord1 = false;
    bool    containWord3 = false;

    SpellingDictionary<LatinTraist>  dict;

    dict.AddWord(word1);
    dict.AddWord(word2);
    dict.AddWord(word3);
    dict.AddWord(word4);
    dict.AddWord(word5);

    vector<string>  searchResult = dict.GetWordOptions(target, 1);

    if (searchResult.size() != 2) {
        return false;
    }

    for (vector<string>::iterator i = searchResult.begin(); i != searchResult.end(); ++i) {
        if ((*i) == word1) {
            containWord1 = true;
        }

        if ((*i) == word3) {
            containWord3 = true;
        }
    }

    return containWord1 && containWord3;
}

bool RemovalsInTheEnd() {
    const string target = "asdb";
    const string word1 = "asd";
    const string word2 = "asda";
    const string word3 = "absad";
    const string word4 = "asddd";
    const string word5 = "csd";

    bool    containWord1 = false;

    SpellingDictionary<LatinTraist>  dict;

    dict.AddWord(word1);
    dict.AddWord(word2);
    dict.AddWord(word3);
    dict.AddWord(word4);
    dict.AddWord(word5);

    vector<string>  searchResult = dict.GetWordOptions(target, 1);

    if (searchResult.size() != 1) {
        return false;
    }

    containWord1 = searchResult[0] == word1;

    return containWord1;
}
