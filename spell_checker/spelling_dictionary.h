#ifndef __SPELLING_DICTIONARY_H__
#define __SPELLING_DICTIONARY_H__

#include <string>

namespace spell_checker {

class spelling_dictionary {
public:
	spelling_dictionary();
	~spelling_dictionary();

	bool	AddWord(std::string &word);

private:
	// disabled
	spelling_dictionary(const spelling_dictionary&);

	// disabled
	spelling_dictionary& operator = (const spelling_dictionary&);
};

}

#endif