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
											////////////////////////
											//////GRAPH UTILITIES///
											////////////////////////

//GRAPH ALGORITHM
int visited[10001];

void DFSUtil(struct vector **graph,int src,int dest,int *flag,FILE *ft)
{
	visited[src] = 1;
	fprintf(ft,"%d ",src);
	if(src == dest)
	{
        *flag = 1;
        return;
    }
	for(int j = 0;j<graph[src]->size;j++)
	{
		if(!visited[graph[src]->arr[j]->to] && !(*flag))
			DFSUtil(graph,graph[src]->arr[j]->to,dest,flag,ft);
	}
	return;
}

void DFS(struct vector **graph,int n,int src,int dest,FILE *ft)
{
	for(int i = 0;i<n+1;i++)
		visited[i] = 0;
    int flag = 0;
	DFSUtil(graph,src,dest,&flag,ft);
	fprintf(ft,"\n");
}

void BFS(struct vector **graph,int n,int src,int dest,FILE *ft)
{
	for(int i = 0;i<n+1;i++)
		visited[i] = 0;
	struct queue *myq;
	myq = init_q();
	myq = enqueue(myq,src,0);
	visited[src] = 1;
	while(!empty(myq))
	{
		int root = myq->front->item->to;
		myq = dequeue(myq);
		fprintf(ft,"%d ",root);
		if(root == dest)
			break;
		for(int i = 0;i<graph[root]->size;i++)
		{
			if(!visited[graph[root]->arr[i]->to])
			{
				visited[graph[root]->arr[i]->to] = 1;
				myq = enqueue(myq,graph[root]->arr[i]->to,graph[root]->arr[i]->w);
			}
		}
	}
	fprintf(ft,"\n");
}
//GRAPH ALGORITHM

int *str_to_numb(char *str,int *sz)
{
	int n = strlen(str);
	int *res = (int *)malloc(sizeof(int) * 0);
	int i = 0;
	while(i<n && str[i] != '\n')
	{
		if(str[i] >= '0' && str[i] <= '9')
		{
			int numb = 0;
			while(str[i] >= '0' && str[i] <= '9')
			{
				numb = 10 * numb + (str[i] - '0');
				i++;
			}
			(*sz)++;
			res = (int *)realloc(res,sizeof(int) * (*sz));
			res[*sz-1] = numb;
		}
		i++;
	}
	return res;
}

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
		graph[i] = init_v();
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
				graph[node] = push_back(graph[node],numb,1);
			}
			if (c == '\n')
				break;
			c = getc(fs);
		}
		node++;
	}
	char *str = (char *)malloc(sizeof(char) * 1000);
	while(fscanf(fs," %[^\n]s",str) != EOF)
	{
		if(str[0] == 's')
			return 0;
		else if(str[0] == 'd')
		{
			int sz = 0;
			int *arr = str_to_numb(str,&sz);
			DFS(graph,n,arr[0],arr[1],ft);
		}
		else if(str[0] == 'b')
		{
			int sz = 0;
			int *arr = str_to_numb(str,&sz);
			BFS(graph,n,arr[0],arr[1],ft);
		}
	}
}
