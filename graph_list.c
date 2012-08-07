#include <stdio.h>
#include <malloc.h>
#include "graph.h"
#include "pq.h"
#include "stackqueue.h"

#ifndef GRAPH_MATRIX

Edge EDGE(int V, int W, int wt, int flow)
{
	Edge a;
	a.v = V; a.w = W; a.wt = wt; a.flow = flow;
	return a;
}

link NEW(int v, link next,int wt, int flow)
{
  link x = malloc(sizeof(*x));
  x->v = v;
  x->next = next;
  x->wt = wt;
  x->flow = flow;
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
	int wt = e.wt;
	int flow = e.flow;
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
		G->adj[v] = NEW(w, G->adj[v],wt,flow);
		
#ifndef DAG
		G->adj[w] = NEW(v, G->adj[w],-wt,-flow);
#endif
		G->adj[v]->dup = G->adj[w];
		G->adj[w]->dup = G->adj[v];
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
			GRAPHdfs(G,EDGE(w,p->v,0, 0));
		}
		p = p->next;
	}
}

// SPT Dijkstra
#define P (wt[v] + t->wt)

// MST Prim 
//#define P (t->wt)
void GRAPHpfs(Graph G, int s, int st[], int wt[])
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
	while (!PQempty(p_pq))
	{
		if (wt[v = PQdel(p_pq).key] != MAXWT)
		{
			//printf("%d(%f) pop!",v,wt[v]);
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

// bellan-ford
void GRAPHford(Graph G, int s, int st[], int wt[])
{
	int i;
	int v, w; link t;
	Item item;
	for (v = 0; v < G->V ; v++)
	{
		st[v] = -1;
		wt[v] = MAXWT;
	}
	st[s] = s;
	wt[s] = 0;
	for (i = 0; i < G->V; i++)
	{
		for ( v = 0; v < G->V ; v++)
		{
			if (wt[v] != MAXWT)  
			{
				for ( t = G->adj[v]; t != NULL ;t = t->next)
				{
					if ( wt[t->v] > wt[v] + t->wt)
					{
						wt[t->v] = wt[v] + t->wt;
						st[t->v] = t->v;
					}
				}
			}
		}
	}
}

#define Q (p->wt < 0 ? -p->flow : p->wt - p->flow)
void GRAPHdfs1(Graph G, int s, int t, link st[MAX_V])
{
	link p;
	int q;
	if (s == t)
	{
		return;
	}
	for( p = G->adj[s]; p != NULL; p = p->next)
	{
		q = p->wt < 0 ? -p->flow : p->wt - p->flow;
		if( Q > 0 && st[p->v] == NULL)
		{
			st[p->v] = p;
			GRAPHdfs1(G,p->v,t,st);
		}
	}
}

void GRAPHbfs1(Graph G, int s, int t, link st[MAX_V])
{
	link p;
	link fw[MAX_V];
	int q,i;
	int qq;
	SQ sq = SQinit(G->V)

	for ( i = 0; i < G->V; i++)
	{
		fw[i] = NULL;
	}
	SQpush(sq,SQITEM(s));
	fw[s] = NULL;
	while (!SQempty(sq))
	{
		q = SQpop(sq).key;
		st[q] = fw[q];
		for ( p = G->adj[q]; p != NULL; p = p->next)
		{
			qq = p->wt < 0 ? -p->flow : p->wt - p->flow;
			if ( Q > 0 && fw[p->v] == NULL)
			{
				SQpush(sq,SQITEM(p->v));
				fw[p->v] = p;
			}
		}
	}
}

int GRAPHfs(Graph G, int s, int t, link st[])
{
	int i;
	int d = MAXWT;
	link p;
	int q;
	for ( i = 0; i < G->V; i++ )
	{
		st[i] = NULL;
	}

	GRAPHbfs1(G,s,t,st);
	if (st[t] == NULL)
	{
		return 0;
	}

	for ( i = t; i != s && st[i] != NULL; i = st[i]->dup->v)
	{
		p = st[i];
		q = p->wt < 0 ? -p->flow : p->wt - p->flow;
		d = ( Q > d? d: Q);
	}
	return d;
}

void GRAPHmaxflow(Graph G, int s, int t)
{
	int d;
	link st[MAX_V];
	int x;
	while (( d = GRAPHfs(G,s,t,st)) > 0)
	{
		for (x = t; x != s; x=st[x]->dup->v)
		{
			st[x]->flow += d;
			st[x]->dup->flow -= d;
			printf("%d--%d, flow add: %d\n", st[x]->v, st[x]->dup->v,d);
		}
	}
}

void GRAPHshowflow(Graph G)
{
	int i, j;
	link point;
	printf("%d vertices, %d edges\n", G->V, G->E);
	for (i = 0; i < G->V; i++) {
		printf("%2d:\n",i);
		point = G->adj[i];
		while(point != NULL)
		{
			printf("%d-%d cap:%d, flow:%d  ",i, point->v,point->wt,point->flow);
			point = point->next;
		}
		printf("\n");
	}
}

#endif