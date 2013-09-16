#include "spelling_dictionary.h"

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <list>

#include "dictionary_option.h"

using namespace std;
using namespace spell_checker;

SpellingDictionary::SpellingDictionary() : m_count(0) {
    m_root = DictionaryTreeNode::CreateRootNode();
}

SpellingDictionary::~SpellingDictionary() {
}

bool
SpellingDictionary::AddWord(const string &word) {
	if (word.empty()) {
		return false;
	}

    DictionaryTreeNode	*current_node = m_root;
	int			index = 0;

	while (true) {
		if (index == word.length() - 1) {
			current_node = current_node->create_ending_child(word[index],word);
			++m_count;
			break;
		} else {
			current_node = current_node->create_child(word[index]);
			++index;
		}
	}

	return true;
}

vector<string>
SpellingDictionary::GetWordOptions(const string &word, unsigned int allowed_correction_count) {

	if (word.empty()) {
		return vector<string>();
	}

    list<DictionaryOption>	current_options;
    list<DictionaryOption>	next_options;
	int			current_corrections=0;

    current_options.push_front(DictionaryOption(m_root, word.length()));

	while (true) {
        for (list<DictionaryOption>::iterator i=current_options.begin(); i != current_options.end(); /*no increment*/) {
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
		return vector<string>();
	} else {
		vector<string> result;
		if (0 == current_corrections) {
			// return original word
			result.push_back(word);
		} else {
			result.reserve(current_options.size());

            for (list<DictionaryOption>::iterator result_option = current_options.begin(); result_option != current_options.end(); ++result_option) {
                string _str = (*result_option).GetString();

				// ignore dublicates
				if (find(result.begin(), result.end(), _str) == result.end()) {
                    result.push_back((*result_option).GetString());
				}
			}
		}

		return result;
	}
}
