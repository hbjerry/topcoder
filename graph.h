typedef struct { int v; int w ;} Edge;
Edge EDGE(int V, int W);

struct graph { int V; int E; int **adj;};
typedef struct graph *Graph;
Graph GRAPHInit(int);
void GRAPHInsertE(Graph, Edge);
void GRAPHRemoveE(Graph, Edge);
int GRAPHedges(Edge[], Graph G);
Graph GRAPHcopy(Graph);
void GRAPHdestroy(Graph);
void GRAPHshow(Graph);

Graph GRAPHrand(int V, int E);
