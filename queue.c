#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
Queue MakeEmptyQueue()
{
    Queue Q = (QNode*)malloc(sizeof(QNode));
    Q->next = NULL;
    return Q;
}

int EmptyOfQueue(Queue Q)
{
    if (Q->next == NULL)
        return 1;
    return 0;
}

void EnQueue(Queue Q, q_type data)
{
    QNode* p;
    for (p = Q; p->next != NULL; p = p->next);
    p->next = (QNode*)malloc(sizeof(QNode));
    p->next->data = data;
    p->next->next = NULL;
}

QNode* DeQueue(Queue Q)
{
    if (!EmptyOfQueue(Q))
    {
        QNode* p = Q->next;
        Q->next = Q->next->next;
        return p;
    }
    printf("ERROR: Queue Is Empty!\n");
    return NULL;
}
