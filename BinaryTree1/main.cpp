#include <iostream>
#include "binarytree.h"

// TODO Add tests
int main() {
    Dictionary<int,int> tree;

    tree.add(16,1);
    tree.add(32,2);
    tree.add(48,3);
    tree.add(8,4);
    tree.remove(48);
    std::cout << tree.pop(8) << std::endl;
    std::cout << tree.find_by_key(16) << std::endl;
    return 0;
}
