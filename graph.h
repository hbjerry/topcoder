typedef struct { int v; int w ;} Edge;
Edge EDGE(int, int);


typedef struct graph *Graph;
Graph GRAPHInit(int);
void GRAPHInsertE(Graph, Edge);
void GRAPHRemoveE(Graph, Edge);
int GRAPHedges(Edge[], Graph G);
Graph GRAPHcopy(Graph);
void GRAPHdestroy(Graph);
