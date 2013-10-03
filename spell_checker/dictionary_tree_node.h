#ifndef __DICTIONARY_TREE_NODE_H__
#define __DICTIONARY_TREE_NODE_H__

/*
	file: 
		dictionary_tree_node.h
	Description:
		Contain class that represent node in string tree;
*/

#include <vector>
#include <map>

namespace spell_checker {

template<typename __symbol_traits>
class DictionaryTreeNode {
private:
    typedef DictionaryTreeNode<__symbol_traits> my_type;

    typedef typename __symbol_traits::string_type   string_type;
    typedef typename __symbol_traits::char_type     char_type;

    typedef std::map<char_type, my_type*> childs_map;

public:
    typedef typename std::vector<my_type*>  childs_collection;

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
        for (typename childs_map::iterator i = m_childs.begin(); i != m_childs.end(); ++i) {
            delete (*i).second;
        }

        if (NULL != m_word) {
            delete m_word;
        }
    }

    my_type*	get_child(char_type symbol) const {
        typename childs_map::const_iterator result = m_childs.find(symbol);
        return (result == m_childs.end() ? NULL : (*result).second);
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
        childs_collection result;

        result.reserve(m_childs.size());

        for (typename childs_map::const_iterator i=m_childs.begin(); i != m_childs.end(); ++i) {
            result.push_back( (*i).second);
        }

        return result;
    }

private:
    explicit DictionaryTreeNode(char_type node_symbol) : m_node_symbol(node_symbol), m_word(NULL) {
    }

	// disabled
    DictionaryTreeNode(const my_type&);
	// disabled
    DictionaryTreeNode& operator = (const my_type&);

	// members
    char_type			m_node_symbol;
    string_type			*m_word;

    childs_map          m_childs;

    void        set_child(my_type *child) {
        m_childs[child->m_node_symbol] = child;
    }

    my_type*	create_child(char_type symbol) {
        my_type     *child = get_child(symbol);

        if (NULL == child) {
            child = new my_type(symbol);
            set_child(child);
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
