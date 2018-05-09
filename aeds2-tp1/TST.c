//
//  TST.c
//  aeds2-tp1
//
//  Created by Gustavo Viegas on 17/04/18.
//  Copyright © 2018 UFV Florestal. All rights reserved.
//

#include "TST.h"

// A utility function to create a new ternary search tree TSTNode
TSTNodePointer createNodeTST(char data)
{
    TSTNodePointer temp = (TSTNodePointer)malloc(sizeof(TSTNode));
    temp->data = data;
    temp->isEndOfString = 0;
    temp->left = temp->eq = temp->right = NULL;
    return temp;
}

// Function to insert a new word in a Ternary Search Tree
void insertNodeTST(TSTNodePointer *root, char *word)
{
    // Base Case: Tree is empty
    if (!(*root))
        *root = createNodeTST(*word);
    // If current character of word is smaller than root's character,
    // then insert this word in left subtree of root
    if ((*word) < (*root)->data)
        insertNodeTST(&((*root)->left), word);
    // If current character of word is greate than root's character,
    // then insert this word in right subtree of root
    else if ((*word) > (*root)->data)
        insertNodeTST(&((*root)->right), word);
    // If current character of word is same as root's character,
    else
    {
        if (*(word + 1))
            insertNodeTST(&((*root)->eq), word + 1);
        else
            // the last character of the word
            (*root)->isEndOfString = 1;
    }
}

// Function to search a given word in TST
int searchTST(TSTNodePointer root, char *word, int *comparisons, int *height) {
    if (!root)
        return 0;
    
    (*height)++;

    if (*word < (root)->data) {
        (*comparisons)++;
        return searchTST(root->left, word, comparisons, height);
    }
    else if (*word > (root)->data) {
        *comparisons += 2;
        return searchTST(root->right, word, comparisons, height);
    }
    else
    {
        if (*(word + 1) == '\0')
            return root->isEndOfString;
        *comparisons += 3;
        return searchTST(root->eq, word + 1, comparisons, height);
    }
}

// A recursive function to traverse Ternary Search Tree
void printTSTSubtree(TSTNodePointer root, char *buffer, int i)
{
    if (root)
    {
        // First traverse the left subtree
        printTSTSubtree(root->left, buffer, i);
        // Store the character of this node
        buffer[i] = root->data;
        if (root->isEndOfString)
        {
            buffer[i + 1] = '\0';
            printf("%s\n", buffer);
        }
        // Traverse the subtree using equal pointer (middle subtree)
        printTSTSubtree(root->eq, buffer, i + 1);
        // Finally Traverse the right subtree
        printTSTSubtree(root->right, buffer, i);
    }
}


// The main function to traverse a Ternary Search Tree.
// It mainly uses traverseTSTUtil()
void printTST(TSTNodePointer root)
{
    char buffer[MAX_SIZE];
    printTSTSubtree(root, buffer, 0);
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int heightTST(TSTNodePointer root)
{
    if (root == NULL)
        return -1;
    int leftHeight = heightTST(root->left);
    int rightHeight = heightTST(root->right);
    int eqHeight = heightTST(root->eq);
    return 1 + max(max(leftHeight, eqHeight), rightHeight);
}

int nodeAmountTST(TSTNodePointer root)
{
    if (root == NULL)
        return 0;
    return 1 + nodeAmountTST(root->left) + nodeAmountTST(root->eq) + nodeAmountTST(root->right);
}

void statsTST(TSTNodePointer root) {
    printf("\t *** Dados da Arvore TST: *** \n");
    printf("Numero de nos TST: %d\n", nodeAmountTST(root));
    printf("Altura da TST: %d\n", greaterWordTST(root));
    printf("\t ********* \n");
}
