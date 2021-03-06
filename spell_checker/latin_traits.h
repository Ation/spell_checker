#ifndef __LATIN_TRAITS_H__
#define __LATIN_TRAITS_H__

#include <string>

class LatinTraits {
public:
    using char_type = char;
    using string_type = std::string;

    static int symbols_count();

    static int get_raw_index(char_type symbol);

    static char_type not_a_symbol();

    static bool isValid(const string_type &word);

    static bool symbol_in_range(char_type symbol);
};

#endif
