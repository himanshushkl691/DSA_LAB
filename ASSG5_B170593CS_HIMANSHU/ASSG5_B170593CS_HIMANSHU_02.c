#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define INF 1000000000
#define show(arr,n) for(int i = 0;i<n;i++) printf("%d ",arr[i]);printf("\n");
													////////////////////////
													//////GRAPH UTILITIES///
													////////////////////////
//pAIR dECLARATION
struct pair
{
	int x;
	int y;
};

struct pair * make_pair(int x,int y)
{
	struct pair *n = (struct pair *)malloc(sizeof(struct pair));
	n->x = x;
	n->y = y;
	return n;
}
//pAIR dECLARATION

//eDGE dECLARATION
struct edge
{
	int to;
	int w;
};
struct edge *newEdge(int to,int w)
{
	struct edge *n = (struct edge *)malloc(sizeof(struct edge));
	n->to = to;
	n->w = w;
	return n;
}
//eDGE dECLARATION

//vECTOR dECLARATION
struct vector
{
	struct edge **arr;
	int size;
	int capacity;
};
struct vector* init_v()
{
	struct vector* newnode = (struct vector *)malloc(sizeof(struct vector));
	newnode->arr = (struct edge **)malloc(sizeof(struct edge *) * 0);
	newnode->size = 0;
	newnode->capacity = 2;
	return newnode;
}
struct vector* push_back(struct vector* h,int to,int w)
{
	if (h->size == h->capacity)
	{
		h->capacity = 2 * h->capacity;
		h->arr = (struct edge **)realloc(h->arr,sizeof(struct edge *) * (h->capacity));
		h->arr[h->size++] = newEdge(to,w);
	}
	else
		h->arr[h->size++] = newEdge(to,w);
	return h;
}
//vECTOR dECLARATION

//qUEUE dECLARATION
struct q_node
{
	struct edge *item;
	struct q_node *next;
};
struct queue
{
	int size;
	struct q_node *front,*tail;
};
int empty(struct queue *h)
{
	return (h->size == 0);
}
struct q_node *createNode(int to,int w)
{
	struct q_node *n = (struct q_node *)malloc(sizeof(struct q_node));
	n->item = newEdge(to,w);
	n->next = NULL;
	return n;
}
struct queue *init_q()
{
	struct queue *n = (struct queue *)malloc(sizeof(struct queue));
	n->front = n->tail = NULL;
	n->size = 0;
	return n;
}
struct queue *enqueue(struct queue *h,int to,int w)
{
	struct q_node *n = createNode(to,w);
	if (empty(h))
	{
		h->front = h->tail = n;
		h->size++;
		return h;
	}
	h->tail->next = n;
	h->tail = n;
	h->size++;
	return h;
}
struct queue *dequeue(struct queue *h)
{
	if (!empty(h))
	{
		h->front = h->front->next;
		h->size--;
	}
	return h;
}
//qUEUE dECLARATION

//pRIORITY qUEUE dECLARATION
struct pq
{
	int size;
	struct pair **item;
};
struct pq *init_pq()
{
	struct pq *n = (struct pq *)malloc(sizeof(struct pq));
	n->item = (struct pair **)malloc(sizeof(struct pair *) * 0);
	n->size = 0;
	return n;
}
int isEmpty(struct pq *h)
{
	return (h->size == 0);
}
void swap(struct pair **a,struct pair **b)
{
	struct pair *tmp = *a;
	*a = *b;
	*b = tmp;
}
void MinHeapify(struct pair **arr,int idx,int n)
{
	int left = 2 * idx + 1;
	int right = 2 * idx + 2;
	int mn = idx;
	if (left < n && arr[left]->x < arr[mn]->x)
		mn = left;
	if(right < n && arr[right]->x < arr[mn]->x)
		mn = right;
	if (mn != idx)
	{
		swap(&arr[idx],&arr[mn]);
		MinHeapify(arr,mn,n);
	}
}
struct pq *push_pq(struct pq *h,struct pair *x)
{
	h->size++;
	h->item = (struct pair **)realloc(h->item,sizeof(struct pair *) * h->size);
	h->item[h->size-1] = x;
	int idx = h->size - 1;
	while(idx > 0 && h->item[idx]->x < h->item[idx/2]->x)
	{
		swap(&h->item[idx],&h->item[idx/2]);
		idx = idx/2;
	}
	return h;
}
struct pair *top_pq(struct pq *h)
{
	if(isEmpty(h))
		return NULL;
	return (h->item[0]);
}
struct pq *pop_pq(struct pq *h)
{
	if(isEmpty(h))
		return h;
	h->item[0] = h->item[h->size-1];
	h->size--;
	h->item = (struct pair **)realloc(h->item,sizeof(struct pair *) * h->size);
	MinHeapify(h->item,0,h->size);
	return h;
}
//pRIORITY qUEUE dECLARATION
											////////////////////////
											//////GRAPH UTILITIES///
											////////////////////////

//GRAPH ALGORITHM
int visited[10001];

void Dijkstra(struct vector **graph,int src,int n,int *prev,int *dist)
{
	for(int i = 0;i<n;i++)
	{
		prev[i] = -1;
		dist[i] = INF;
	}
	dist[src] = 0;
	struct pq *mypq;
	mypq = init_pq();
	mypq = push_pq(mypq,make_pair(dist[src],src));
	while(!isEmpty(mypq))
	{
		int root = top_pq(mypq)->y;
		mypq = pop_pq(mypq);
		for(int i = 0;i<graph[root]->size;i++)
		{
			if(dist[root] + graph[root]->arr[i]->w < dist[graph[root]->arr[i]->to])
			{
				dist[graph[root]->arr[i]->to] = dist[root] + graph[root]->arr[i]->w;
                //printf("child-->%d %d\n",graph[root]->arr[i]->to,dist[graph[root]->arr[i]->to]);
				prev[graph[root]->arr[i]->to] = root;
				mypq = push_pq(mypq,make_pair(dist[graph[root]->arr[i]->to],graph[root]->arr[i]->to));
			}
		}
	}
}

void apsp(struct vector **graph,int src,int n,FILE *ft)
{
	int *prev,*dist;
	prev = (int *)malloc(sizeof(int) * n);
	dist = (int *)malloc(sizeof(int) * n);
	Dijkstra(graph,src,n,prev,dist);
    for(int i = 0;i<n;i++)
    {
        if(dist[i] == INF)
        {
            fprintf(ft,"%d INF\n",i);
            continue;
        }
        fprintf(ft,"%d %d\n",i,dist[i]);
    }
    return;
}
//GRAPH ALGORITHM

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
	int n,m;
	fscanf(fs,"%d %d",&n,&m);
	struct vector **graph;
	graph = (struct vector *)malloc(sizeof(struct vector) * n);
	for(int i = 0;i<n;i++)
		graph[i] = init_v();
	for(int i = 0;i < m;i++)
	{
		int u,v,w;
		fscanf(fs,"%d %d %d",&u,&v,&w);
		graph[u] = push_back(graph[u],v,w);
	}
	int src;
	fscanf(fs,"%d",&src);
	apsp(graph,src,n,ft);
	fclose(fs);
	fclose(ft);
	return 0;
}
/////////////////////////
///DRIVER FUNCTION END///
/////////////////////////
