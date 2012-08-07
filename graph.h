typedef struct { int v; int w ; int wt; int flow;} Edge;
Edge EDGE(int V, int W, int, int);
#ifdef GRAPH_MATRIX
struct graph { int V; int E; int **adj;};
#else
typedef struct node *link;
struct node{ int v; int wt;int flow;link next;link dup;};
struct graph { int V; int E;link *adj;};
#endif

//maxmium vertices num
#define MAX_V 100

// maxmium weight s
#define MAXWT 10000

typedef struct graph *Graph;
Graph GRAPHInit(int);
void GRAPHInsertE(Graph, Edge);
void GRAPHRemoveE(Graph, Edge);
int GRAPHedges(Edge[], Graph G);
Graph GRAPHcopy(Graph);
void GRAPHdestroy(Graph);
void GRAPHshow(Graph);

Graph GRAPHrand(int V, int E);

void GRAPHdfs(Graph G, Edge e);