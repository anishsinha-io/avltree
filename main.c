#include "avl/avl.h"
#include <stdio.h>

int main() {
    AVLTree *tree1 = avltree();
    insert(tree1, 9);
    insert(tree1, 5);
    insert(tree1, 10);
    insert(tree1, 0);
    insert(tree1, 6);
    insert(tree1, 11);
    insert(tree1, -1);
    insert(tree1, 1);
    insert(tree1, 2);
    preorder(root(tree1));
    printf("\n");
    delete(tree1, 10);
    preorder(root(tree1));
    return 0;
}
