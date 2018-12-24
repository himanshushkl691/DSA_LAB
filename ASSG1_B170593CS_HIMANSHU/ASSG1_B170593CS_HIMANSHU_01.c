#include <stdio.h>
#include <stdlib.h>
#define br printf("\n");
#define upto(i,a,b,inc) for(int i = a;i<=b;i += inc)
#define INF 1000000007

struct node{
	int data;
	struct node *link;
};

struct linked_list{
	struct node *head;
};

struct t_node{
	int data;
	int freq;
	struct t_node *left,*right;
};

struct set{
	struct t_node *root;
};

struct t_node *tn(int item)
{
	struct t_node *n;
	n = (struct t_node *)malloc(sizeof(struct t_node));
	n->data = item;
	n->freq = 1;
	n->left = n->right = NULL;
	return n;
}

struct set *news()
{
	struct set *n;
	n = (struct set *)malloc(sizeof(struct set));
	n->root = NULL;
	return n;
}

struct t_node *insert(struct t_node *root,int item)
{
	if (!root)
	{
		struct t_node *n;
		n = tn(item);
		root = n;
	}
	else if (item < root->data)
		root->left = insert(root->left,item);
	else if (item > root->data)
		root->right = insert(root->right,item);
	else if (item == root->data)
		root->freq++;
	return root;
}
int best = 0,elt = -INF;
int h_occur(struct t_node *root)
{
	if(root)
	{
		if (root->freq > best)
		{
			best = root->freq;
			elt = root->data;
		}
		h_occur(root->left);
		h_occur(root->right);
	}
}

struct node* newnode(int item)
{
	struct node * newn;
	newn = (struct node*)malloc(sizeof(struct node));
	newn->link = NULL;
	newn->data = item;
	return newn;
}

struct linked_list *newl()
{
	struct linked_list *l;
	l = (struct linked_list*)malloc(sizeof(struct linked_list));
	l->head = NULL;
	return l;
}

struct node *add_node(struct node *head,int item)
{
	if (!head)
	{
		struct node *nn;
		nn = newnode(item);
		head = nn;
	}
	else
		head->link = add_node(head->link,item);
	return head;
}

void print(struct node *head,FILE *ft)
{
	if (head)
	{
		fprintf(ft,"%d ",head->data);
		print(head->link,ft);
	}
}

void create(struct linked_list *h,struct set *myset,FILE *fs)
{
	int a,n;
	char ch;
	fscanf(fs,"%d",&n);
	upto(i,0,n-1,1)
	{
		int a;
		fscanf(fs,"%d",&a);
		h->head = add_node(h->head,a);
		myset->root = insert(myset->root,a);
	}
}

int main()
{
	FILE *fs,*ft;
	fs = fopen("input.txt","r");
	if (fs == NULL)
	{
		printf("Could not open input file\n");
		exit(0);
	}
	ft = fopen("output.txt","w");
	if (ft == NULL)
	{
		printf("Error opening output file\n");
		fclose(fs);
		exit(0);
	}
	char ch;
	struct linked_list *h;
	struct set *myset;
	h = newl();
	myset = news();
	while (fscanf(fs,"%c",&ch) == 1)
	{
		if (ch == 's')
			return 0;
		else if (ch == 'c')
		{
			h = newl();
			myset = news();
			create(h,myset,fs);
		}
		else if (ch == 'p')
		{
			print(h->head,ft);
			fprintf(ft,"\n");
		}
		else if (ch == 'h')
		{
			best = 0;
			elt = -INF;
			h_occur(myset->root);
            if (elt == -INF)
                fprintf(ft,"no element is there\n");
            else
                fprintf(ft,"%d\n",elt);
		}
		else if (ch == 'a')
		{
			int a;
			fscanf(fs,"%d",&a);
			h->head = add_node(h->head,a);
			myset->root = insert(myset->root,a);
		}
	}
}
