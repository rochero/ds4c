#ifndef L_TYPE
#define L_TYPE
typedef int l_type;
#endif

#ifndef LIST
#define LIST
typedef struct _l
{
	l_type data;
	struct _l* next;
} LNode, *List;
#endif

List InitList();
void PushBackToList(List L, l_type data);
void PushFrontToList(List L, l_type data);
int EmptyOfList(List L);
LNode* FindByValueOfList(List L, l_type data);
LNode* FindByIndexOfList(List L, int i);
int DeleteByValueOfList(List L, l_type data);
int DeleteByIndexOfList(List L, int i);
int ValueToIndexOfList(List L, l_type data);
int InsertToList(List L, l_type data, int position);


