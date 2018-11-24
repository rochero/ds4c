typedef int q_type;
typedef struct _q
{
	q_type data;
	struct _q* next;
} QNode, *Queue;

Queue MakeEmptyQueue(void);
int EmptyOfQueue(Queue Q);
void EnQueue(Queue Q, q_type data);
QNode* DeQueue(Queue Q);
