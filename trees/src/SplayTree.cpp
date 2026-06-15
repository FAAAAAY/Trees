#include "../include/SplayTree.hpp"

SplayTree::~SplayTree() {
    clear(root);
}

void SplayTree::clear(Node* u) {
    if (!u) return;
    clear(u->left);
    clear(u->right);
    delete u;
}

void SplayTree::rotate(Node* n) const {
    Node* p = n->parent;
    if (!p) return;
    Node* g = p->parent;

    if (g) {
        if (g->left == p) g->left = n;
        else g->right = n;
    }
    n->parent = g;

    if (p->left == n) {
        p->left = n->right;
        if (n->right) n->right->parent = p;
        n->right = p;
    } else {
        p->right = n->left;
        if (n->left) n->left->parent = p;
        n->left = p;
    }
    p->parent = n;
}

void SplayTree::splay(Node* n) const {
    if (!n) return;
    while (n->parent) {
        Node* p = n->parent;
        Node* g = p->parent;
        if (!g) {
            rotate(n);
        } else {
            bool is_p_left = (g->left == p);
            bool is_n_left = (p->left == n);
            if (is_p_left == is_n_left) {
                rotate(p);
                rotate(n);
            } else {
                rotate(n);
                rotate(n);
            }
        }
    }
    root = n;
}

SplayTree::Node* SplayTree::find(int value) const {
    Node* curr = root;
    Node* last = nullptr;
    
    while (curr) {
        last = curr;
        if (curr->key == value) {
            break;
        }
        if (value < curr->key) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
    
    if (last) {
        splay(last);
    }
    
    if (last && last->key == value) {
        return last;
    }
    return nullptr;
}

bool SplayTree::contains(int value) const {
    return find(value) != nullptr;
}

bool SplayTree::insert(int value) {
    if (!root) {
        root = new Node(value);
        node_count++;
        return true;
    }

    Node* curr = root;
    Node* p = nullptr;
    
    while (curr) {
        p = curr;
        if (value == curr->key) {
            splay(curr);
            return false;
        }
        if (value < curr->key) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }

    Node* n = new Node(value);
    n->parent = p;
    if (value < p->key) {
        p->left = n;
    } else {
        p->right = n;
    }
    
    node_count++;
    splay(n);
    return true;
}

bool SplayTree::remove(int value) {
    Node* target = find(value);
    if (!target) return false;

    Node* L = target->left;
    Node* R = target->right;

    if (!L && !R) {
        root = nullptr;
    } else if (!L) {
        root = R;
        R->parent = nullptr;
    } else if (!R) {
        root = L;
        L->parent = nullptr;
    } else {
        L->parent = nullptr;
        Node* maxL = L;
        while (maxL->right) {
            maxL = maxL->right;
        }
        root = L; 
        splay(maxL); 
        root->right = R;
        R->parent = root;
    }

    delete target;
    node_count--;
    return true;
}

std::size_t SplayTree::size() const {
    return node_count;
}

bool SplayTree::empty() const {
    return node_count == 0;
}

std::vector<int> SplayTree::values() const {
    std::vector<int> res;
    res.reserve(node_count);
    inOrder(root, res);
    return res;
}

void SplayTree::inOrder(Node* u, std::vector<int>& res) const {
    if (!u) return;
    inOrder(u->left, res);
    res.push_back(u->key);
    inOrder(u->right, res);
}