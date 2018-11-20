#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
Heap BuildHeap(const int max)
{
    Heap H = (Heap)malloc(sizeof(struct _h));
    H->heap = (h_type*)malloc((max + 1) * sizeof(h_type));
    H->heap[0] = (h_type)malloc(sizeof(struct _h_node));
    H->size = 0;
    H->max = max;
    H->heap[0]->weight = SENTRY;
    return H;
}

int FullOfHeap(Heap H)
{
    if (H->size == H->max)
        return 1;
    return 0;
}

int EmptyOfHeap(Heap H)
{
    if (H->size == 0)
        return 1;
    return 0;
}
void InsertToMaxHeap(Heap H, struct _h_node node)
{
    if (!FullOfHeap(H))
    {
        h_type pNewNode = (h_type)malloc(sizeof(struct _h_node));
        int i;
        for (i = ++H->size; H->heap[i / 2]->weight < pNewNode->weight; i /= 2)
            H->heap[i] = H->heap[i / 2];
        H->heap[i] = pNewNode;
        return;
    }
    printf("ERROR: MaxHeap Is Full\n");
}

void InsertToMinHeap(Heap H, struct _h_node node)
{
    if (!FullOfHeap(H))
    {
        h_type pNewNode = (h_type)malloc(sizeof(struct _h_node));
        int i;
        for (i = ++H->size; H->heap[i / 2]->weight > pNewNode->weight; i /= 2)
            H->heap[i] = H->heap[i / 2];
        H->heap[i] = pNewNode;
        return;
    }
    printf("ERROR: MinHeap Is Full\n");
}

h_type DeleteMaxOfMaxHeap(Heap H)
{
    if (!EmptyOfHeap(H))
    {
        int parent, child;
        h_type max = H->heap[1];
        h_type tmp = H->heap[H->size--];
        for(parent = 1; parent * 2 <= H->size; parent = child)
        {
            child = parent * 2
                    if((child != H->size) && (H->heap[child]->weight < H->heap[child + 1]->weight))
                        ++child;
            if(tmp->weight >= H->heap[child]->weight)
                break;
            else
                H->heap[parent] = H->heap[child];
        }
        H->heap[parent] = tmp;
        return max;
    }
    printf("ERROR: MaxHeap Is Empty\n");
}

h_type DeleteMinOfMinHeap(Heap H)
{
    if (!EmptyOfHeap(H))
    {
        int parent, child;
        h_type min = H->heap[1];
        h_type tmp = H->heap[H->size--];
        for(parent = 1; parent * 2 <= H->size; parent = child)
        {
            child = parent * 2;
            if((child != H->size) && (H->heap[child]->weight > H->heap[child + 1]->weight))
                child++;
            if(tmp->weight <= H->heap[child]->weight)
                break;
            else
                H->heap[parent] = H->heap[child];
        }
        H->heap[parent] = tmp;
        return min;
    }
    printf("ERROR: MinHeap Is Empty\n");
}

void DestroyMaxHeap(Heap H)
{
    while (!EmptyOfHeap(H))
    {
        h_type p = DeleteMaxOfMaxHeap(H);
        free(p);
    }
}
void DestroyMinHeap(Heap H)
{
    while (!EmptyOfHeap(H))
    {
        h_type p = DeleteMinOfMinHeap(H);
        free(p);
    }
}
