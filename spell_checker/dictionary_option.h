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

    void		InsertCorrections(std::list<DictionaryOption> &c, const std::string &word) const;

    bool	ReachEnd(const std::string &word) const;

    bool	WordComplete() const;

    bool	MoveToNextSymbol(const std::string &word);

	std::string		GetString() const;

private:
    void		skip_symbol();

    void		insert_node(DictionaryTreeNode	*new_node);

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
