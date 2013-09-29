#ifndef __DICTIONARY_TREE_NODE_H__
#define __DICTIONARY_TREE_NODE_H__

/*
	file: 
		dictionary_tree_node.h
	Description:
		Contain class that represent node in string tree;
*/

#include <vector>

namespace spell_checker {

template<typename __symbol_traits>
class DictionaryTreeNode {
private:
    typedef DictionaryTreeNode<__symbol_traits> my_type;

    typedef typename __symbol_traits::string_type   string_type;
    typedef typename __symbol_traits::char_type     char_type;

public:
    typedef typename std::vector<my_type*>          childs_collection;

    static my_type*	CreateRootNode() {
        return new my_type(__symbol_traits::not_a_symbol());
    }

    bool AddWordToNode(const string_type &word) {
        if (!__symbol_traits::isValid(word)) {
            return false;
        }

        my_type     *current_node = this;
        int         index = 0;

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

    virtual ~DictionaryTreeNode() {
        for (int i=0; i < __symbol_traits::symbols_count(); ++i) {
            if (0 != m_childs[i]) {
                delete m_childs[i];
            }
        }

        if (NULL != m_word) {
            delete m_word;
        }
    }

    my_type*	get_child(char_type symbol) {
        int index = __symbol_traits::get_raw_index(symbol);

        return get_child_by_index(index);
    }

    bool		could_be_last() const {
        return NULL != m_word;
    }

    char_type		get_node_symbol() const {
        return m_node_symbol;
    }

    string_type     get_node_string() const {
        if (NULL != m_word) {
            return string_type(*m_word);
        } else {
            return string_type();
        }
    }

    childs_collection   getChilds() const {
        return childs_collection(m_childs);
    }

private:
    explicit DictionaryTreeNode(char_type node_symbol) : m_node_symbol(node_symbol), m_word(NULL) {
        erase_child_pointers();
    }

	// disabled
    DictionaryTreeNode(const my_type&);
	// disabled
    DictionaryTreeNode& operator = (const my_type&);

	// members
    char_type			m_node_symbol;
    string_type			*m_word;

    std::vector< my_type* >		m_childs;

    void        erase_child_pointers() {
        m_childs.assign(__symbol_traits::symbols_count(), NULL);
    }

    my_type*    get_child_by_index(int raw_index) {
        return m_childs[raw_index];
    }

    void        set_child(my_type *child, int raw_index) {
        m_childs[raw_index] = child;
    }

    my_type*	create_child(char_type symbol) {
        int     index = __symbol_traits::get_raw_index(symbol);
        DictionaryTreeNode*     child = get_child_by_index(index);

        if (NULL == child) {
            child = new DictionaryTreeNode(symbol);
            set_child(child, index);
        }

        return child;
    }

    my_type*	create_ending_child(char_type symbol,const string_type &word) {
        my_type* child = create_child(symbol);
        if (NULL != child) {
            if (child->m_word == NULL) {
                child->m_word = new string_type(word);
            }
        }

        return child;
    }
};

}

#endif //__DICTIONARY_TREE_NODE_H__
