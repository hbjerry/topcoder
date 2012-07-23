#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int randV(Graph G)
{
	return G->V * (rand()/(RAND_MAX + 1.0));
}

Graph GRAPHrand(int V, int E)
{
	Graph G = GRAPHInit(V);
	while( G->E < E)
	{
		GRAPHInsertE(G,EDGE(randV(G), randV(G), 0));
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
	GRAPHInsertE(G,EDGE(0, 1, 41));
	GRAPHInsertE(G,EDGE(1, 2, 51));
	GRAPHInsertE(G,EDGE(2, 3, 50));
	GRAPHInsertE(G,EDGE(4, 3, 36));
	GRAPHInsertE(G,EDGE(3, 5, 38));
	GRAPHInsertE(G,EDGE(3, 0, 45));
	GRAPHInsertE(G,EDGE(0, 5, 29));
	GRAPHInsertE(G,EDGE(5, 4, 21));
	GRAPHInsertE(G,EDGE(1, 4, 32));
	GRAPHInsertE(G,EDGE(4, 2, 32));
	GRAPHInsertE(G,EDGE(5, 1, 29));

	return G;
}
int main(int argc, const char *argv[])
{
	int V = atoi(argv[1]);
	int E = atoi(argv[2]);
	int st[MAX_V];
	double wt[MAX_V];
	int i;
	//Graph G = GRAPHrand(V,E);
	Graph G = GRAPHfix(V,E);
	if(V < 20)
		GRAPHshow(G);
	else
		printf("%d vectices, %d edges\n", V, E);
	
	GRAPHdfs(G,EDGE(0,0,0));
	//printf("path: %d\n",GRAPHpath(G,0,V-1));

	GRAPHpfs(G, 0, st, wt);
	for ( i = 0 ; i < 6; i++)
	{
		printf(" %d(%f)", st[i],wt[i]);
	}
	return 0;
}
