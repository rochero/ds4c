#include "huffman.h"
#include "stdlib.h"
HuffmanTree BuildHuffmanTree(Heap H)
{
    int i, size = H->size;
    HuffmanTree T;
    for (i = 1; i < size; ++i)
	{
		T = (HuffmanTree)malloc(sizeof(struct _huf));
		T->data = 0;
		T->left = DeleteMinOfMinHeap(H);
		T->right = DeleteMinOfMinHeap(H);
		T->weight = T->left->weight + T->right->weight;
		InsertToMinHeap(H, T);
	}
	T = DeleteMinOfMinHeap(H);
	return T;
}

