#include <iostream>

#include "testing.h"
#include "dictionary_tree_node_testing.h"
#include <latin_traits.h>
#include <dictionary_tree_node.h>

using namespace spell_checker;
using namespace std;

static bool CreateRootNodeTest();
static bool CreateChildTest();

typedef DictionaryTreeNode<LatinTraits> node_type;

static TestCase	cases[] = {
	{"Create Root node", CreateRootNodeTest},
    //{"Create child test", CreateChildTest}
};

bool StartDictionaryTreeNodeTesting() {
    return ExecuteTestCases(cases, sizeof(cases)/sizeof(*cases));
}

bool
CreateRootNodeTest() {
    node_type *root_node = node_type::CreateRootNode();

	bool result = false;

	if (NULL != root_node) {
		do {
			if (root_node->could_be_last()) {
				result = false;
				break;
			}

            if (LatinTraits::not_a_symbol() != root_node->get_node_symbol()) {
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

#if 0
bool
CreateChildTest() {
	bool	result;

    node_type *root_node = node_type::CreateRootNode();
    node_type *child = NULL;
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
#endif
