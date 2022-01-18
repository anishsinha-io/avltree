#include <stdlib.h>
#include <stdio.h>

typedef struct AVLNode {
    double val;
    struct AVLNode *left;
    struct AVLNode *right;
    int height;
} AVLNode;

typedef struct AVLTree {
    AVLNode *root;
} AVLTree;

AVLNode *avlnode(double val) {
    AVLNode *node = malloc(sizeof(AVLNode));
    node->val = val;
    node->left = node->right = NULL;
    node->height = 0;
    return node;
}

AVLTree *avltree() {
    AVLTree *tree = malloc(sizeof(AVLTree));
    tree->root = NULL;
    return tree;
}

static int get_height(AVLNode *n) {
    if (n == NULL) return -1;
    return n->height;
}

static int get_balance(AVLNode *n) {
    if (n == NULL) return -1;
    return get_height(n->left) - get_height(n->right);
}

static int max(int x, int y) {
    return (x > y) ? x : y;
}

static AVLNode *rotate_right(AVLNode *gr) {
    AVLNode *par = gr->left;
    AVLNode *ch = par->right;
    par->right = gr;
    gr->left = ch;
    gr->height = max(get_height(gr->left), get_height(gr->right)) + 1;
    par->height = max(get_height(par->left), get_height(par->right)) + 1;
    return par;
}


static AVLNode *rotate_left(AVLNode *gr) {
    AVLNode *par = gr->right;
    AVLNode *ch = par->left;
    par->left = gr;
    gr->right = ch;
    gr->height = max(get_height(gr->left), get_height(gr->right)) + 1;
    par->height = max(get_height(par->left), get_height(par->right)) + 1;
    return par;
}


static AVLNode *insert_and_rebalance(AVLNode *root, double val) {
    if (root == NULL) return avlnode(val);
    if (val < root->val) root->left = insert_and_rebalance(root->left, val);
    else if (val > root->val) root->right = insert_and_rebalance(root->right, val);
    else return root;
    root->height = max(get_height(root->left), get_height(root->right)) + 1;
    int balance = get_balance(root);
    if (balance > 1 && val < root->left->val) return rotate_right(root);
    if (balance < -1 && val > root->right->val) return rotate_left(root);
    if (balance > 1 && val > root->left->val) {
        root->left = rotate_left(root->left);
        return rotate_right(root);
    }
    if (balance < -1 && val < root->right->val) {
        root->right = rotate_right(root->right);
        return rotate_left(root);
    }
    return root;
}

static AVLNode *get_inorder_successor(AVLNode *node) {
    AVLNode *t = node->right;
    while (t->left != NULL) t = t->left;
    return t;
}

static AVLNode *delete_and_rebalance(AVLNode *root, double val) {
    if (root == NULL) return root;
    if (val < root->val) root->left = delete_and_rebalance(root->left, val);
    else if (val > root->val) root->right = delete_and_rebalance(root->right, val);
    else {
        if (root->left == NULL || root->right == NULL) {
            AVLNode *t = root->left ? root->left : root->right;
            if (t == NULL) {
                t = root;
                root = NULL;
            } else *root = *t;
            free(t);
        } else {
            AVLNode *t = get_inorder_successor(root);
            root->val = t->val;
            root->right = delete_and_rebalance(root->right, t->val);
        }
    }
    if (root == NULL) return root;
    root->height = max(get_height(root->left), get_height(root->right)) + 1;
    int balance = get_balance(root);
    if (balance > 1 && get_balance(root->left) >= 0) return rotate_right(root);
    if (balance > 1 && get_balance(root->left) < 0) {
        root->left = rotate_left(root->left);
        return rotate_right(root);
    }
    if (balance < -1 && get_balance(root->right) <= 0) return rotate_left(root);
    if (balance < -1 && get_balance(root->right) > 0) {
        root->right = rotate_right(root->right);
        return rotate_left(root);
    }
    return root;
}

void insert(AVLTree *tree, double val) {
    if (!tree) return;
    tree->root = insert_and_rebalance(tree->root, val);
}

void delete(AVLTree *tree, double val) {
    if (!tree) return;
    tree->root = delete_and_rebalance(tree->root, val);
}

AVLNode *root(AVLTree *tree) {
    return tree->root;
}


void inorder(AVLNode *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%f\t", root->val);
        inorder(root->right);
    }
}

void preorder(AVLNode *root) {
    if (root != NULL) {
        printf("%f\t", root->val);
        preorder(root->left);
        preorder(root->right);
    }
}
