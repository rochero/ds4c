#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SENTRY 1024 // the sentry of minheap
#define MAX 100     // defalt size of code string
typedef struct _huf
{
	char data;
	char flag;
	double weight;
	struct _huf* parent;
	struct _huf* left;
	struct _huf* right;
} *HuffmanTree;

typedef struct _huf HNode;

typedef struct _h
{
	HNode** heap;
	int size;
	int max;
} *Heap;

typedef struct _code
{
	char data;
	char code[MAX];
	int start;
} Code;

int Read(char *str)
{
	scanf("%s", str);
	return strlen(str)-1;
}
Code* Init(int n)
{
	int i;
	Code* C = (Code*)calloc(n, sizeof(Code));
	for (i = 0; i < n; ++i)
		C[i].start = MAX-1;
	return C;
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

void InsertToMinHeap(Heap H, HNode* node)
{
    if (!FullOfHeap(H))
    {
        int i;
        for (i = ++H->size; i/2 > 0 && H->heap[i / 2]->weight > node->weight; i /= 2)
            H->heap[i] = H->heap[i / 2];
        H->heap[i] = node;
        return;
    }
    printf("ERROR: MinHeap Is Full\n");
}

Heap BuildMinHeap(const int max, char *str)
{
	int i;
    Heap H = (Heap)malloc(sizeof(struct _h));
    H->heap = (HNode**)malloc((max + 1) * sizeof(HNode*));
    H->heap[0] = (HNode*)malloc(sizeof(HNode));
    H->size = 0;
    H->max = max;
    H->heap[0]->weight = SENTRY;
    for (i = 1; i <= max; ++i)
	{
		HNode* newNode = (HNode*)malloc(sizeof(HNode));
		scanf("%lf", &(newNode->weight));
		newNode->data = str[i-1];
		newNode->left = newNode->right = NULL;
		InsertToMinHeap(H, newNode);
	}
    return H;
}

HNode* DeleteMinOfMinHeap(Heap H)
{
    if (!EmptyOfHeap(H))
    {
        int parent, child;
        HNode* min = H->heap[1];
        HNode* tmp = H->heap[H->size--];
        for(parent = 1; parent * 2 <= H->size; parent = child)
        {
        	child = parent*2;
            if((child != H->size) && (H->heap[child]->weight > H->heap[child + 1]->weight))
                ++child;
            if(tmp->weight <= H->heap[child]->weight)
                break;
            else
                H->heap[parent] = H->heap[child];
        }
        H->heap[parent] = tmp;
        return min;
    }
    printf("ERROR: MinHeap Is Empty\n");
    return NULL;
}

HuffmanTree BuildHuffmanTree(Heap H)
{
    int i, n = H->size;
    HuffmanTree T;
    for (i = 1; i < n; ++i)
	{
		T = (HuffmanTree)malloc(sizeof(struct _huf));
		T->data = 0;
		T->left = DeleteMinOfMinHeap(H);
		T->left->flag = '0';
		T->left->parent = T;
		T->right = DeleteMinOfMinHeap(H);
		T->right->flag = '1';
		T->right->parent = T;
		T->weight = T->left->weight + T->right->weight;
		InsertToMinHeap(H, T);
	}
	T = DeleteMinOfMinHeap(H);
	T->parent = NULL;
	return T;
}

HuffmanTree FindNode(HuffmanTree T, char key)
{
	HuffmanTree p = NULL;
	if (T != NULL)
	{
		if (T->data == key)
			return T;
		p = FindNode(T->left, key);
		if (p != NULL)
			return p;
		p = FindNode(T->right, key);
		if (p != NULL)
			return p;
	}
	return NULL;
}

void Encode(Code* C, HuffmanTree T, char *str, int n) //get the huffman code of each object
{
	int i;
	for (i = 0; i < n; ++i)
	{
		C[i].data = str[i];
		HuffmanTree p = FindNode(T, str[i]);
		for (;p->parent != NULL; p = p->parent)
			C[i].code[--C[i].start] = p->flag;
	}
}

void Output(Code *C, int n)
{
	int i;
	for (i = 0; i < n; ++i)
		printf("%c:%s\n", C[i].data, C[i].code + C[i].start);
}
int main()
{
	char str[MAX];
	int n = Read(str);
	Heap H = BuildMinHeap(n, str);
	HuffmanTree T = BuildHuffmanTree(H);
	Code *C = Init(n);
	Encode(C, T, str, n);
	Output(C, n);
	return 0;
}
