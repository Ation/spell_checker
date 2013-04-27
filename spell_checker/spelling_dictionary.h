#ifndef __SPELLING_DICTIONARY_H__
#define __SPELLING_DICTIONARY_H__

#include <string>
#include <vector>
#include <memory>

namespace spell_checker {

class SpellingDictionary {
public:
	SpellingDictionary();
	~SpellingDictionary();

	bool	add_word(std::string &word);
	
	std::vector<std::shared_ptr<std::string> > get_words(std::string &word) const;
private:
	// disabled
	SpellingDictionary(const SpellingDictionary&);

	// disabled
	SpellingDictionary& operator = (const SpellingDictionary&);
};

}

#endif