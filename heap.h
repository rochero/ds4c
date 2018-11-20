
#ifndef H_DATA_TYPE
#define H_DATA_TYPE
typedef int h_data_type;
#endif

#ifdef H_DATA_TYPE
typedef struct _h_node
{
	h_data_type data;
	int weight;
} *h_type;
#endif

#ifndef HEAP
#define HEAP
typedef struct _h
{
    h_type* heap;
    int size;
    int max;
} *Heap;
#endif

#define SENTRY 1024

Heap BuildHeap(const int max);
int FullOfHeap(Heap H);
int EmptyOfHeap(Heap H);
void InsertToMaxHeap(Heap H, h_type node);
void InsertToMinHeap(Heap H, h_type node);
h_type DeleteMaxOfMaxHeap(Heap H);
h_type DeleteMinOfMinHeap(Heap H);
void DestroyMaxHeap(Heap H);
void DestroyMinHeap(Heap H);
