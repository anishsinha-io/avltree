#ifndef AVLTREE_AVL_H
#define AVLTREE_AVL_H

typedef struct AVLNode AVLNode;
typedef struct AVLTree AVLTree;

int get_balance(AVLNode *);
void inorder(AVLNode *root);
void preorder(AVLNode *root);
void insert(AVLTree *, double);
void delete(AVLTree *, double);
AVLTree *avltree(void);
AVLNode *avlnode(double);
AVLNode *root(AVLTree *);

#endif //AVLTREE_AVL_H
