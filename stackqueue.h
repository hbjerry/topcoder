typedef struct { int key; } SQItem;
SQItem SQITEM(int);
typedef struct sq { SQItem *head; int n; int max;};
typedef struct sq *SQ;

SQ SQinit(int);
int SQempty(SQ);
void SQpush(SQ,SQItem);
SQItem SQpop(SQ);
void SQshow(SQ);