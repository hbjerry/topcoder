#include "pq.h"

Item ITEM(int k, double v)
{
	Item a;
	a.key = k; a.wt = v;
	return a;
}

// compare
// if less, then max heap
// if more, then min heap
int compare(Item a, Item b)
{
	// current less, max heap
	return a.wt > b.wt;
}

void exch(PQ p_pq, int i, int j)
{
	Item item = p_pq->head[i];
	p_pq->head[i] = p_pq->head[j];
	p_pq->head[j] = item;
}

void fix_up(PQ p_pq, int n)
{
	while( n > 1 && compare(p_pq->head[n/2],p_pq->head[n]))
	{	
		// child bigger then parant
		exch(p_pq,n/2,n);
		n = n/2;
	}	
}

void fix_down(PQ p_pq, int head, int tail)
{
	int j = 0;
	while (head*2 < tail)
	{
		j = 2 * head;
		if (compare(p_pq->head[j], p_pq->head[j+1]))
		{
			j = j + 1;
		}
		if (compare(p_pq->head[head],p_pq->head[j]))
		{
			exch(p_pq,head, j);
			head = j;
		}
		else
			break;
	}
}

PQ PQinit(int max)
{
	PQ p_pq = (PQ)malloc(sizeof(*p_pq));
	p_pq->max = max;
	p_pq->n = 0;
	p_pq->head = (Item*)malloc((max+1)*sizeof(Item));
	return p_pq;
}
int PQempty(PQ p_pq)
{
	return p_pq->n == 0;
}
void PQinsert(PQ p_pq,Item item)
{
	if (p_pq->n == p_pq->max)
	{
		return;
	}
	p_pq->head[++p_pq->n] = item;
	fix_up(p_pq,p_pq->n);
}

Item PQdel(PQ p_pq)
{
	exch(p_pq,1,p_pq->n);
	fix_down(p_pq,1,p_pq->n-1);
	return p_pq->head[p_pq->n--];
}


void PQshow(PQ p_pq)
{
	int i;
	for ( i = 1; i <= p_pq->n; i++)
	{
		printf(" %d(%f)",p_pq->head[i].key,p_pq->head[i].wt);
	}
	printf("\n");
}

void PQchange(PQ p_pq, Item item)
{
	int i;
	for ( i = 1; i <= p_pq->n; i++)
	{
		if(p_pq->head[i].key == item.key)
		{

			if (compare(p_pq->head[i],item))
			{
				p_pq->head[i] = item;
				fix_up(p_pq,i);
			}
			else
			{
				p_pq->head[i] = item;
				fix_down(p_pq,i,p_pq->n);
			}
		}
	}
}