#ifndef __DICTIONARY_TREE_NODE_H__
#define __DICTIONARY_TREE_NODE_H__

/*
	file: 
		dictionary_tree_node.h
	Description:
		Contain class that represent node in string tree;
*/

namespace spell_checker {

class DictionaryTreeNode {
public:
	typedef DictionaryTreeNode my_type;

	DictionaryTreeNode();
	virtual ~DictionaryTreeNode();

private:
	// disabled
	DictionaryTreeNode(const DictionaryTreeNode&);
	// disabled
	DictionaryTreeNode& operator = (const DictionaryTreeNode&);
};

};

#endif //__DICTIONARY_TREE_NODE_H__