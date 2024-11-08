#include <iostream>
#include "BST_Tree.h"


int max(int a, int b){
    if (a > b) return a;
    return b;
}
int maxDepth(BST_Node* node){
    if(node == nullptr)
        return 0;

    int l = maxDepth(node->left);
    int r = maxDepth(node->right);

    return max(l,r)+1;
}

int main(int argc, char const *argv[])
{
    BST_Node tree(10);
    tree.insert(&tree, 1);
    tree.insert(&tree, 20);
    BST_Node::printNodeInOrder(&tree);
    // tree.printNodeInOrder(&tree);



    return 0;
}

