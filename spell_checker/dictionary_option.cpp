#include "dictionary_option.h"

using namespace std;
using namespace spell_checker;

DictionaryOption::DictionaryOption(DictionaryTreeNode *root, int max_string_length) : m_corrections(0), word_index(0), node(root) {
	m_last_operation = NotProceededOperation;
}


DictionaryOption::DictionaryOption(const DictionaryOption &src) : 
  m_corrections(src.m_corrections), word_index(src.word_index), node(src.node), m_last_operation(src.m_last_operation) {
}

bool
DictionaryOption::corrections_allowed(int	allowed_correction_count) const {
	return m_corrections < allowed_correction_count;
}

string
DictionaryOption::GetString() const {
	return node->get_node_string();
}

bool
DictionaryOption::ReachEnd(std::string &word) const {
    return word_index == word.length();
}

bool
DictionaryOption::WordComplete() const {
    return node->could_be_last();
}

bool
DictionaryOption::MoveToNextSymbol(std::string &word) {
    node = node->get_child(word[word_index]);

    if (0 != node) {
        // next symbol exists
        ++word_index;
        m_last_operation = SymbolFindOperation;
        return true;
    }

    return false;
}

void
DictionaryOption::InsertCorrections(std::list<DictionaryOption> &c, std::string &word) const {
    // add possible insertions
    std::vector<DictionaryTreeNode*> childs = node->getChilds();
    for (std::vector<DictionaryTreeNode*>::iterator i_node = childs.begin(); i_node != childs.end(); ++i_node) {
        if (0 == (*i_node)) {
            continue;
        }

        if ((*i_node)->get_node_symbol() == node->get_node_symbol()) {
            continue;
        }

        DictionaryOption op(*this);

        op.insert_node(*i_node);

        c.push_back(op);
    }

    // add removal if make sence
    if (word_index < word.length()) {
        DictionaryOption op(*this);

        op.skip_symbol();

        c.push_back(op);
    }
}

void
DictionaryOption::skip_symbol() {
    m_last_operation = RemoveOperation;
    ++m_corrections;
    ++word_index;
}

void
DictionaryOption::insert_node(DictionaryTreeNode	*new_node) {
    m_last_operation = InsertOperation;
    ++m_corrections;
    node = new_node;
}
