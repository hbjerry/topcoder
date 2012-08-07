#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "stackqueue.h"

int randV(Graph G)
{
	return G->V * (rand()/(RAND_MAX + 1.0));
}

Graph GRAPHrand(int V, int E)
{
	Graph G = GRAPHInit(V);
	while( G->E < E)
	{
		GRAPHInsertE(G,EDGE(randV(G), randV(G), 0,0));
	}

	return G;
}


static int visited[MAX_V];
#define  true 1
#define  false 0

// find one path from v to w
/*int GRAPHpath(Graph G, int v, int w)
{
	int i = 0;
	link p;
	if (v == w)
	{
		return true;
	}
	visited[v] = 1;
	p = G->adj[v];
	while(p != NULL)
	{
		if (visited[p->v] != 1)
		{
			if(GRAPHpath(G,p->v,w))
			{
				printf("path from %d--->%d\n",v,p->v);
				return true;
			}
		}
		p = p->next;
	}
	return false;
}*/

Graph GRAPHfix(int V, int E)
{
	Graph G = GRAPHInit(6);
	GRAPHInsertE(G,EDGE(0, 1, 2, 0));
	GRAPHInsertE(G,EDGE(0, 2, 3, 0));
	GRAPHInsertE(G,EDGE(1, 3, 3, 0));
	GRAPHInsertE(G,EDGE(1, 4, 1, 0));
	GRAPHInsertE(G,EDGE(2, 3, 1, 0));
	GRAPHInsertE(G,EDGE(2, 4, 1, 0));
	GRAPHInsertE(G,EDGE(3, 5, 2, 0));
	GRAPHInsertE(G,EDGE(4, 5, 3, 0));

	//GRAPHInsertE(G,EDGE(0, 6, 51));
	//GRAPHInsertE(G,EDGE(0, 1, 32));
	//GRAPHInsertE(G,EDGE(0, 2, 29));
	//GRAPHInsertE(G,EDGE(4, 3, 34));
	//GRAPHInsertE(G,EDGE(5, 3, 18));
	//GRAPHInsertE(G,EDGE(7, 4, 45));
	//GRAPHInsertE(G,EDGE(5, 4, 40));
	//GRAPHInsertE(G,EDGE(0, 5, 60));
	//GRAPHInsertE(G,EDGE(6, 4, 51));
	//GRAPHInsertE(G,EDGE(7, 0, 31));
	//GRAPHInsertE(G,EDGE(7, 6, 25));
	//GRAPHInsertE(G,EDGE(7, 1, 21));

	return G;
}
int main(int argc, const char *argv[])
{
	int V = atoi(argv[1]);
	int E = atoi(argv[2]);
	int st[MAX_V];
	int wt[MAX_V];
	SQ sq;
	int i;
	//Graph G = GRAPHrand(V,E);
	Graph G = GRAPHfix(V,E);
	if(V < 20)
		GRAPHshowflow(G);
	else
		printf("%d vectices, %d edges\n", V, E);

	sq = SQinit(V);
	for ( i = 0; i < V; i ++)
	{
		SQpush(sq,SQITEM(i));
	}
	for ( i = 0; i < V; i ++)
	{
		printf("%d\n", SQpop(sq).key);
	}

	
	//GRAPHdfs(G,EDGE(0,0,0));
	//printf("path: %d\n",GRAPHpath(G,0,V-1));

	/*GRAPHspAll(G);*/
	/*GRAPHpfs(G, 0, st, wt);
	for ( i = 0 ; i < G->V; i++)
	{
		printf(" %d(%f) ", st[i],wt[i]);
	}
	printf("\n");
	GRAPHford(G, 0, st, wt);
	for ( i = 0 ; i < G->V; i++)
	{
		printf(" %d(%f) ", st[i],wt[i]);
	}*/

	GRAPHmaxflow(G,0,5);
	GRAPHshowflow(G);
	return 0;
}
