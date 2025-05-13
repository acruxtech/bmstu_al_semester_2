#include "../include/BSTree.hpp"
#include <iostream>


int main() {
    BSTree tree1 = {50, 30, 70, 20, 40, 60, 80};
    std::cout << "Tree1:\n";
    tree1.print();
    
    BSTree tree2;
    tree2.add_element(50);
    tree2.add_element(30);
    tree2.add_element(70);
    tree2.add_element(20);
    tree2.add_element(40);
    tree2.add_element(60);
    tree2.add_element(80);
    std::cout << "\nTree2:\n";
    tree2.print();
    
    std::cout << "\nSearching in tree2:\n";
    std::cout << "Element 40: " << (tree2.find_element(40) ? "Found" : "Not found") << "\n";
    std::cout << "Element 45: " << (tree2.find_element(45) ? "Found" : "Not found") << "\n";
    
    std::cout << "\nDeleting elements from tree2:\n";
    std::cout << "Delete 20: " << (tree2.delete_element(20) ? "Success" : "Failed") << "\n";
    std::cout << "Delete 70: " << (tree2.delete_element(70) ? "Success" : "Failed") << "\n";
    std::cout << "Delete 99: " << (tree2.delete_element(99) ? "Success" : "Failed") << "\n";
    tree2.print();
    
    std::cout << "\nFile operations:\n";
    if (tree1.save_to_file("tree.txt")) {
        std::cout << "Tree saved to file\n";
        
        BSTree tree3;
        if (tree3.load_from_file("tree.txt")) {
            std::cout << "Tree loaded from file:\n";
            tree3.print();
        } else {
            std::cout << "Failed to load tree from file\n";
        }
    } else {
        std::cout << "Failed to save tree to file\n";
    }
    
    return 0;
}
