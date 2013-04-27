#include "dictionary_option.h"

using namespace std;
using namespace spell_checker;

DictionaryOption::DictionaryOption(SpellingDictionary::node_type *root, int max_string_length) : m_corrections(0), word_index(0), node(root) {
	m_last_operation = NotProceededOperation;
}


DictionaryOption::DictionaryOption(const DictionaryOption &src) : 
  m_corrections(src.m_corrections), word_index(src.word_index), node(src.node), m_last_operation(src.m_last_operation) {
}

void
DictionaryOption::append_symbol(char symbol) {
}


void
DictionaryOption::increase_corrections() {
	++m_corrections;
}

bool
DictionaryOption::corrections_allowed(int	allowed_correction_count) const {
	return m_corrections < allowed_correction_count;
}

string
DictionaryOption::GetString() const {
	return node->get_node_string();
}