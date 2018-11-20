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
#endif // BINTREE
typedef BTNode* s_type;
#ifndef STACK
#define STACK
typedef struct _s
{
    s_type *stack;
    int top;
    int max;
}*Stack;
#endif
Stack InitStack(const int max);
int EmptyOfStack(Stack S);
int FullOfStack(Stack S);
int PushToStack(Stack S, s_type data);
void PopOfStack(Stack S);
s_type* TopOfStack(Stack S);

