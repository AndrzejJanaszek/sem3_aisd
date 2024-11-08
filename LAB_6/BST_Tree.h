#ifndef BST_TREE
#define BST_TREE

#include <iostream>

class BST_Node{
public:
    int key = 0;
    BST_Node* parent = nullptr;
    BST_Node* left = nullptr;
    BST_Node* right = nullptr;

    BST_Node(){
        this->key = 0;
        this->parent = nullptr;
        this->left = nullptr;
        this->right = nullptr;
    }

    BST_Node(int key){
        this->key = key;
        this->parent = nullptr;
        this->left = nullptr;
        this->right = nullptr;
    }

    BST_Node(int key, BST_Node* parent, BST_Node* left, BST_Node* right){
        this->key = key;
        this->parent = parent;
        this->left = left;
        this->right = right;
    }

    static void insert(BST_Node* node, int key);
    static void deleteNode(BST_Node* node);

    static void printNodePreOrder(BST_Node* node);
    static void printNodeInOrder(BST_Node* node);
    static void printNodePostOrder(BST_Node* node);

    static BST_Node* min(BST_Node* node);
    static BST_Node* max(BST_Node* node);

    static BST_Node* inOrderSuccessor(BST_Node* node);
    static BST_Node* inOrderPredeccessor(BST_Node* node);
};

void BST_Node::insert(BST_Node* node, int key){
    BST_Node* node_ptr = node;
    BST_Node* last_parent = nullptr;

    while( node_ptr ){
        last_parent = node_ptr;

        if(node_ptr->key < key){
            node_ptr = node_ptr->right;
            if (node_ptr == nullptr){
                last_parent->right = new BST_Node(key, nullptr, nullptr, nullptr);
                return;
            }
        }
        else{
            node_ptr = node_ptr->left;
            if (node_ptr == nullptr){
                last_parent->left = new BST_Node(key, nullptr, nullptr, nullptr);
                return;
            }
        }
    }
}

void BST_Node::deleteNode(BST_Node* node){
    // leaf
    if(node->left == nullptr && node->right == nullptr){
        BST_Node* tmp = node;

        BST_Node* p = node->parent;
        // delete node
        if(p->right == node){
            p->right = nullptr;
        }
        else{
            p->left = nullptr;
        }
        delete tmp;
        return;
    }
    // if single child
    // replace value and delete child
    if((node->left == nullptr && node->right != nullptr) || (node->left != nullptr && node->right == nullptr) ){
        if(node->left){
            node->key = node->right->key;
            BST_Node* temp = node->right;
            delete temp;
            node->right = nullptr;
        }
        else{
            node->key = node->left->key;
            BST_Node* temp = node->left;
            delete temp;
            node->left = nullptr;
        }

        return;
    }

    // 3rd case
    if(node->parent->right == node){
        // right child
        BST_Node* repNode = BST_Node::inOrderPredeccessor(node);
        node->key = repNode->key;   // copy node (key)
        BST_Node::deleteNode(repNode);
    }
}

void BST_Node::printNodePreOrder(BST_Node* node){
    // print root
    std::cout << node->key << " ";

    // print lewo
    if(node->left != nullptr){
        BST_Node::printNodePreOrder(node->left);
    }

    // print prawo
    if(node->right != nullptr){
        BST_Node::printNodePreOrder(node->right);
    }
}

void BST_Node::printNodeInOrder(BST_Node* node){
    // print lewo
    if(node->left != nullptr){
        BST_Node::printNodePreOrder(node->left);
    }

    // print root
    std::cout << node->key << " ";

    // print prawo
    if(node->right != nullptr){
        BST_Node::printNodePreOrder(node->right);
    }
}

void BST_Node::printNodePostOrder(BST_Node* node){
    // print lewo
    if(node->left != nullptr){
        BST_Node::printNodePreOrder(node->left);
    }

    // print prawo
    if(node->right != nullptr){
        BST_Node::printNodePreOrder(node->right);
    }

    // print root
    std::cout << node->key << " ";
}

BST_Node* BST_Node::min(BST_Node* node){
    BST_Node* ptr = node;
    while(ptr->left != nullptr){
        ptr = ptr->left;
    }

    return ptr;
}

BST_Node* BST_Node::max(BST_Node* node){
    BST_Node* ptr = node;
    while(ptr->right != nullptr){
        ptr = ptr->right;
    }

    return ptr;
}

BST_Node* BST_Node::inOrderSuccessor(BST_Node* node){
    if(node->right != nullptr){
        return BST_Node::min(node->right);
    }
    
    BST_Node* ptr = node->parent;

    while (ptr != nullptr)
    {
        if(ptr->right != nullptr && ptr->right != node){
            // jezeli jest prawe w przodku
            return BST_Node::min(ptr);
        }

        ptr = ptr->parent;
    }

    return ptr;
}

BST_Node* BST_Node::inOrderPredeccessor(BST_Node* node){
    if(node->left != nullptr){
        return BST_Node::max(node->left);
    }
    
    BST_Node* ptr = node->parent;

    while (ptr != nullptr)
    {
        if(ptr->left != nullptr && ptr->left != node){
            // jezeli jest lewe w przodku
            return BST_Node::max(ptr);
        }

        ptr = ptr->parent;
    }

    return ptr;
}

#endif