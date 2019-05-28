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
    Dictionary<int,int> tree;

    tree.add(16,1);
    tree.add(32,2);
    tree.add(48,3);
    tree.add(8,4);
    tree.remove(48);
    std::cout << tree.pop(8) << std::endl;
    return 0;
}
