#ifndef __DICTIONARY_TREE_NODE_H__
#define __DICTIONARY_TREE_NODE_H__

/*
	file: 
		dictionary_tree_node.h
	Description:
		Contain class that represent node in string tree;
*/

#include <string>
#include <vector>

namespace spell_checker {

class DictionaryTreeNode {
public:
    static DictionaryTreeNode*	CreateRootNode();

	virtual ~DictionaryTreeNode();

    DictionaryTreeNode*	get_child(char symbol);

    DictionaryTreeNode*	create_child(char symbol);

    DictionaryTreeNode*	create_ending_child(char symbol, std::string &word);

	bool		could_be_last() const;

	char		get_node_symbol() const;

	std::string		get_node_string() const;

	static const char	_not_a_symbol = 0;

    std::vector<DictionaryTreeNode*> getChilds() const;

private:
	DictionaryTreeNode(char node_symbol, std::string &word);

	DictionaryTreeNode(char node_symbol);

	// disabled
	DictionaryTreeNode(const DictionaryTreeNode&);
	// disabled
	DictionaryTreeNode& operator = (const DictionaryTreeNode&);

	// members
	char				m_node_symbol;
	std::string			*m_word;

    std::vector< DictionaryTreeNode * >		m_childs;

	void			erase_child_pointers();

	int				get_raw_index(char symbol) const;

    DictionaryTreeNode*		get_child_by_index(int raw_index);
    void                    set_child(DictionaryTreeNode *child, int raw_index);

	// internal constants
	static const int	_alpha_count = 26;
	static const int	_invalid_raw_index = -1;
};

};

#endif //__DICTIONARY_TREE_NODE_H__
