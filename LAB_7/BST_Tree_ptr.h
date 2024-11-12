#ifndef BST_TREE
#define BST_TREE

#include <iostream>
#include <memory>

template <class T, class CompareFunction>
class BST_Node{
public:
    std::unique_ptr<T> key;
    BST_Node* parent = nullptr;
    BST_Node* left = nullptr;
    BST_Node* right = nullptr;

    CompareFunction compareFunction;

    // Konstruktor domyślny
    BST_Node() : key(nullptr), parent(nullptr), left(nullptr), right(nullptr) {}

    // Konstruktor inicjalizujący z kluczem
    BST_Node(T key_value, CompareFunction compareFunction = CompareFunction())
        : key(std::make_unique<T>(key_value)), compareFunction(compareFunction), parent(nullptr), left(nullptr), right(nullptr) {}

    // Konstruktor inicjalizujący z kluczem i wskaźnikami do innych węzłów
    BST_Node(T key_value, BST_Node* parent, BST_Node* left, BST_Node* right)
        : key(std::make_unique<T>(key_value)), parent(parent), left(left), right(right) {}

    // Funkcje statyczne do zarządzania węzłami drzewa
    static void insert(BST_Node* node, T key_value);
    static void printNodePreOrder(BST_Node* node);
    static void printNodeInOrder(BST_Node* node);
    static void printNodePostOrder(BST_Node* node);

    static BST_Node* min(BST_Node* node);
    static BST_Node* max(BST_Node* node);

    static BST_Node* inOrderSuccessor(BST_Node* node);
    static BST_Node* inOrderPredecessor(BST_Node* node);
};

// Implementacja metod
template <class T, class CompareFunction>
void BST_Node<T, CompareFunction>::insert(BST_Node* node, T key_value) {
    BST_Node* node_ptr = node;
    BST_Node* last_parent = nullptr;

    while (node_ptr) {
        last_parent = node_ptr;

        if (node_ptr->compareFunction(*(node_ptr->key), key_value)) {
            node_ptr = node_ptr->right;
            if (node_ptr == nullptr) {
                last_parent->right = new BST_Node(key_value, last_parent, nullptr, nullptr);
                return;
            }
        } else {
            node_ptr = node_ptr->left;
            if (node_ptr == nullptr) {
                last_parent->left = new BST_Node(key_value, last_parent, nullptr, nullptr);
                return;
            }
        }
    }
}

template <class T, class CompareFunction>
void BST_Node<T, CompareFunction>::printNodePreOrder(BST_Node* node) {
    if (!node) return;
    std::cout << *(node->key) << " ";
    printNodePreOrder(node->left);
    printNodePreOrder(node->right);
}

template <class T, class CompareFunction>
void BST_Node<T, CompareFunction>::printNodeInOrder(BST_Node* node) {
    if (!node) return;
    printNodeInOrder(node->left);
    std::cout << *(node->key) << " ";
    printNodeInOrder(node->right);
}

template <class T, class CompareFunction>
void BST_Node<T, CompareFunction>::printNodePostOrder(BST_Node* node) {
    if (!node) return;
    printNodePostOrder(node->left);
    printNodePostOrder(node->right);
    std::cout << *(node->key) << " ";
}

template <class T, class CompareFunction>
BST_Node<T, CompareFunction>* BST_Node<T, CompareFunction>::min(BST_Node* node) {
    while (node && node->left != nullptr) {
        node = node->left;
    }
    return node;
}

template <class T, class CompareFunction>
BST_Node<T, CompareFunction>* BST_Node<T, CompareFunction>::max(BST_Node* node) {
    while (node && node->right != nullptr) {
        node = node->right;
    }
    return node;
}

template <class T, class CompareFunction>
BST_Node<T, CompareFunction>* BST_Node<T, CompareFunction>::inOrderSuccessor(BST_Node* node) {
    if (node->right) {
        return min(node->right);
    }
    BST_Node* ptr = node->parent;
    while (ptr && node == ptr->right) {
        node = ptr;
        ptr = ptr->parent;
    }
    return ptr;
}

template <class T, class CompareFunction>
BST_Node<T, CompareFunction>* BST_Node<T, CompareFunction>::inOrderPredecessor(BST_Node* node) {
    if (node->left) {
        return max(node->left);
    }
    BST_Node* ptr = node->parent;
    while (ptr && node == ptr->left) {
        node = ptr;
        ptr = ptr->parent;
    }
    return ptr;
}

#endif
