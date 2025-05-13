#include "../include/BSTree.hpp"
#include <iostream>
#include <fstream>


BSTree::BSTree() : root(nullptr) {}


BSTree::BSTree(std::initializer_list<int> list) : root(nullptr) {
    for (int value : list) {
        add_element(value);
    }
}


BSTree::~BSTree() {
    clear(root);
}


bool BSTree::add_element(int value) {
    if (!root) {
        root = new Node(value);
        return true;
    }
    
    Node* current = root;
    while (true) {
        if (value == current->value) {
            return false;
        }
        
        if (value < current->value) {
            if (!current->left) {
                current->left = new Node(value, current);
                return true;
            }
            current = current->left;
        } else {
            if (!current->right) {
                current->right = new Node(value, current);
                return true;
            }
            current = current->right;
        }
    }
}


bool BSTree::delete_element(int value) {
    Node* node = find_node(value);
    if (!node) return false;
    
    if (node->left && node->right) {
        Node* successor = find_min(node->right);
        node->value = successor->value;
        node = successor;
    }
    
    Node* child = node->left ? node->left : node->right;
    Node* parent = node->parent;
    
    if (child) {
        child->parent = parent;
    }
    
    if (!parent) {
        root = child;
    } else if (parent->left == node) {
        parent->left = child;
    } else {
        parent->right = child;
    }
    
    delete node;
    return true;
}


bool BSTree::find_element(int value) const {
    return find_node(value) != nullptr;
}


void BSTree::print() const {
    print_tree(root);
    std::cout << std::endl;
}


bool BSTree::save_to_file(const std::string& path) const {
    std::ofstream out(path);
    if (!out.is_open()) return false;
    
    save_to_file(root, out);
    out.close();
    return true;
}


bool BSTree::load_from_file(const std::string& path) {
    std::ifstream in(path);
    if (!in.is_open()) return false;
    
    clear(root);
    root = load_from_file(in);
    in.close();
    return root != nullptr;
}


Node* BSTree::find_min(Node* node) const {
    while (node && node->left) {
        node = node->left;
    }
    return node;
}


Node* BSTree::find_max(Node* node) const {
    while (node && node->right) {
        node = node->right;
    }
    return node;
}


Node* BSTree::find_node(int value) const {
    Node* current = root;
    while (current) {
        if (value == current->value) {
            return current;
        }
        current = value < current->value ? current->left : current->right;
    }
    return nullptr;
}


void BSTree::print_tree(Node* node, int level) const {
    if (!node) return;
    
    print_tree(node->right, level + 1);
    
    for (int i = 0; i < level; ++i) {
        std::cout << "    ";
    }
    std::cout << node->value << "\n";
    
    print_tree(node->left, level + 1);
}


void BSTree::clear(Node* node) {
    if (node) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}


void BSTree::save_to_file(Node* node, std::ofstream& out) const {
    if (!node) {
        out << "null ";
        return;
    }
    
    out << node->value << " ";
    save_to_file(node->left, out);
    save_to_file(node->right, out);
}


Node* BSTree::load_from_file(std::ifstream& in, Node* parent) {
    std::string token;
    if (!(in >> token) || token == "null") {
        return nullptr;
    }
    
    try {
        int value = std::stoi(token);
        Node* node = new Node(value, parent);
        node->left = load_from_file(in, node);
        node->right = load_from_file(in, node);
        return node;
    } catch (...) {
        return nullptr;
    }
}
