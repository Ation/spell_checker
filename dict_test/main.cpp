#include <fstream>
#include <iostream>
#include <string>

using namespace std;

#include <spelling_dictionary.h>
#include <latin_traits.h>

using namespace spell_checker;

// print memory usage
// print how many memory is useless (null childs)

int main(int argc, char **argv) {
    if (argc != 2) {
        cout << "Specify dictionary file name";
        return 1;
    }

    ifstream f(argv[1]);
    const int buffer_size = 50;
    char buffer[buffer_size];
    int  word_count = 0;

    string  str;
    str.reserve(buffer_size);

    if (f.is_open()) {
        SpellingDictionary<LatinTraist> dictionary;

        cout << "Start reading file" << endl;

        while (f) {
            f.getline(buffer, buffer_size);
            str = buffer;
            if (dictionary.AddWord(str)) {
                word_count++;
            } else {
                cout << "Failed to add " << str << endl;
            }
        }

        cout << "Read completed" << endl;
        f.close();


    } else {
        cout << "Failed to open " << argv[1] << endl;
    }

    return 0;
}
