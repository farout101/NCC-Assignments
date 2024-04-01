#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

// to create new node
struct BSTNode* createBSTNode(int data) {
    struct BSTNode* bnode = (struct BSTNode*)malloc(sizeof(struct BSTNode));
    bnode->data = data;
    bnode->left = NULL;
    bnode->right = NULL;
    return bnode;
}

// to insert a new node into the BST
struct BSTNode* insertBST(struct BSTNode* root, int data) {
    if (root == NULL) {
        return createBSTNode(data);
    }
    if (data < root->data) {
        root->left = insertBST(root->left, data);
    } else if (data > root->data) {
        root->right = insertBST(root->right, data);
    }
    return root;
}

// to search for a key in the BST
struct BSTNode* searchBST(struct BSTNode* root, int key) {
    if (root == NULL || root->data == key) {
        return root;
    }
    if (key < root->data) {
        return searchBST(root->left, key);
    }
    return searchBST(root->right, key);
}

// to perform an inorder traversal of the BST (prints in sorted order)
void inorderTraversalBST(struct BSTNode* root) {
    if (root != NULL) {
        inorderTraversalBST(root->left);
        printf("%d ", root->data);
        inorderTraversalBST(root->right);
    }
}

// to perform a preorder traversal of the BST
void preorderTraversalBST(struct BSTNode* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorderTraversalBST(root->left);
        preorderTraversalBST(root->right);
    }
}

// to perform a postorder traversal of the BST
void postorderTraversalBST(struct BSTNode* root) {
    if (root != NULL) {
        postorderTraversalBST(root->left);
        postorderTraversalBST(root->right);
        printf("%d ", root->data);
    }
}
