#ifndef BST_H
#define BST_H

struct BSTNode {
    int data;
    struct BSTNode* left;
    struct BSTNode* right;
};

// Functions
struct BSTNode* createBSTNode(int data);
struct BSTNode* insertBST(struct BSTNode* root, int data);
struct BSTNode* searchBST(struct BSTNode* root, int key);
void inorderTraversalBST(struct BSTNode* root);
void preorderTraversalBST(struct BSTNode* root);
void postorderTraversalBST(struct BSTNode* root);

#endif