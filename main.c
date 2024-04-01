#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "bst.h"

int main() {
    int choice, data;

    while (1) {
        printf("1 for Stack Operations\n");
        printf("2 for BST Operations\n");
        printf("3 for Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        system("cls");

        if (choice == 1) {
            struct Stack* stack = createStack();
            do {
                printf("\nStack Operations:\n");
                printf("1. Push\n");
                printf("2. Pop\n");
                printf("3. Print Stack\n");
                printf("4. Exit Stack Operations\n");
                printf("Enter your choice: ");
                scanf("%d", &choice);
                system("cls");

                switch (choice) {
                    case 1:
                        printf("Enter data to push: ");
                        scanf("%d", &data);
                        push(stack, data);
                        break;
                    case 2:
                        if (!isEmpty(stack)) {
                            printf("%d popped from stack\n", pop(stack));
                        } else {
                            printf("Stack is empty\n");
                        }
                        break;
                    case 3:
                        printf("Stack elements: ");
                        printStack(stack);
                        printf("\n");
                        break;
                    case 4:
                        printf("Exiting Stack Operations\n");
                        break;
                    default:
                        printf("Invalid choice! Please enter a valid choice.\n");
                }
            } while (choice != 4);
            // Free the memory allocated by the stack
            free(stack);
        } else if (choice == 2) {
            // Create a new binary search tree
            struct BSTNode* root = NULL;

            do {
                printf("\nBinary Search Tree (BST) Operations:\n");
                printf("1. Insert\n");
                printf("2. Print Inorder Traversal\n");
                printf("3. Print Preorder Traversal\n");
                printf("4. Print Postorder Traversal\n");
                printf("5. Search\n");
                printf("6. Exit BST Operations\n");
                printf("Enter your choice: ");
                scanf("%d", &choice);
                system("cls");

                switch (choice) {
                    case 1:
                        printf("Enter data to insert: ");
                        scanf("%d", &data);
                        root = insertBST(root, data);
                        break;
                    case 2:
                        printf("Inorder traversal: ");
                        inorderTraversalBST(root);
                        printf("\n");
                        break;
                    case 3:
                        printf("Preorder traversal: ");
                        preorderTraversalBST(root);
                        printf("\n");
                        break;
                    case 4:
                        printf("Postorder traversal: ");
                        postorderTraversalBST(root);
                        printf("\n");
                        break;
                    case 5:
                        printf("Enter data to search: ");
                        scanf("%d", &data);
                        if (searchBST(root, data) != NULL) {
                            printf("%d found in the BST\n", data);
                        } else {
                            printf("%d not found in the BST\n", data);
                        }
                        break;
                    case 6:
                        printf("Exiting BST Operations\n");
                        break;
                    default:
                        printf("Invalid choice! Please enter a valid choice.\n");
                }
            } while (choice != 6);
            // Free the memory allocated by the binary search tree
            free(root);
        } else if (choice == 3) {
            break;
        } else {
            printf("Invalid choice! Please enter a valid choice.\n");
        }
    }
    return 0;
}
