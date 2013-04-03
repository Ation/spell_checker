#include "dictionary_tree_node.h"

using namespace spell_checker;
using namespace std;

DictionaryTreeNode::my_type*
DictionaryTreeNode::CreateRootNode() {
	return new DictionaryTreeNode(_not_a_symbol);
}

DictionaryTreeNode::DictionaryTreeNode(char node_symbol) : 
  m_node_symbol(node_symbol), m_word(NULL) {
	erase_child_pointers();
}

DictionaryTreeNode::DictionaryTreeNode(char node_symbol, string &word) : 
  m_node_symbol(node_symbol) {

	m_word = new string(word);
	erase_child_pointers();
}

DictionaryTreeNode::~DictionaryTreeNode() {
	for (int i=0; i<_alpha_count; ++i) {
		if (0 != m_childs[i]) {
			delete m_childs[i];
		}
	}

	if (NULL != m_word) {
		delete m_word;
	}
}

void
DictionaryTreeNode::erase_child_pointers() {
	m_childs.assign(_alpha_count, 0);
}

DictionaryTreeNode*
DictionaryTreeNode::get_child(char symbol) {
	DictionaryTreeNode* result = NULL;
	int index = get_raw_index(symbol);

	if (_invalid_raw_index != index) {
		result = get_child_by_index(index);
	}

	return result;
}

DictionaryTreeNode*
DictionaryTreeNode::create_child(char symbol) {
	int		index = get_raw_index(symbol);

	if (_invalid_raw_index != index) {
		DictionaryTreeNode*		child = get_child_by_index(index);

		if (NULL == child) {
			child = new DictionaryTreeNode(symbol);
			set_child(child, index);
		}

		return child;
	}

	return NULL;
}

DictionaryTreeNode*
DictionaryTreeNode::create_ending_child(char symbol, string &word) {
	int		index = get_raw_index(symbol);

	if (_invalid_raw_index != index) {
		DictionaryTreeNode*		child = get_child_by_index(index);

		if (NULL == child) {
			child = new DictionaryTreeNode(symbol, word);
			set_child(child, index);
		} else {
			child->m_word = new string(word);
		}

		return child;
	}

	return NULL;
}

bool
DictionaryTreeNode::could_be_last() const {
	return NULL != m_word;
}

char
DictionaryTreeNode::get_node_symbol() const {
	return m_node_symbol;
}

int
DictionaryTreeNode::get_raw_index(char symbol) const {
	if ((symbol >= 'a') && (symbol <= 'z')) {
		return symbol - 'a';
	}

	if ((symbol >= 'A') && (symbol <= 'Z')) {
		return symbol - 'A';
	}

	return _invalid_raw_index;
}

DictionaryTreeNode*
DictionaryTreeNode::get_child_by_index(int raw_index) {
	return m_childs[raw_index];
}

void
DictionaryTreeNode::set_child(DictionaryTreeNode *child, int raw_index) {
	m_childs[raw_index] = child;
}

string
DictionaryTreeNode::get_node_string() const {
	if (NULL != m_word) {
		return string(*m_word);
	} else {
		return string();
	}
}