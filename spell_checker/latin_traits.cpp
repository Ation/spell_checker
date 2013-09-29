#include "latin_traits.h"

int LatinTraist::symbols_count() {
    return 26;
}

LatinTraist::char_type LatinTraist::not_a_symbol() {
    return 0;
}

bool LatinTraist::isValid(const LatinTraist::string_type &word) {
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

bool LatinTraist::symbol_in_range(LatinTraist::char_type symbol) {
    return (((symbol >= 'a') && (symbol <= 'z')) ||
            ((symbol >= 'A') && (symbol <= 'Z')) );
}

int LatinTraist::get_raw_index(LatinTraist::char_type symbol) {
    if ((symbol >= 'a') && (symbol <= 'z')) {
        return symbol - 'a';
    }

    if ((symbol >= 'A') && (symbol <= 'Z')) {
        return symbol - 'A';
    }

    return -1;
}
