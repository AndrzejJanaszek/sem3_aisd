#ifndef BST_TREE
#define BST_TREE

#include <iostream>

template <class T, class CompareFunction>
class BST_Node {
public:
    T key;
    BST_Node* parent = nullptr;
    BST_Node* left = nullptr;
    BST_Node* right = nullptr;

    static CompareFunction compareFunction;

    BST_Node() {
        this->key;
        this->parent = nullptr;
        this->left = nullptr;
        this->right = nullptr;
    }

    BST_Node(T key, CompareFunction compareFunction = CompareFunction()) {
        this->key = key;
        this->parent = nullptr;
        this->left = nullptr;
        this->right = nullptr;
    }

    BST_Node(T key, BST_Node* parent, BST_Node* left, BST_Node* right) {
        this->key = key;
        this->parent = parent;
        this->left = left;
        this->right = right;
    }

    static void insert(BST_Node* node, T key);
    static void deleteNode(BST_Node* node);

    static void printNodePreOrder(BST_Node* node);
    static void printNodeInOrder(BST_Node* node);
    static void printNodePostOrder(BST_Node* node);

    static BST_Node* min(BST_Node* node);
    static BST_Node* max(BST_Node* node);

    static BST_Node* inOrderSuccessor(BST_Node* node);
    static BST_Node* inOrderPredeccessor(BST_Node* node);
};

template <class T, class CompareFunction>
CompareFunction BST_Node<T, CompareFunction>::compareFunction;

template <class T, class CompareFunction>
void BST_Node<T, CompareFunction>::insert(BST_Node* node, T key) {
    BST_Node* node_ptr = node;
    BST_Node* last_parent = nullptr;

    while (node_ptr) {
        last_parent = node_ptr;

        if (compareFunction(node_ptr->key, key)) {
            node_ptr = node_ptr->right;
            if (node_ptr == nullptr) {
                last_parent->right = new BST_Node(key, nullptr, nullptr, nullptr);
                return;
            }
        }
        else {
            node_ptr = node_ptr->left;
            if (node_ptr == nullptr) {
                last_parent->left = new BST_Node(key, nullptr, nullptr, nullptr);
                return;
            }
        }
    }
}

template <class T, class CompareFunction>
void BST_Node<T, CompareFunction>::deleteNode(BST_Node* node) {
    // leaf
    if (node->left == nullptr && node->right == nullptr) {
        BST_Node* tmp = node;
        BST_Node* p = node->parent;
        if (p->right == node) {
            p->right = nullptr;
        }
        else {
            p->left = nullptr;
        }
        delete tmp;
        return;
    }

    // if single child
    if ((node->left == nullptr && node->right != nullptr) || (node->left != nullptr && node->right == nullptr)) {
        BST_Node* child = node->left ? node->left : node->right;
        node->key = child->key;
        if (node->left) node->left = nullptr;
        if (node->right) node->right = nullptr;
        delete child;
        return;
    }

    // 3rd case - two children
    BST_Node* repNode = BST_Node::inOrderSuccessor(node);
    node->key = repNode->key;
    BST_Node::deleteNode(repNode);
}

template <class T, class CompareFunction>
void BST_Node<T, CompareFunction>::printNodePreOrder(BST_Node* node) {
    if (node == nullptr) return;
    std::cout << node->key << " ";
    BST_Node::printNodePreOrder(node->left);
    BST_Node::printNodePreOrder(node->right);
}

template <class T, class CompareFunction>
void BST_Node<T, CompareFunction>::printNodeInOrder(BST_Node* node) {
    if (node == nullptr) return;
    BST_Node::printNodeInOrder(node->left);
    std::cout << node->key << " ";
    BST_Node::printNodeInOrder(node->right);
}

template <class T, class CompareFunction>
void BST_Node<T, CompareFunction>::printNodePostOrder(BST_Node* node) {
    if (node == nullptr) return;
    BST_Node::printNodePostOrder(node->left);
    BST_Node::printNodePostOrder(node->right);
    std::cout << node->key << " ";
}

template <class T, class CompareFunction>
BST_Node<T, CompareFunction>* BST_Node<T, CompareFunction>::min(BST_Node* node) {
    BST_Node* ptr = node;
    while (ptr && ptr->left != nullptr) {
        ptr = ptr->left;
    }
    return ptr;
}

template <class T, class CompareFunction>
BST_Node<T, CompareFunction>* BST_Node<T, CompareFunction>::max(BST_Node* node) {
    BST_Node* ptr = node;
    while (ptr && ptr->right != nullptr) {
        ptr = ptr->right;
    }
    return ptr;
}

template <class T, class CompareFunction>
BST_Node<T, CompareFunction>* BST_Node<T, CompareFunction>::inOrderSuccessor(BST_Node* node) {
    if (node->right != nullptr) {
        return BST_Node::min(node->right);
    }
    
    BST_Node* ptr = node->parent;
    while (ptr != nullptr) {
        if (ptr->right != nullptr && ptr->right != node) {
            return BST_Node::min(ptr);
        }
        ptr = ptr->parent;
    }
    return ptr;
}

template <class T, class CompareFunction>
BST_Node<T, CompareFunction>* BST_Node<T, CompareFunction>::inOrderPredeccessor(BST_Node* node) {
    if (node->left != nullptr) {
        return BST_Node::max(node->left);
    }
    
    BST_Node* ptr = node->parent;
    while (ptr != nullptr) {
        if (ptr->left != nullptr && ptr->left != node) {
            return BST_Node::max(ptr);
        }
        ptr = ptr->parent;
    }
    return ptr;
}

#endif
