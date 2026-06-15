#pragma once

#include <vector>
#include <cstddef>

class SplayTree {
public:
    SplayTree() = default;
    ~SplayTree();

    bool contains(int value) const;
    bool insert(int value);
    bool remove(int value);

    std::size_t size() const;
    bool empty() const;

    std::vector<int> values() const;

private:
    struct Node {
        int key;
        Node* left;
        Node* right;
        Node* parent;
        
        Node(int k) : key(k), left(nullptr), right(nullptr), parent(nullptr) {}
    };

    mutable Node* root = nullptr;
    std::size_t node_count = 0;

    void splay(Node* n) const;
    void rotate(Node* n) const;
    Node* find(int value) const;
    void clear(Node* u);
    void inOrder(Node* u, std::vector<int>& res) const;
};