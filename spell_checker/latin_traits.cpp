#include "latin_traits.h"

int LatinTraits::symbols_count() {
    return 26;
}

LatinTraits::char_type LatinTraits::not_a_symbol() {
    return 0;
}

bool LatinTraits::isValid(const LatinTraits::string_type &word) {
    if (word.empty()) {
        return false;
    }

    bool    result = true;

    for (int i=0; i < word.length(); ++i) {
        if (!symbol_in_range(word[i])) {
            result = false;
            break;
        }
    }

    return result;
}

bool LatinTraits::symbol_in_range(LatinTraits::char_type symbol) {
    return (((symbol >= 'a') && (symbol <= 'z')) ||
            ((symbol >= 'A') && (symbol <= 'Z')) );
}

int LatinTraits::get_raw_index(LatinTraits::char_type symbol) {
    if ((symbol >= 'a') && (symbol <= 'z')) {
        return symbol - 'a';
    }

    if ((symbol >= 'A') && (symbol <= 'Z')) {
        return symbol - 'A';
    }

    return -1;
}
