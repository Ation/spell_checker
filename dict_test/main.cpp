#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include <dictionary_tree_node.h>
#include <latin_traits.h>

using namespace spell_checker;

// print memory usage
// print how many memory is useless (null childs)

typedef LatinTraist symbols_info;
typedef DictionaryTreeNode<symbols_info> node_type;

typedef struct __level_statistics {
    __level_statistics() : used_childs(0), unused_childs(0), word_count(0), strings_length(0) {}

    int     used_childs;
    int     unused_childs;
    int     word_count;
    int     strings_length;
}level_stat;

void analyze_node(node_type *node, int node_level, vector<level_stat> &info);
void print_levels(vector<level_stat> &info);

int main(int argc, char **argv) {
    if (argc != 2) {
        cout << "Specify dictionary file name";
        return 1;
    }

    ifstream f(argv[1]);
    const int buffer_size = 50;
    char buffer[buffer_size];
    int  word_count = 0;
    int max_length = 0;

    string  str;
    str.reserve(buffer_size);

    if (f.is_open()) {
        node_type *root = node_type::CreateRootNode();

        cout << "Start reading file" << endl;

        while (f) {
            f.getline(buffer, buffer_size);
            str = buffer;
            if (root->AddWordToNode(str)) {
                word_count++;
                if (str.length() > max_length) {
                    max_length = str.length();
                }
            } else {
                if (!str.empty()) {
                    cout << "Failed to add " << str << endl;
                }
            }
        }

        cout << "Read completed. " << word_count << " words added." << endl;
        cout << "Max length " << max_length << endl;
        f.close();

        vector<level_stat> levels_info;
        levels_info.resize(max_length + 1);

        analyze_node(root, 0, levels_info);

        print_levels(levels_info);

        delete root;
    } else {
        cout << "Failed to open " << argv[1] << endl;
    }

    return 0;
}

void analyze_node(node_type *node, int node_level, vector<level_stat> &info) {
    node_type::childs_collection childs = node->getChilds();

    info[node_level].used_childs++;
    if (node->could_be_last()) {
        info[node_level].word_count++;
        info[node_level].strings_length += node->get_node_string().length();
    }

    for (node_type::childs_collection::iterator _i = childs.begin(); _i != childs.end(); ++_i) {
        if ((*_i) == NULL) {
            info[node_level].unused_childs++;
        } else {
            analyze_node((*_i), node_level+1, info);
        }
    }
}

void print_levels(vector<level_stat> &info) {
    level_stat total;
    const size_t node_size = sizeof(node_type) + sizeof(node_type*) * symbols_info::symbols_count();
    const size_t pointer_size = sizeof(node_type*);

    size_t  memory_usefull;
    size_t  memory_useless;
    size_t  memory_total;

    cout << "Level | Unused nodes | used nodes | words  | rate" << endl;
    for (int i=0; i < info.size(); i++) {
        memory_usefull = info[i].used_childs * node_size;
        memory_useless = info[i].unused_childs * pointer_size;
        memory_total = memory_usefull + memory_useless;

        cout << i << "  | " << info[i].unused_childs << "  |  " << info[i].used_childs << "  |  " << info[i].word_count
          << " # "
          << (float)(memory_usefull) / (memory_total) << endl;
        total.unused_childs += info[i].unused_childs;
        total.used_childs += info[i].used_childs;
        total.word_count += info[i].word_count;
        total.strings_length += info[i].strings_length;

    }

    memory_usefull = total.used_childs * node_size;
    memory_useless = total.unused_childs * pointer_size;
    memory_total = memory_usefull + memory_useless;

    cout << "Total: " << total.unused_childs << " | " << total.used_childs << " | " << total.word_count << endl;
    cout << "Memory used for nodes: " << memory_usefull << endl;
    cout << "Useles memory: " << memory_useless << endl;
    cout << "Memory usage rate : " << (float)(memory_usefull) / (memory_total) << endl;
    cout << "Total strings length " << total.strings_length << endl;
}
