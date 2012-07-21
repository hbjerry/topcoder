#include <stdio.h>
#include <graph.h>

int randV(Graph G)
{
	return G->V * (rand()/(RAND_MAX + 1));
}

Graph GRAPHrand(int V, int E)
{
	Graph G = GRAPHInit(V, E);
	while( G->E < E)
		GRAPHInsertE(G,EDGE(randV(G), randV(G)));
}

int main(int argc, const char *argv[])
{
	int V = atoi(argv[1]);
	int E = atoi(argv[2]);
	Graph G = GRAPHrand(V,E);
	if(V < 20)
		GRAPHshow(G);
	else
		printf("%d vectices, %d edges, ", V, E);
	printf("%d components(s)\n",GRAPHcc(G));
	return 0;
}
