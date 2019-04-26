#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define INF 1000000007

int add(int a,int b)
{
    if ((a != INF && a != -INF) && (b != INF && b != -INF))
        return (a + b);
    else if (a == INF && (b != INF && b != -INF))
        return INF;
    else if (a == INF && b == INF)
        return INF;
    else if (a == INF && b == -INF)
        return 0;
    else if (a == -INF && (b != INF && b != -INF))
        return -INF;
    else if (a == -INF && b == INF)
        return 0;
    else if (a == -INF && b == -INF)
        return -INF;
    else if (b == INF && (a != INF && a != -INF))
        return INF;
    else if (b == INF && a == INF)
        return INF;
    else if (b == INF && a == -INF)
        return 0;
    else if (b == -INF && (a != INF && a != -INF))
        return -INF;
    else if (b == -INF && a == INF)
        return 0;
    else if (b == -INF && a == -INF)
        return -INF;
}

struct pair
{
    int x,y,z;
};

struct pair *make_pair(int x,int y,int z)
{
    struct pair *newpair = (struct pair *)malloc(sizeof(struct pair));
    newpair->x = x;
    newpair->y = y;
    newpair->z = z;
    return newpair;
}

void swap(struct pair **a,struct pair **b)
{
    struct pair *tmp = *a;
    *a = *b;
    *b = tmp;
}

//vECTOR dECLARATION
struct vector
{
    struct pair **arr;
    unsigned int size;
    unsigned int capacity;
};

struct vector *init_vector()
{
    struct vector *newvector = (struct vector *)malloc(sizeof(struct vector));
    newvector->arr = (struct pair **)malloc(sizeof(struct pair *) * 0);
    newvector->size = 0;
    newvector->capacity = 2;
    return newvector;
}

struct vector *push_back(struct vector *h,struct pair *item)
{
    if(h->capacity == h->size)
    {
        h->capacity = 2 * h->capacity;
        h->arr = (struct pair **)realloc(h->arr,sizeof(struct pair *) * h->capacity);
        h->arr[h->size++] = item;
    }
    else
        h->arr[h->size++] = item;
    return h;
}
//vECTOR dECLARATION

//dISJOINT sET dECLARATION
int parent[100001];
int rnk[100001];

void MakeSet(int x)
{
    parent[x] = x;
    rnk[x] = 0;
}

int FindSet(int x)
{
    while(x != parent[x])
    {
        parent[x] = parent[parent[x]];
        x = parent[x];
    }
    return x;
}

void Union(int x,int y)
{
    int a = FindSet(x);
    int b = FindSet(y);
    if(a != b)
    {
        if(rnk[a] < rnk[b])
            parent[a] = b;
        else
        {
            parent[b] = a;
            if(rnk[a] == rnk[b])
                rnk[a]++;
        }
    }
}
//dISJOINT sET dECLARATION

//pRIORITY qUEUE
struct pq
{
    struct pair **arr;
    int size;
};

struct pq *init_priorityqueue()
{
    struct pq *newpq = (struct pq *)malloc(sizeof(struct pq));
    newpq->arr = (struct pair **)malloc(sizeof(struct pair *) * 0);
    newpq->size = 0;
    return newpq;
}

int isEmpty(struct pq *h)
{
    return (h->size == 0);
}

void MinHeapify(struct pair **arr,int idx,int n)
{
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
    int mn = idx;
    if(left < n && arr[left]->x < arr[mn]->x)
        mn = left;
    if(right < n && arr[right]->x < arr[mn]->x)
        mn = right;
    if(mn != idx)
    {
        swap(&arr[mn],&arr[idx]);
        MinHeapify(arr,mn,n);
    }
}

struct pq *push(struct pq *h,struct pair *item)
{
    h->size++;
    h->arr = (struct pair **)realloc(h->arr,sizeof(struct pair *) * h->size);
    h->arr[h->size - 1] = item;
    int idx = h->size - 1;
    while(idx > 0 && h->arr[idx]->x < h->arr[idx/2]->x)
    {
        swap(&h->arr[idx],&h->arr[idx/2]);
        idx = idx/2;
    }
    return h;
}

struct pq *extract_min(struct pq *h)
{
    if(isEmpty(h))
        return h;
    h->arr[0] = h->arr[h->size - 1];
    h->size--;
    h->arr = (struct pair **)realloc(h->arr,sizeof(struct pair *) * h->size);
    MinHeapify(h->arr,0,h->size);
    return h;
}

struct pair *top(struct pq *h)
{
    if(isEmpty(h))
        return NULL;
    return (h->arr[0]);
}
//pRIORITY qUEUE

//gRAPH aLGORITHM
struct vector **MST_Kruskal(struct vector **ST,struct vector **graph,int n)
{
    for(int i = 0;i<n;i++)
        MakeSet(i);
    struct pq *heap = init_priorityqueue();
    for(int i = 0;i<n;i++)
    {
        for(int j = 0;j<graph[i]->size;j++)
            heap = push(heap,make_pair(graph[i]->arr[j]->z,graph[i]->arr[j]->x,graph[i]->arr[j]->y));
    }
    while(!isEmpty(heap))
    {
        struct pair *tmp = top(heap);
        heap = extract_min(heap);
        int d = tmp->x;
        int u = tmp->y;
        int v = tmp->z;
        if(FindSet(u) != FindSet(v))
        {
            Union(u,v);
            ST[u] = push_back(ST[u],make_pair(u,v,d));
            ST[v] = push_back(ST[v],make_pair(v,u,d));
        }
    }
    return ST;
}

int visited[100001];

void DFS(struct vector **graph,int src)
{
    visited[src] = 1;
    printf("%d->",src);
    for(int i = 0;i<graph[src]->size;i++)
    {
        if(!visited[graph[src]->arr[i]->y])
        {
            DFS(graph,graph[src]->arr[i]->y);
        }
    }
    printf("\n");
}
//gRAPH aLGORITHM

/////////////////////
///DRIVER FUNCTION///
/////////////////////
int main()
{
	FILE *fs,*ft;
	fs = fopen("input.txt","r");
	if(!fs)
	{
		printf("Could not open input file.\n");
		exit(0);
	}
	ft = fopen("output.txt","w");
	if(!ft)
	{
		printf("Could not open output file.\n");
		fclose(fs);
		exit(0);
	}
	int n;
	fscanf(fs,"%d",&n);
	struct vector **graph;
	graph = (struct vector *)malloc(sizeof(struct vector) * n);
	for(int i = 0;i<n;i++)
		graph[i] = init_vector();
	char c;
	int node = 0;
	c = getc(fs);
	while (node < n && (c = getc(fs)) != EOF)
	{
		while (c != '\n')
		{
			if(c>='0' && c<='9')
			{
				int numb = 0;
				while(c>='0' && c<='9')
				{
					numb = numb * 10 + (c - '0');
					c = getc(fs);
				}
				graph[node] = push_back(graph[node],make_pair(node,numb,1));
			}
			if (c == '\n')
				break;
			c = getc(fs);
		}
		node++;
	}
    node = 0;
	while (node < n && (c = getc(fs)) != EOF)
	{
        int e_idx = 0;
		while (c != '\n')
		{
			if(c>='0' && c<='9')
			{
				int numb = 0;
				while(c>='0' && c<='9')
				{
					numb = numb * 10 + (c - '0');
					c = getc(fs);
				}
				graph[node]->arr[e_idx++]->z = numb;
			}
			if (c == '\n')
				break;
			c = getc(fs);
		}
		node++;
	}
	struct vector **ST;
	ST = (struct vector *)malloc(sizeof(struct vector) * n);
	for(int i = 0;i<n;i++)
		ST[i] = init_vector();
    ST = MST_Kruskal(ST,graph,n);
    int MST_W = 0;
    for(int i = 0;i < n;i++)
    { 
        if(ST[i]->size)
        {
            for(int j = 0;j < ST[i]->size;j++)
                MST_W += ST[i]->arr[j]->z;
        }
    }
    fprintf(ft,"%d\n",MST_W / 2);
    fclose(fs);
    fclose(ft);
    return 0;
}
