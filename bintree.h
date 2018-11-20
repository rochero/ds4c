#include <stdio.h>
#include <stdlib.h>
#define END_FLAG 0

#ifndef BT_TYPE
#define BT_TYPE
typedef int bt_type;
#endif

#ifndef BINTREE
#define BINTREE
typedef struct _bt
{
    bt_type data;
    struct _bt *left, *right;
} BTNode, *BinTree;
#endif

#ifndef AVLTREE
#define AVLTREE
typedef struct _avl
{
    bt_type data;
    struct _avl *left, *right;
    int height;
} AVLNode, *AVL;
#endif

#ifndef TREE_TYPE
#define TREE_TYPE
typedef AVL tree_type;
#endif

BinTree BuildBinTree(BinTree T);
BinTree BuildBinTree1(BinTree T, bt_type preOrder[], int preL,
                      bt_type inOrder[], int inL, int n);
BinTree BuildBinTree2(BinTree T, bt_type postOrder[], int postL,
                      bt_type inOrder[], int inL, int n);
void PostOrderTraversal(BinTree T);
#include "stack.h"
void PostOrderTraversal1(BinTree T, Stack S);
void LevelOrderTraversal(BinTree T);
int GetHeightOfBinTree(tree_type T); //BinTree, AVL
void FindAncestor(BinTree T, Stack S, bt_type key);

// Binary Search Tree Operation
BinTree InsertToBST(BinTree BST, bt_type data);
BinTree DeleteBST(BinTree BST, bt_type data);
BTNode* FindBST(BinTree BST, bt_type data);
BTNode* FindMinOfBST(BinTree BST);
BTNode* FindMaxOfBST(BinTree BST);

// AVL Tree Operation
AVL InsertToAVL(AVL T, bt_type data);
AVL SingleLeftRotateAVL(AVL T);
AVL SingleRightRotateAVL(AVL T);
AVL DoubleLeftRightRotateAVL(AVL T);
AVL DoubleRightLeftRotateAVL(AVL T);
