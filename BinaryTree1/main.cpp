//
//  main.cpp
//  BinaryTree1
//
//  Created by Winky Face on 15/05/2019.
//  Copyright © 2019 Barnaba Krupowicz. All rights reserved.
//

#include <iostream>
#include "binarytree.h"

int main() {
    BinaryTree<int,int> tree;
    tree.radd(32,0);
    tree.radd(16,0);
    tree.radd(34,0);
    tree.radd(31,0);
    tree.radd(8,0);
    tree.radd(17,0);
    std::cout << tree.countleaves() << std::endl;
    std::cout << tree.height() << std::endl;
    return 0;
}
