#ifndef __DICTIONARY_OPTION_H__
#define __DICTIONARY_OPTION_H__

#include <memory>
#include <list>

#include "dictionary_tree_node.h"

namespace spell_checker {

template<typename __symbol_traits>
class DictionaryOption {
public:
    typedef DictionaryTreeNode<__symbol_traits> node_type;
    typedef DictionaryOption<__symbol_traits> my_type;

    typedef typename __symbol_traits::string_type   string_type;

    explicit DictionaryOption(node_type *root) : m_corrections(0), m_word_index(0),
      m_node(root), m_last_operation(NotProceededOperation)
    {}

    DictionaryOption(const my_type &src) :
      m_corrections(src.m_corrections), m_word_index(src.m_word_index), m_node(src.m_node),
      m_last_operation(src.m_last_operation)
    {}

    ~DictionaryOption() {}

    bool    corrections_allowed(int allowed_correction_count) const {
        return m_corrections < allowed_correction_count;
    }

    void    InsertCorrections(std::list<my_type> &c, const string_type &word) const {
        // add possible insertions
        typename node_type::childs_collection childs = m_node->getChilds();
        for (typename node_type::childs_collection::iterator i_node = childs.begin(); i_node != childs.end(); ++i_node) {
            if (0 == (*i_node)) {
                continue;
            }

            if ((*i_node)->get_node_symbol() == m_node->get_node_symbol()) {
                continue;
            }

            my_type op(*this);

            op.insert_node(*i_node);

            c.push_back(op);
        }

        // add removal if make sence
        if (m_word_index < word.length()) {
            my_type op(*this);

            op.skip_symbol();

            c.push_back(op);
        }
    }

    bool    ReachEnd(const string_type &word) const {
        return m_word_index == word.length();
    }

    bool    WordComplete() const {
        return m_node->could_be_last();
    }

    bool	MoveToNextSymbol(const string_type &word) {
        node_type *next_symbol_node = m_node->get_child(word[m_word_index]);

        if (NULL != next_symbol_node) {
            m_node = next_symbol_node;
            // next symbol exists
            ++m_word_index;
            m_last_operation = SymbolFindOperation;
            return true;
        }

        return false;
    }

    string_type		GetString() const {
        return m_node->get_node_string();
    }

private:
    void    skip_symbol() {
        m_last_operation = RemoveOperation;
        ++m_corrections;
        ++m_word_index;
    }

    void    insert_node(node_type	*new_node) {
        m_last_operation = InsertOperation;
        ++m_corrections;
        m_node = new_node;
    }

	int								m_corrections;
    size_t							m_word_index;

    node_type	*m_node;

	enum _last_operation {
		InsertOperation,
		RemoveOperation,
		SymbolFindOperation,
		NotProceededOperation
	} m_last_operation;
};

}

#endif
