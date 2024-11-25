#include <iostream>
#include "BST_Tree.h"

int main(int argc, char const *argv[])
{
    BST_Node tree(10);
    tree.insert(&tree, 1);
    tree.insert(&tree, 20);
    BST_Node::printNodeInOrder(&tree);
    // tree.printNodeInOrder(&tree);

    return 0;
}

