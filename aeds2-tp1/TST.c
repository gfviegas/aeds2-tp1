//
//  TST.c
//  aeds2-tp1
//
//  Created by Gustavo Viegas on 17/04/18.
//  Copyright © 2018 UFV Florestal. All rights reserved.
//

#include "TST.h"

// A utility function to create a new ternary search tree TSTNode
TSTNodePointer newNode(char data) {
    TSTNodePointer temp = (TSTNodePointer) malloc(sizeof(TSTNode));
    temp->data = data;
    temp->isEndOfString = 0;
    temp->left = temp->eq = temp->right = NULL;
    return temp;
}

// Function to insert a new word in a Ternary Search Tree
void insertTST(TSTNodePointer* root, char *word) {
    // Base Case: Tree is empty
    if (!(*root))
        *root = newNode(*word);
    // If current character of word is smaller than root's character,
    // then insert this word in left subtree of root
    if ((*word) < (*root)->data)
        insertTST(&( (*root)->left ), word);
    // If current character of word is greate than root's character,
    // then insert this word in right subtree of root
    else if ((*word) > (*root)->data)
        insertTST(&( (*root)->right ), word);
    // If current character of word is same as root's character,
    else {
        if (*(word+1))
            insertTST(&( (*root)->eq ), word+1);
        else
            // the last character of the word
            (*root)->isEndOfString = 1;
    }
}
// Function to search a given word in TST
int searchTST(TSTNodePointer root, char *word) {
    if (!root)
        return 0;
    if (*word < (root)->data)
        return searchTST(root->left, word);
    else if (*word > (root)->data)
        return searchTST(root->right, word);
    else
    {
        if (*(word+1) == '\0')
            return root->isEndOfString;
        return searchTST(root->eq, word+1);
    }
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int heightTST(TSTNodePointer root) {
    if (root == NULL) return -1;
    int leftHeight = heightTST(root->left);
    int rightHeight = heightTST(root->right);
    int eqHeight = heightTST(root->eq);
    return 1 + max(max(leftHeight, eqHeight), rightHeight);
}

int nodeAmountTST(TSTNodePointer root) {
    if (root == NULL) return 0;
    return 1 + nodeAmountTST(root->left) + nodeAmountTST(root->eq) + nodeAmountTST(root->right);
}
