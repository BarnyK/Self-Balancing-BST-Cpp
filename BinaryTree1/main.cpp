#include <iostream>
#include <exception>
#include <vector>
#include <cmath>
#include "binarytree.h"

int main() {
    Dictionary<int,int> tree;
    
    // Addition and display
    tree.add(16,1);
    tree.add(32,2);
    tree.add(8, 4);
    tree.add(15,5);
    tree.display();
    std::cout << std::endl;
    
    // Addition when key is already in the dictionary
    if(!tree.add(15,234))
        std::cout << "15 was added" << std::endl;
    else
        std::cout << "15 wasn't added" << std::endl;
    
    // Remove function
    tree.remove(15);
    tree.display();
    std::cout << std::endl;
    
    // Rotation happens after adding 14
    tree.add(13,23);
    tree.display();
    std::cout << std::endl;
    
    tree.add(14,238723498);
    tree.display();
    std::cout << std::endl;
    
    // Removal function when node is a root
    if(!tree.remove(16))
        std::cout << "16 was removed" << std::endl;
    else
        std::cout << "16 wasn't removed" << std::endl;
    tree.display();
    std::cout << std::endl;
    
    // Heigh and size functions
    std::cout << "Height: " << tree.height() << std::endl;
    std::cout << "Size: " << tree.size() << std::endl;
    
    // Get
    std::cout << "Value under key 14: " << tree.get(14) << std::endl;
    tree.get(14) = 5;
    std::cout << "Value under key 14: " << tree.get(14) << std::endl;
    
    // Pop
    std::cout << "Value under 13: " << tree.pop(13) << std::endl;
    std::cout << "Tree after poping 13:" << std::endl;
    tree.display();
    std::cout << std::endl;
    
    // Contains
    if(tree.contains_key(13))
        std::cout << "Key 13 in the dictionary" << std::endl;
    else
        std::cout << "Key 13 not in the dictionary" << std::endl;
    
    // Clear
    tree.clear();
    tree.display();
    std::cout << std::endl;
    
    std::cout << "Simple left rotation" << std::endl;
    tree.add(1,1);
    tree.add(2,2);
    tree.display();
    std::cout << std::endl;
    tree.add(3,3);
    tree.display();
    std::cout << std::endl;
    tree.clear();
    
    std::cout << "Simple right rotation" << std::endl;
    tree.add(3,3);
    tree.add(2,2);
    tree.display();
    std::cout << std::endl;
    tree.add(1,1);
    tree.display();
    std::cout << std::endl;
    tree.clear();
    
    std::cout << "Right left rotation" << std::endl;
    tree.add(2,2);
    tree.add(1,1);
    tree.add(5,5);
    tree.add(3,3);
    tree.add(6,6);
    tree.display();
    std::cout << std::endl;
    tree.add(4,4);
    tree.display();
    std::cout << std::endl;
    tree.clear();
    
    std::cout << "Left right rotation" << std::endl;
    tree.add(5,5);
    tree.add(6,6);
    tree.add(2,2);
    tree.add(1,1);
    tree.add(4,4);
    tree.display();
    std::cout << std::endl;
    tree.add(3,3);
    tree.display();
    std::cout << std::endl;
    
    
    
    // Not int int
    std::cout << "Different dictionary" << std::endl;
    Dictionary<float, char> letters;
    letters.add(1, 'a');
    letters.add(2, 'b');
    letters.add(3, 'c');
    letters.add(4, 'd');
    letters.add(5, 'e');
    letters.add(6, 'f');
    letters.display();
    std::cout << "5th letter: " << letters.get(5) << std::endl;
    
    return 0;
}
