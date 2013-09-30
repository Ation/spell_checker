#include "spell_checker_testing.h"

#include "dictionary_tree_node_testing.h"
#include "find_word_testing.h"

#include <iostream>

using namespace std;

void
StartTest() {
    bool    result = true;
    result = result && StartDictionaryTreeNodeTesting();
    result = result && StartAddWordTesting();

    cout << "Summary: " << (result ? "all pass" : "failed") << endl;
}
