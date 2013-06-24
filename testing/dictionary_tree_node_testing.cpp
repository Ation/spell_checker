#include <iostream>

#include "testing.h"
#include "dictionary_tree_node_testing.h"
#include <dictionary_tree_node.h>

using namespace spell_checker;
using namespace std;

static bool CreateRootNodeTest();
static bool CreateChildTest();

TestCase	cases[] = {
	{"Create Root node", CreateRootNodeTest},
	{"Create child test", CreateChildTest}
};

void
StartDictionaryTreeNodeTesting() {
	bool result;

	for (int i=0; i<sizeof(cases)/sizeof(*cases); i++) {

		cout << "################################" << endl;

        cout << "Starting: " << cases[i].test_name << endl;
		try {
            result = cases[i].test_function();
			cout << "Result: " << (result ? "PASS" : "FAIL") << endl;
		} catch (...) {
			cout << "Ended with exception" << endl;
		}

		cout << "################################" << endl << endl;
	}
}

bool
CreateRootNodeTest() {
	DictionaryTreeNode *root_node = DictionaryTreeNode::CreateRootNode();

	bool result = false;

	if (NULL != root_node) {
		do {
			if (root_node->could_be_last()) {
				result = false;
				break;
			}

			if (DictionaryTreeNode::_not_a_symbol != root_node->get_node_symbol()) {
				result = false;
				break;
			}

			if (root_node->get_node_string().length() != 0) {
				result = false;
				break;
			}

			result = true;
		} while (false);

		delete root_node;
	} else {
		result = false;
	}

	return result;
}

bool
CreateChildTest() {
	bool	result;

	DictionaryTreeNode *root_node = DictionaryTreeNode::CreateRootNode();
	DictionaryTreeNode *child = NULL;
	char symbol = 'a';

	if (NULL != root_node) {
		do {
			result = false;

			child = root_node->get_child(symbol);
			if (NULL != child) {
				break;
			}

			child = root_node->create_child(symbol);

			if (NULL == child) {
				break;
			}

			child = root_node->get_child(symbol);
			if (NULL == child) {
				break;
			}

			if (child->get_node_symbol() != symbol) {
				break;
			}

			if (child->get_node_string().length() != 0) {
				break;
			}

			if (child->could_be_last()) {
				break;
			}

			result = true;
		} while (false);

		delete root_node;
	} else {
		result = false;
	}

	return result;
}
