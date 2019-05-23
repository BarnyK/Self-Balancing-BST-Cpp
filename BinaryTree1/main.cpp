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
    tree.add(32,0);
    tree.add(16,0);
    tree.add(34,0);
    tree.add(31,0);
    tree.add(8,0);
    std::cout << tree.countleaves() << std::endl;
    std::cout << tree.height() << std::endl;
    
    return 0;
}
