#include <stdio.h>
#include <graph.h>

int main(int argc, const char *argv[])
{
	int V = atoi(argv[1]);
	int E = atoi(argv[2]);
	Graph G = GRAPHrand(V,E);
	if(V < 20)
		GRAPHshow(G);
	else
		printf("%d vectices, %d edges, ", V, E);
	return 0;
}
