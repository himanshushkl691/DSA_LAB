#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

struct Node *hash[1000001];

int min(int a,int b)
{
	return ((a<b)?a:b);
}

void swap(int *a,int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

struct Node
{
	int item;
	int degree;
	struct Node *left,*sibling,*parent;
};

struct BinomialHeap
{
	struct Node *head;
};

struct q_node
{
	struct Node *item;
	struct q_node *link;
};

struct queue
{
	int size;
	struct q_node *front,*tail;
};

struct q_node *create_q_node(struct Node *item)
{
	struct q_node *n;
	n = (struct q_node *)malloc(sizeof(struct q_node));
	n->item = item;
	n->link = NULL;
	return n;
}

struct queue *init()
{
	struct queue *n;
	n = (struct queue *)malloc(sizeof(struct queue));
	n->front = n->tail = NULL;
	n->size = 0;
	return n;
}

int empty(struct queue *h)
{
	return (h->size == 0);
}

struct queue *enqueue(struct queue *h,struct Node *x)
{
	struct q_node *newnode = create_q_node(x);
	if(!(h->front))
	{
		h->front = newnode;
		h->tail = newnode;
		h->size++;
		return h;
	}
	h->tail->link = newnode;
	h->tail = newnode;
	h->size++;
	return h;
}

struct q_node *dequeue(struct queue *h)
{
	struct q_node *ans = h->front;
	h->front = h->front->link;
	h->size--;
	return ans;
}

struct Node *createNode(int item)
{
	struct Node *newn;
	newn = (struct Node *)malloc(sizeof(struct Node));
	newn->left = newn->sibling = newn->parent = NULL;
	newn->degree = 0;
	newn->item = item;
	return newn;
}

struct BinomialHeap *MakeHeap()
{
	struct BinomialHeap *newn;
	newn = (struct BinomialHeap *)malloc(sizeof(struct BinomialHeap));
	newn->head = NULL;
	return newn;
}

struct BinomialHeap *attach(struct BinomialHeap *h,int item)
{
	struct Node *newnode = createNode(item);
	if(!(h->head))
	{
		h->head = newnode;
		return h;
	}
	struct Node *curr = h->head;
	while(curr->sibling)
		curr = curr->sibling;
	curr->sibling = newnode;
	return h;
}

struct BinomialHeap *attachNode(struct BinomialHeap *h,struct Node *n)
{
	if(!h->head)
	{
		h->head = n;
		h->head->sibling = NULL;
		return h;
	}
	struct Node *curr = h->head;
	while(curr->sibling)
		curr = curr->sibling;
	curr->sibling = n;
	curr->sibling->sibling = NULL;
	return h;
}

struct BinomialHeap *attachNodeBefore(struct BinomialHeap *h,struct Node *n)
{
	if (!h->head)
	{
		h->head = n;
		h->head->sibling = NULL;
		return h;
	}
	n->sibling = h->head;
	h->head = n;
	return h;
}

struct Node *BinomialLink(struct Node *x,struct Node *y)
{
	x->sibling = y->left;
	x->parent = y;
	y->left = x;
	y->degree++;
	return y;
}

struct BinomialHeap *BinomialMerge(struct BinomialHeap *h1,struct BinomialHeap *h2)
{
	struct Node *curr0,*curr1;
	curr0 = h1->head;curr1 = h2->head;
	struct BinomialHeap *newh;
	newh = MakeHeap();
	while(curr0 && curr1)
	{
		if(curr0->degree < curr1->degree)
		{
			struct Node *tmp = curr0->sibling;
			newh = attachNode(newh,curr0);
			curr0 = tmp;
		}
		else
		{
			struct Node *tmp = curr1->sibling;
			newh = attachNode(newh,curr1);
			curr1 = tmp;
		}
	}
	if(curr0)
	{
		while(curr0)
		{
			struct Node *tmp = curr0->sibling;
			newh = attachNode(newh,curr0);
			curr0 = tmp;
		}
	}
	if(curr1)
	{
		while(curr1)
		{
			struct Node *tmp = curr1->sibling;
			newh = attachNode(newh,curr1);
			curr1 = tmp;
		}
	}
	return newh;
}

struct BinomialHeap *BinomialUnion(struct BinomialHeap *h1,struct BinomialHeap *h2)
{
	struct BinomialHeap *n;
	n = (struct BinomialHeap *)malloc(sizeof(struct BinomialHeap));
	n = BinomialMerge(h1,h2);
	if (!n->head)
		return n;
	struct Node *prev_x,*x,*next_x;
	prev_x = NULL;
	x = n->head;
	next_x = x->sibling;
	while(next_x)
	{
		if((x->degree != next_x->degree) || (next_x->sibling && next_x->sibling->degree == x->degree))
		{
			prev_x = x;
			x = next_x;
		}
		else
		{
			if (x->item <= next_x->item)
			{
				x->sibling = next_x->sibling;
				BinomialLink(next_x,x);
			}
			else
			{
				if (!prev_x)
				{
					n->head = next_x;
				}
				else
				{
					prev_x->sibling = next_x;
				}
				BinomialLink(x,next_x);
				x = next_x;
			}
		}
		next_x = x->sibling;
	}
	return n;
}

struct BinomialHeap *Insert(struct BinomialHeap *h,int x)
{
	struct BinomialHeap *n;
	n = MakeHeap();
	n = attach(n,x);
	hash[x] = n->head;
	h = BinomialUnion(h,n);
	return h;
}

struct Node *minimum(struct BinomialHeap *h)
{
	struct Node *curr = h->head,*res = NULL;
	int mn = 1000000007;
	while(curr)
	{
		if(curr->item<mn)
		{
			mn = curr->item;
			res = curr;
		}
		curr = curr->sibling;
	}
	return res;
}

struct BinomialHeap *extractMin(struct BinomialHeap *h)
{
	struct Node *root = minimum(h);
	if(root)
	{
		struct Node *curr = h->head,*prev = NULL,*tmp;
		while(curr && curr!=root)
		{
			prev = curr;
			curr = curr->sibling;
		}
		if(curr)
		{
			if(!prev)
				h->head = curr->sibling;
			else
				prev->sibling = curr->sibling;
		}
		struct BinomialHeap *newh;
		newh = MakeHeap();
		tmp = root->left;
		while(tmp)
		{
			struct Node *temp = tmp->sibling;
			newh = attachNodeBefore(newh,tmp);
			tmp = temp;
		}
		h = BinomialUnion(h,newh);
		return h;
	}
}

struct BinomialHeap *decreaseKey(struct BinomialHeap *h,struct Node *x,int key)
{
	if (key > x->item)
		return h;
	else
	{
		struct Node *tmp = hash[x->item];
		hash[x->item] = NULL;
		x->item = key;
		struct Node *y = x->parent;
		if(key>=0)
			hash[key] = x;
		while(y && y->item>x->item)
		{
			if(key>=0)
				hash[key] = y;
			hash[y->item] = x;
			swap(&y->item,&x->item);
			x = y;
			y = x->parent;
		}
		return h;
	}
}

struct BinomialHeap *delNode(struct BinomialHeap *h,struct Node *x)
{
	if(!x)
		return h;
	hash[x->item] = NULL;
	h = decreaseKey(h,x,-1000000007);
	h = extractMin(h);
	return h;
}

void printBinomialTree(struct Node * h,FILE *ft)
{
	struct queue *myqueue;
	myqueue = init();
	if (h)
		myqueue = enqueue(myqueue,h);
	while(!empty(myqueue))
	{
		struct Node *curr = dequeue(myqueue)->item;
		while(curr)
		{
			fprintf(ft,"%d ",curr->item);
			if(curr->left)
				myqueue = enqueue(myqueue,curr->left);
			curr = curr->sibling;
		}
	}
}

int str_to_num(char *str,int i)
{
	int n = strlen(str);
	int numb = 0;
	while(i<n && str[i]>='0' && str[i]<='9')
	{
		numb = numb * 10 + (str[i] - '0');
		i++;
	}
	return numb;
}

int main()
{
	struct BinomialHeap *c;
	c = MakeHeap();
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
	char *str;
	str = (char *)malloc(sizeof(char) * 1000001);
	while(fscanf(fs," %[^\n]s",str) != EOF)
	{
		if (str[0] == 's')
			return 0;
		else if (str[0] == 'm')
		{
			if(minimum(c))
				fprintf(ft,"%d\n",minimum(c)->item);
			else
				fprintf(ft,"ERROR\n");
		}
		else if (str[0] == 'x')
		{
			if(minimum(c))
			{
				c = extractMin(c);
			}
			else
				fprintf(ft,"ERROR\n");
		}
		else if (str[0] == 'p')
		{
			printBinomialTree(c->head,ft);
			fprintf(ft,"\n");
		}
		else if (str[0] == 'i')
		{
			int k = str_to_num(str,2);
			c = Insert(c,k);
		}
		else if (str[0] == 'd')
		{
			int k = str_to_num(str,2);
			c = delNode(c,hash[k]);
		}
	}
	return 0;
}
