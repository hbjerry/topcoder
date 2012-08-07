#include "stackqueue.h"

SQItem SQITEM(int k)
{
	SQItem a;
	a.key = k;
	return a;
}

SQ SQinit(int max)
{
	SQ p_sq = (SQ)malloc(sizeof(*p_sq));
	p_sq->max = max;
	p_sq->n = 0;
	p_sq->head = (SQItem*)malloc((max+1)*sizeof(SQItem));
	return p_sq;
}
int SQempty(SQ p_sq)
{
	return p_sq->n == 0;
}
void SQpush(SQ p_sq,SQItem item)
{
	if (p_sq->n == p_sq->max)
	{
		return;
	}
	p_sq->head[p_sq->n++] = item;
}

SQItem SQpop(SQ p_sq)
{
#ifdef STACK
	return p_sq->head[--p_sq->n];
#else
	int i;
	SQItem a = p_sq->head[0];
	p_sq->n--;
	for ( i = 0; i < p_sq->n; i++ )
	{
		p_sq->head[i] = p_sq->head[i+1];
	}
	return a;
#endif
	
}


void SQshow(SQ p_sq)
{
	int i;
	for ( i = 1; i <= p_sq->n; i++)
	{
		printf(" %d(%f)",p_sq->head[i].key);
	}
	printf("\n");
}
