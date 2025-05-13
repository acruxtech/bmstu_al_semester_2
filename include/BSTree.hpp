#ifndef BSTREE_H
#define BSTREE_H


#include <initializer_list>
#include <string>


struct Node {
    int value;
    Node* left;
    Node* right;
    Node* parent;
    
    Node(int val, Node* p = nullptr) 
        : value(val), left(nullptr), right(nullptr), parent(p) {}
};


class BSTree {
    private:
        Node* root;
        
        Node* find_min(Node* node) const;
        Node* find_max(Node* node) const;
        Node* find_node(int value) const;
        void print_tree(Node* node, int level = 0) const;
        void clear(Node* node);
        void save_to_file(Node* node, std::ofstream& out) const;
        Node* load_from_file(std::ifstream& in, Node* parent = nullptr);
    
    public:
        BSTree();
        BSTree(std::initializer_list<int> list);
        ~BSTree();
        
        bool add_element(int value);
        bool delete_element(int value);
        bool find_element(int value) const;
        void print() const;
        bool save_to_file(const std::string& path) const;
        bool load_from_file(const std::string& path);
};

#endif // BSTREE_H
