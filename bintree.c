#include "bintree.h"
BinTree BuildBinTree(BinTree T)
{
    bt_type data;
    scanf("%d", &data);
    if (data == END_FLAG)
        return NULL;
    T = (BTNode*)malloc(sizeof(BTNode));
    T->data = data;
    T->left = BuildBinTree(T->left);
    T->right = BuildBinTree(T->right);
    return T;
}


// Build by Preorder and Inorder Sequence(data must be unique)
BinTree BuildBinTree1(BinTree T, bt_type preOrder[], int preL,
                      bt_type inOrder[], int inL, int n)
{
    if (n == 0)
        return NULL;
    T = (BinTree)malloc(sizeof(BTNode));
    int i;
    for (i = 0; i < n && inOrder[inL + i] != preOrder[preL]; ++i);
    // if (n == i) printf("ERROR:Invalid Sequence\n");
    int numL = i, numR = n - i - 1;
    T->data = preOrder[preL];
    T->left = BuildBinTree1(T->left, preOrder, preL + 1, inOrder, inL, numL);
    T->right = BuildBinTree1(T->right, preOrder, preL + numL + 1, inOrder, inL + numL + 1, numR);
    return T;
}

void PostOrderTraversal(BinTree T)
{
    if (T != NULL)
    {
        PostOrderTraversal(T->left);
        PostOrderTraversal(T->right);
        printf("%d ", T->data);
    }
}
#include "stack.h"
void PostOrderTraversal1(BinTree T, Stack S)
{
    BinTree pre = NULL;
    while (T != NULL || !EmptyOfStack(S))
    {
        while (T != NULL)
        {
            PushToStack(S, T);
            T = T->left;
        }
        if (!EmptyOfStack(S))
        {
            T = *TopOfStack(S);
            if (T->right != NULL && T->right != pre)
                T = T->right;
            else
            {
                printf("%d ", T->data);
                PopOfStack(S);
                pre = T;
                T = NULL;
            }
        }
    }
}

void LevelOrderTraversal(BinTree T)
{
    if (T == NULL)
        return;
    BTNode* Q[100];
    int front, rear, i;
    for (front = 0, rear = 0, Q[0] = T; front <= rear; ++front)
    {
        if (Q[front]->left != NULL)
            Q[++rear] = Q[front]->left;
        if (Q[front]->right != NULL)
            Q[++rear] = Q[front]->right;
    }
    for (i = 0; i <= rear; ++i)
        printf("%d%c", Q[i]->data, i != rear ? ' ' : '\n');
}

int GetHeightOfBinTree(tree_type T)
{
    int hL, hR;
    if (T != NULL)
    {
        hL = GetHeightOfBinTree(T->left);
        hR = GetHeightOfBinTree(T->right);
        return (hL > hR ? hL : hR) + 1;
    }
    return 0;
}

void FindAncestor(BinTree T, Stack S, bt_type key)
{
    BTNode* pre = NULL;
    while (T != NULL || !EmptyOfStack(S))
    {
        while (T != NULL)
        {
            PushToStack(S, T);
            T = T->left;
        }
        if (!EmptyOfStack(S))
        {
            T = *TopOfStack(S);
            if (T->right && T->right != pre)
                T = T->right;
            else
            {
                PopOfStack(S);
                if (T->data == key)
                    return;
                pre = T;
                T = NULL;
            }
        }
    }
}

// Binary Search Tree

BinTree InsertToBST(BinTree BST, bt_type data)
{
    if (BST == NULL)
    {
        BTNode* p = (BTNode*)malloc(sizeof(BTNode));
        p->data = data;
        p->left = p->right = NULL;
        BST = p;
    }
    else if (data < BST->data)
        BST->left = InsertToBST(BST->left, data);
    else
        BST->right = InsertToBST(BST->right, data);
    return BST;
}

BTNode* FindOfBST(BinTree BST, bt_type data)
{
    while (BST != NULL)
    {
        if( data < BST->data)
            BST = BST->left;
        else if( data > BST->data )
            BST = BST->right;
        else
            return BST;
    }
    return NULL;
}

BTNode* FindMinOfBST(BinTree BST)
{
    if (BST != NULL)
        while (BST->left != NULL)
            BST = BST->left;
    return BST;
}

BTNode* FindMaxOfBST(BinTree BST)
{
    if (BST != NULL)
        while (BST->right != NULL)
            BST = BST->right;
    return BST;
}
BinTree DeleteOfBST(BinTree BST, bt_type data)
{
    BTNode* tmp;
    if (BST == NULL)
        printf("Not Found\n");
    else if (data < BST->data)
        BST->left = DeleteOfBST(BST->left, data);
    else if (data > BST->data)
        BST->right = DeleteOfBST(BST->right, data);
    else if (BST->left != NULL && BST->right != NULL)
    {
        tmp = FindMinOfBST(BST->right);
        BST->data = tmp->data;
        BST->right = DeleteOfBST(BST->right, BST->data);
    }
    else
    {
        tmp = BST;
        if(BST->left == NULL)
            BST = BST->right;
        else if(BST->right == NULL)
            BST = BST->left;
        free(tmp);
    }
    return BST;
}

// AVL Tree

AVL InsertToAVL(AVL T, bt_type data)
{
    if (T == NULL)
    {
        T = (AVLNode*)malloc(sizeof(AVLNode));
        T->data = data;
        T->left = T->right = NULL;
        T->height = 0;
    }
    else if (data < T->data)
    {
        T->left = InsertToAVL(T->left, data);
        if ((GetHeightOfBinTree(T->left) - GetHeightOfBinTree(T->right)) == 2)
        {
            if (data < T->left->data)
                T = SingleLeftRotateAVL(T);
            else
                T = DoubleLeftRightRotateAVL(T);
        }
    }
    else if (data > T->data)
    {
        T->right = InsertToAVL(T->right, data);
        if ((GetHeightOfBinTree(T->right) - GetHeightOfBinTree(T->left)) == 2)
        {
            if (data > T->right->data)
                T = SingleRightRotateAVL(T);
            else
                T = DoubleRightLeftRotateAVL(T);
        }
    }
    return T;
}

AVL SingleLeftRotateAVL(AVL T)
{
    int t;
    AVLNode* p = T->left;
    T->left = p->right;
    p->right = T;
    T->height = GetHeightOfBinTree(T);
    p->height = ((t = GetHeightOfBinTree(p->left)) > T->height ? t : T->height) + 1;
    return p;
}

AVL SingleRightRotateAVL(AVL T)
{
    int t;
    AVLNode* p = T->right;
    T->right = p->left;
    p->left = T;
    T->height = GetHeightOfBinTree(T);
    p->height = ((t = GetHeightOfBinTree(p->right)) > T->height ? t : T->height) + 1;
    return p;
}

AVL DoubleLeftRightRotateAVL(AVL T)
{
    T->left = SingleRightRotateAVL(T->left);
    return SingleLeftRotateAVL(T);
}

AVL DoubleRightLeftRotateAVL(AVL T)
{
    T->right = SingleLeftRotateAVL(T->right);
    return SingleRightRotateAVL(T);
}

// Heap

