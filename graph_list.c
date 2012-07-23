#include <stdio.h>
#include <malloc.h>
#include "graph.h"
#include "pq.h"

#ifndef GRAPH_MATRIX

Edge EDGE(int V, int W, double wt)
{
	Edge a;
	a.v = V; a.w = W; a.wt = wt;
	return a;
}

link NEW(int v, link next,double wt)
{
  link x = malloc(sizeof(*x));
  x->v = v;
  x->next = next;
  x->wt = wt;
  return x;
}

Graph GRAPHInit(int V)
{
	int v;
	Graph G = malloc(sizeof(*G));
	G->V = V; G->E = 0;
	G->adj = malloc(V*sizeof(link));
	for ( v = 0; v < V; v++)
	{
		G->adj[v] = NULL;
	}
	return G;
}

void GRAPHInsertE(Graph G, Edge e)
{
	int v = e.v , w = e.w;
	double wt = e.wt;
	link p = G->adj[v];
	printf("insert %d %d\n",v, w);
	while(p != NULL)
	{
		if (w == p->v)
		{
			break;
		}
		p = p->next;
	}
	if (!p)
	{
		G->adj[v] = NEW(w, G->adj[v],wt);
#ifndef DAG
		G->adj[w] = NEW(v, G->adj[w]);
#endif
		G->E++;
	}
}

void GRAPHshow(Graph G)
{
	int i, j;
	link point;
	printf("%d vertices, %d edges\n", G->V, G->E);
	for (i = 0; i < G->V; i++) {
		printf("%2d:\n",i);
		point = G->adj[i];
		while(point != NULL)
		{
			printf(" %2d", point->v);
			point = point->next;
		}
		printf("\n");
	}
}

int cnt = 0;
int pre[MAX_V];
void GRAPHdfs(Graph G, Edge e)
{
	int t, w = e.w;
	link p;
	pre[w] = ++cnt;
	printf("visit %d\n",w);
	p = G->adj[w];
	while(p != NULL)
	{
		if (pre[p->v] == 0)
		{
			GRAPHdfs(G,EDGE(w,p->v,0.0));
		}
		p = p->next;
	}
}

#define P (wt[v] + t->wt)
void GRAPHpfs(Graph G, int s, int st[], double wt[])
{
	int v, w; link t;
	Item item;
	PQ p_pq = PQinit(G->V);
	for (v = 0; v < G->V ; v++)
	{
		st[v] = -1;
		wt[v] = MAXWT;
		PQinsert(p_pq,ITEM(v,MAXWT));
	}
	wt[s] = 0.0; 
	PQchange(p_pq,ITEM(s,0.0));
	PQshow(p_pq);
	while (!PQempty(p_pq))
	{
		if (wt[v = PQdel(p_pq).key] != MAXWT)
		{
			for ( t = G->adj[v]; t != NULL; t = t->next)
			{
				if ( P < wt[t->v] )
				{
					wt[t->v] = P;
					PQchange(p_pq,ITEM(t->v,wt[t->v]));
					st[t->v] = v;
				}
			}
		}
	}
}

#endif