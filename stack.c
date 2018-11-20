#include "stack.h"
#include "stdlib.h"
int EmptyOfStack(Stack S)
{
    if (S->top == -1)
        return 1;
    return 0;
}

int FullOfStack(Stack S)
{
    if (S->top + 1 == S->max)
        return 1;
    return 0;
}

int PushToStack(Stack S, s_type data)
{
    if (FullOfStack(S))
        return 0;
	S->stack[++S->top] = data;
	return 1;
}

void PopOfStack(Stack S)
{
	--S->top;
}

s_type* TopOfStack(Stack S)
{
	return &S->stack[S->top];
}

Stack InitStack(const int max)
{
    Stack S = (Stack)malloc(sizeof(Stack));
    S->stack = (s_type*)malloc(sizeof(s_type) * max);
    S->top = -1, S->max = max;
    return S;
}
