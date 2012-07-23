#include <stdlib.h>
#include "pq.h"
/*
int main(int argc, const char *argv[])
{
	int max = atoi(argv[1]);
	int max_wt = atoi(argv[2]);
	PQ p_pq = PQinit(max);
	int i ;
	double wt;
	Item item;
	for ( i = 0 ;i < max; i++)
	{
		wt = ((double)max_wt) * (rand()/(RAND_MAX + 1.0));
		item.key = i;
		item.wt = wt;
		PQinsert(p_pq,item);
	}
	PQshow(p_pq);

	PQchange(p_pq,ITEM(5,0));

	PQshow(p_pq);


	for ( i = 0 ; i < max ; i++)
	{
		item = PQdel(p_pq);
		printf(" %d(%f)", item.key,item.wt);
	}

	return 0;
}*/