#ifndef __SPELLING_DICTIONARY_H__
#define __SPELLING_DICTIONARY_H__

#include <string>
#include <vector>

#include "dictionary_tree_node.h"

namespace spell_checker {

class SpellingDictionary {
public:
	SpellingDictionary();
	~SpellingDictionary();

	// Method:
	//	AddWord - add word to dictionary.
	// Input:
	//	word - word to add
	// Return:
	//	true if word was added
	//	false if word could not be added to dictionary
	bool AddWord(std::string &word);

	// Method:
	//	GetWordOptions - get possible words from dictionary
	// Input
	//	word - word to search
	//	allowed_correction_count - allowed insertions or removals in original word
	// Return
	//	list of words from dictionary with equal (minimum) amount of corrections
	//	if list is empty, than word and all possible modifications not exist in dictionary
	// Remarks:
	//	if exact match found word is returned in original form
	std::vector<std::string> GetWordOptions(std::string &word, unsigned int allowed_correction_count);

	typedef DictionaryTreeNode node_type;
	bool	AddWord(std::string &word);
private:
	// disabled
	SpellingDictionary(const SpellingDictionary&);
	// disabled
	SpellingDictionary& operator = (const SpellingDictionary&);

	node_type	*m_root;

	int			m_count;
};

}

#endif // __SPELLING_DICTIONARY_H__
