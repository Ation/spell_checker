#ifndef __SPELLING_DICTIONARY_H__
#define __SPELLING_DICTIONARY_H__

#include <vector>

#include "dictionary_option.h"

namespace spell_checker {

template<typename __symbol_traits>
class SpellingDictionary {
public:
    SpellingDictionary() {
        m_root = DictionaryTreeNode::CreateRootNode();
    }

    ~SpellingDictionary() {
        delete m_root;
    }

private:
    typedef typename __symbol_traits::string_type string_type;
    typedef typename spell_checker::DictionaryOption option_type;

public:
	// Method:
	//	AddWord - add word to dictionary.
	// Input:
	//	word - word to add
	// Return:
	//	true if word was added
	//	false if word could not be added to dictionary
    bool AddWord(const string_type &word) {
        if (!DictionaryTreeNode::checkWord(word)) {
            return false;
        }

        DictionaryTreeNode	*current_node = m_root;
        int			index = 0;

        while (true) {
            if (index == word.length() - 1) {
                current_node = current_node->create_ending_child(word[index],word);
                break;
            } else {
                current_node = current_node->create_child(word[index]);
                ++index;
            }
        }

        return true;
    }

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
    std::vector<string_type> GetWordOptions(const string_type &word, unsigned int allowed_correction_count) {
        if (word.empty()) {
            return std::vector<string_type>();
        }

        std::list<option_type> current_options;
        std::list<spell_checker::DictionaryOption> next_options;
        int                         current_corrections=0;

        current_options.push_front(DictionaryOption(m_root, word.length()));

        while (true) {
            for (std::list<spell_checker::DictionaryOption>::iterator i=current_options.begin(); i != current_options.end(); /*no increment*/) {
                while (true) {
                    // add ppossible corrections for current word path
                    if ((*i).corrections_allowed(allowed_correction_count)) {
                        (*i).InsertCorrections(next_options, word);
                    }

                    if ((*i).ReachEnd(word)) {
                        if ((*i).WordComplete()){
                            // leave this path in options list, will be returned in result
                            ++i;
                        } else {
                            // word not found
                            i = current_options.erase(i);
                        }
                        break;
                    }

                    if (!(*i).MoveToNextSymbol(word)) {
                        i = current_options.erase(i);
                        break;
                    }
                }
            }

            if ((!current_options.empty()) || (next_options.empty())) {
                break;
            }

            current_options.swap(next_options);
            ++current_corrections;
        }

        if (current_options.empty()) {
            return std::vector<string_type>();
        } else {
            std::vector<string_type> result;
            if (0 == current_corrections) {
                // return original word
                result.push_back(word);
            } else {
                result.reserve(current_options.size());

                for (std::list<spell_checker::DictionaryOption>::iterator result_option = current_options.begin(); result_option != current_options.end(); ++result_option) {
                    string_type _str = (*result_option).GetString();

                    // ignore dublicates
                    if (find(result.begin(), result.end(), _str) == result.end()) {
                        result.push_back((*result_option).GetString());
                    }
                }
            }

            return result;
        }
    }

private:
	// disabled
    SpellingDictionary(const SpellingDictionary<_Opt>&);
	// disabled
    SpellingDictionary& operator = (const SpellingDictionary<_Opt>&);

    DictionaryTreeNode	*m_root;
};

}

#endif // __SPELLING_DICTIONARY_H__
