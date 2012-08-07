#include <stdio.h>
#include <malloc.h>
#include "graph.h"

#ifdef GRAPH_MATRIX

Edge EDGE(int V, int W , int wt)
{
  Edge a;
  a.v = V; a.w = W; a.wt = wt;
  return a;
}

int **MATRIXint(int r, int c, int val)
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
	G->adj[v][w] = e.wt;
#ifndef DAG
	G->adj[w][v] = e.wt;
#endif
}

void GRAPHRemoveE(Graph G, Edge e)
{
	int v = e.v , w = e.w;
	if(G->adj[v][w] == 1) G->E--;
	G->adj[v][w] = 0;
#ifndef DAG
	G->adj[w][v] = 0;
#endif
}

int GRAPHedges(Edge a[], Graph G)
{
	int v, w , E = 0;
	for(v = 0; v < G->V; v++)
		for(w = v+1; w < G->V; w++)
			if(G->adj[v][w] > 0)
				a[E++] = EDGE(v,w,G->adj[v][w]);
	return E;
}

void GRAPHshow(Graph G)
{
	int i, j;
	printf("%d vertices, %d edges\n", G->V, G->E);
	for (i = 0; i < G->V; i++) {
		printf("%2d:\n",i);
		for (j = 0; j < G->V; j++) {
			if(G->adj[i][j] > 0 ) printf(" %2d", j);
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
		if (G->adj[w][t] > 0 && pre[t] == 0)
		{
			GRAPHdfs(G,EDGE(w,t,G->adj[w][t]));
		}
	}
}


void GRAPHmstV(Graph G, int st[], int wt[])
{
	int fr[MAX_V]; // the nearest neigbout of tree vertex and  nontree vertex
	int i ,v ,w , min;
	for (i = 0 ;i < G->V; i++)
	{
		st[i] = -1;
		fr[i] = i;
		wt[i] = MAXWT;
	}
	st[0] = 0; wt[G->V] = MAXWT;
	for (min = 0; min != G->V ;)
	{
		v = min;
		st[min] = fr[min]; // if the vertex is min, then we get the st[min]
		// reset min to G->V  to find out the next min
		for (w = 0 ,min = G->V; w < G->V; w++)
		{
			if ( st[w] == -1)
			{
				if (G->adj[v][w] > 0 && G->adj[v][w] < wt[w])
				{
					wt[w] = G->adj[v][w];
					fr[w] = v;	
				}
				if ( wt[w] < wt[min])
				{
					min = w;
				}
			}
		}
	}
}

void GRAPHspAll(Graph G)
{
	int i, s, t;
	int **d = MATRIXint(G->V,G->V,MAXWT);
	int **st = MATRIXinit(G->V,G->V,G->V);
	for ( i = 0; i < G->V ; i++)
	{
		for ( s = 0; s < G->V; s++)
		{
			if ( G->adj[i][s] > 0) // no init 
			{
				d[i][s] = G->adj[i][s];
				st[i][s] = s;
			}
		}
		d[i][i] = 0;
		st[i][i] = i;
	}

	for (i = 0 ; i < G->V ;i ++)
	{
		for (s = 0; s < G->V ; s++)
		{
			if (d[i][s] < MAXWT)
			{
				for(t = 0 ; t < G->V; t++)
				{
					if (d[t][s] > d[t][i] + d[i][s] )
					{
						d[t][s] = d[t][i] + d[i][s];
						st[t][s] = st[t][i];
					}
				}
			}
		}
	}

	for ( i = 0; i < G->V ; i++)
	{
		for ( s = 0; s < G->V; s++)
		{
			printf(" %.0f(%d)",d[i][s],st[i][s]);
		}
		printf("\n");
	}
}

#endif // GRAPH_MATRIX