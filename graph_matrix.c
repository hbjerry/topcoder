#include <stdio.h>
#include <malloc.h>
#include "graph.h"

#ifdef GRAPH_MATRIX

Edge EDGE(int V, int W)
{
  Edge a;
  a.v = V; a.w = W;
  return a;
}

int **MATRIXinit(int r, int c, int val)
{
	int i,j;
	int **t = malloc(r * sizeof(int *));
	for(i = 0; i < r ; i++)
		t[i] = malloc(sizeof(int) * c);
	for(i = 0; i < r; i++)
		for (j = 0; j < c; j++) {
			/* code */
			t[i][j] = val;
		}
	return t;
}

Graph GRAPHInit(int V)
{
	Graph G = malloc(sizeof(*G));
	G->V = V; G->E = 0;
	G->adj = MATRIXinit(V,V,0);
	return G;
}

void GRAPHInsertE(Graph G, Edge e)
{
	int v = e.v , w = e.w;
	if(G->adj[v][w] == 0) G->E++;
	G->adj[v][w] = 1;
	G->adj[w][v] = 1;
}

void GRAPHRemoveE(Graph G, Edge e)
{
	int v = e.v , w = e.w;
	if(G->adj[v][w] == 1) G->E--;
	G->adj[v][w] = 0;
	G->adj[w][v] = 0;
}

int GRAPHedges(Edge a[], Graph G)
{
	int v, w , E = 0;
	for(v = 0; v < G->V; v++)
		for(w = v+1; w < G->V; w++)
			if(G->adj[v][w] == 1)
				a[E++] = EDGE(v,w);
	return E;
}

void GRAPHshow(Graph G)
{
	int i, j;
	printf("%d vertices, %d edges\n", G->V, G->E);
	for (i = 0; i < G->V; i++) {
		printf("%2d:\n",i);
		for (j = 0; j < G->V; j++) {
			if(G->adj[i][j] == 1) printf(" %2d", j);
		}
		printf("\n");
	}
}

int cnt = 0;
int pre[MAX_V];
void GRAPHdfs(Graph G, Edge e)
{
	int t, w = e.w;
	pre[w] = ++cnt;
	printf("visit %d\n",w);
	for( t = 0; t < G->V; t++)
	{
		if (G->adj[w][t] == 1 && pre[t] == 0)
		{
			GRAPHdfs(G,EDGE(w,t));
		}
	}
}

#endif // GRAPH_MATRIX