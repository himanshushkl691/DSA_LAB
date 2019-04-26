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
    else if (b == -INF && (a != INF && a != -INF))
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
//gRAPH aLGORITHM
int BellmanFordNegativeDetect(struct vector **graph,int src,int V)
{
    int *dist = (int *)malloc(sizeof(int) * V);
    for(int i = 0;i<V;i++)
        dist[i] = INF;
    dist[src] = 0;
    for(int i = 0;i<V - 1;i++)
    {
        for(int j = 0;j<V;j++)
        {
            if(graph[j]->size)
            {
                for(int k = 0;k<graph[j]->size;k++)
                {
                    int v = graph[j]->arr[k]->y;
                    int w = graph[j]->arr[k]->z;
                    if(add(dist[j],w) < dist[v])
                        dist[v] = add(dist[j],w);
                }
            }
        }
    }
    for(int j = 0;j<V;j++)
    {
        if(graph[j]->size)
        {
            for(int k = 0;k<graph[j]->size;k++)
            {
                int v = graph[j]->arr[k]->y;
                int w = graph[j]->arr[k]->z;
                if(add(dist[j],w) < dist[v])
                    return 1;
            }
        }
    }
    return -1;
}
//gRAPH aLGORITHM

int main()
{
    int n,m;
    struct vector **graph;
    graph = (struct vector **)malloc(sizeof(struct vector *) * n);
    for(int i = 0;i<n;i++)
        graph[i] = init_vector();
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
    fscanf(fs,"%d %d",&n,&m);
    for(int i = 0;i < m;i++)
    {
	    int u,v,w;
	    fscanf(fs,"%d %d %d",&u,&v,&w);
	    graph[u] = push_back(graph[u],make_pair(u,v,w));
    }
    fprintf(ft,"%d\n",BellmanFordNegativeDetect(graph,0,n));
    return 0;
}
