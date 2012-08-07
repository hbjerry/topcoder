typedef struct { int key; int wt;} Item;
Item ITEM(int , int);
typedef struct pq { Item *head; int n; int max;};
typedef struct pq *PQ;

// compare
// if less, then max heap
// if more, then min heap
int compare(Item a, Item b);
PQ PQinit(int);
int PQempty(PQ);
void PQinsert(PQ,Item);
Item PQdel(PQ);
void PQshow(PQ);
void PQchange(PQ,Item);