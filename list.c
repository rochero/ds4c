#include "list.h"
#include <stdlib.h>
List InitList()
{
    List L = (LNode*)malloc(sizeof(LNode));
    L->next = NULL;
    return L;
}

void PushBackToList(List L, l_type data)
{
    LNode* p;
    for (p = L; p->next != NULL; p = p->next);
    p->next = (LNode*)malloc(sizeof(LNode));
    p->next->data = data;
    p->next->next = NULL;
}

void PushFrontToList(List L, l_type data)
{
    LNode* p = L->next;
    L->next = (LNode*)malloc(sizeof(LNode));
    L->next->data = data;
    L->next->next = p;
}

int EmptyOfList(List L)
{
    if (L->next == NULL)
        return 1;
    return 0;
}

LNode* FindByValueOfList(List L, l_type data)
{
    LNode* p;
    for (p = L->next; p != NULL && p->data != data; p = p->next);
    return p;
}

int ValueToIndexOfList(List L, l_type data)
{
	int i = 0;
	LNode* p;
	for (p = L->next; p != NULL && p->data != data; ++i, p = p->next);
	if (p != NULL)
		return i;
	return 0;
}
LNode* FindByIndexOfList(List L, int i)
{
    LNode* p;
    for (p = L->next; p != NULL && i > 1; --i, p = p->next);
    return p;
}
int DeleteByValueOfList(List L, l_type data)
{
    LNode* pre, *cur;
    for (pre = L, cur = L->next; cur != NULL && cur->data != data; pre = cur, cur = cur->next);
    if (cur != NULL)
    {
        pre->next = cur->next;
        free(cur);
    }
    else
        return 0;
    return 1;
}

int DeleteByIndexOfList(List L, int i)
{
	LNode* pre, *cur;
	for (pre = L, cur = L->next; cur != NULL && i > 1; --i, pre = cur, cur = cur->next);
    if (cur != NULL)
    {
        pre->next = cur->next;
        free(cur);
    }
    else
        return 0;
    return 1;
}

int InsertToList(List L, l_type data, int i)
{
	LNode* pre, *cur;
	for (pre = L, cur = L->next; cur != NULL && i > 1; --i, pre = cur, cur = cur->next);
	if (cur != NULL)
	{
		pre->next = (LNode*)malloc(sizeof(LNode));
		pre->next->data = data;
		pre->next->next = cur;
	}
	else
		return 0;
	return 1;
}
