#ifndef __DICTIONARY_OPTION_H__
#define __DICTIONARY_OPTION_H__

#include <string>
#include <memory>
#include <list>

#include "spelling_dictionary.h"

namespace spell_checker {

class DictionaryOption {
public:
    DictionaryOption(DictionaryTreeNode *root, int max_string_length);

	DictionaryOption(const DictionaryOption &src);

	~DictionaryOption() {}

	bool		corrections_allowed(int	allowed_correction_count) const;

    int			get_corrections_count() const;

    void		InsertCorrections(std::list<DictionaryOption> &c, std::string &word) {
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

	bool	ReachEnd(std::string &word) {
		return word_index == word.length();
	}

	bool	WordComplete() {
		return node->could_be_last();
	}

	bool	MoveToNextSymbol(std::string &word) {
		node = node->get_child(word[word_index]);

		if (0 != node) {
			// next symbol exists
			++word_index;
			m_last_operation = SymbolFindOperation;
			return true;
		}

		return false;
	}

	std::string		GetString() const;

private:
	void		append_symbol(char symbol);

	void		increase_corrections();

	void		skip_symbol() {
		m_last_operation = RemoveOperation;
		++m_corrections;
		++word_index;
	}

    void		insert_node(DictionaryTreeNode	*new_node) {
		m_last_operation = InsertOperation;
		++m_corrections;
		node = new_node;
	}

	int								m_corrections;
	size_t							word_index;

    DictionaryTreeNode	*node;

	enum _last_operation {
		InsertOperation,
		RemoveOperation,
		SymbolFindOperation,
		NotProceededOperation
	} m_last_operation;
};

}

#endif
