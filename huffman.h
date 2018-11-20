#include "heap.h"
#ifndef HUF_TYPE
#define HUF_TYPE
typedef int huf_type;
#endif

#ifndef HUFFMAN
#define HUFFMAN
typedef struct _huf
{
	int weight;
	huf_type data;
	struct _huf *left, *right;
} *HuffmanTree;
#endif

HuffmanTree BuildHuffmanTree(Heap H);
