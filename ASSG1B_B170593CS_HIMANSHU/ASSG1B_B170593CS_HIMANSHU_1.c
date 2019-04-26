#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
struct ln{
  int data;
  struct ln *link;
};

struct ll{
  struct ln *head;
  int size;
};

struct ln *createl(int item){
  struct ln *n;
  n = (struct ln *)malloc(sizeof(struct ln));
  n->data = item;
  n->link = NULL;
  return n;
}

struct ll *initl(){
  struct ll *n;
  n = (struct ll*)malloc(sizeof(struct ll));
  n->head = NULL;
  n->size = 0;
  return n;
}

struct ll *insertl(struct ll *h,int item){
  struct ln *tmp;
  tmp = createl(item);
  if (h->head == NULL){
    h->head = tmp;
    h->size++;
    return h;
  }
  else{
    struct ln *curr;
    curr = h->head;
    while (curr->link)
      curr = curr->link;
    curr->link = tmp;
    h->size++;
    return h;
  }
}

struct node{
  int f;
  char ch;
  int t;
  struct node *left,*right;
};

struct bt{
  struct node *root;
};

struct node *create(int freq,char ch,int time){
  struct node *n;
  n = (struct node *)malloc(sizeof(struct node));
  n->f = freq;
  n->ch = ch;
  n->t = time;
  n->left = n->right = NULL;
  return n;
}

struct bt *newbt(){
  struct bt *n;
  n = (struct bt *)malloc(sizeof(struct bt));
  n->root = NULL;
}

int comp(struct node *a,struct node *b)
{
  if (a->f<b->f)
    return 1;
  else if (a->ch == '#' && b->ch == '#' && (a->f == b->f) && (a->t<b->t))
    return 1;
  else if (a->ch == '#' && b->ch == '#' && (a->f == b->f) && (a->t>b->t))
    return 0;
  else if (b->ch == '#' && (a->f == b->f))
    return 1;
  else if (a->ch == '#' && (a->f == b->f))
    return 0;
  else if (a->ch != '#' && b->ch != '#' && (a->f == b->f) && (a->ch < b->ch))
    return 1;
  else
    return 0;
}

struct PriorityQueue{
  struct node **arr;
  int time;
  int size;
};


void swap(struct node **a,struct node **b){
  struct node *tmp = *a;
  *a = *b;
  *b = tmp;
}

struct PriorityQueue *initialise(){
  struct PriorityQueue * n;
  n = (struct PriorityQueue *)malloc(sizeof(struct PriorityQueue));
  n->size = 0;
  n->time = 0;
  n->arr = (struct node *)malloc(sizeof(struct node)*n->size);
  return n;
}

void MinHeapify(struct node **arr,int idx,int n){
  int left = 2 * idx + 1;
  int right = 2 * idx + 2;
  int mn = idx;
  if (left < n && comp(arr[left],arr[mn]))
    mn = left;
  if (right < n && comp(arr[right],arr[mn]))
    mn = right;
  if (mn != idx){
    swap(&arr[mn],&arr[idx]);
    MinHeapify(arr,mn,n);
  }
}

struct PriorityQueue *insert(struct PriorityQueue * pq,struct node *item){
  pq->size++;
  pq->arr = (struct node *)realloc(pq->arr,sizeof(struct node)*pq->size);
  pq->arr[pq->size-1] = item;
  int idx = pq->size-1;
  while (idx>0 && comp(pq->arr[idx],pq->arr[idx/2])){
    swap(&pq->arr[idx],&pq->arr[idx/2]);
    idx /= 2;
  }
  pq->time++;
  return pq;
}

int minimum(struct PriorityQueue * pq){
  if (pq->size)
    return pq->arr[0]->f;
  else
    return -100000009;
}

struct node *extractMin(struct PriorityQueue * pq){
  if (!pq->size)
    return NULL;
  else if (pq->size == 1){
    struct node *tmp = pq->arr[0];
    int sz = pq->size -1;
    pq->arr = (struct node *)realloc(pq->arr,sizeof(struct node)*sz);
    pq->size--;
    return tmp;
  }
  else{
    struct node *tmp = pq->arr[0];
    swap(&pq->arr[0],&pq->arr[pq->size-1]);
    int sz = pq->size - 1;
    pq->arr = (struct node *)realloc(pq->arr,sizeof(struct node)*sz);
    pq->size--;
    MinHeapify(pq->arr,0,pq->size);
    return tmp;
  }
}

struct node *buildTree(struct PriorityQueue *pq){
  while(pq->size > 0 && pq->size != 1){
    struct node *tmp0 = extractMin(pq);
    struct node *tmp1 = extractMin(pq);
    int f0 = tmp0->f,f1 = tmp1->f;
    struct node *newnode;
    newnode = create(f0+f1,'#',pq->time);
    newnode->left = tmp0;
    newnode->right = tmp1;
    pq = insert(pq,newnode);
  }
  return extractMin(pq);
}

void print_arr(int *arr,int n){
  for (int i = 0;i<n;i++)
    printf("%d ",arr[i]);
  printf("\n");
}

void preorder(struct node *root,struct ll **aRes,int *tmp,int top){
  if (root->left){
    tmp[top] = 0;
    preorder(root->left,aRes,tmp,top+1);
  }
  if (root->right){
    tmp[top] = 1;
    preorder(root->right,aRes,tmp,top+1);
  }
  if (!(root->left)&&!(root->right)){
    for (int i = 0;i<top;i++){
      aRes[root->ch - 'a'] = insertl(aRes[root->ch - 'a'],tmp[i]);
    }
  }
}

struct ll **find_huffman_code(char *str)
{
  struct PriorityQueue * pq;
  pq = initialise();
  int *alpha;
  alpha = (int *)malloc(sizeof(int)*26);
  for (int i = 0;i<26;i++)
    alpha[i] = 0;
  int n = strlen(str);
  for (int i = 0;i<n;i++){
    alpha[str[i] - 'a']++;
  }
  int visited[26];
  for (int i = 0;i<26;i++)
    visited[i] = 0;
  for (int i = 0;i<n;i++)
    {
      char c = str[i];
      if (!visited[c-'a'])
	{
	  struct node *tmp;
	  tmp = create(alpha[c-'a'],c,pq->time);
	  pq = insert(pq,tmp);
	  visited[c-'a'] = 1;
	}
    }
  struct ll **aRes;
  int *tmp;
  tmp = (int *)malloc(sizeof(int)*n);
  aRes = (struct ll *)malloc(sizeof(struct ll)*26);
  for (int i = 0;i<26;i++)
    aRes[i] = initl();
  struct node *huffmanTree;
  huffmanTree = buildTree(pq);
  preorder(huffmanTree,aRes,tmp,0);
  return aRes;
}

void print_codes(char *str,FILE *ft)
{
  struct ll **aRes;
  int n = strlen(str);
  aRes = find_huffman_code(str);
  for (int i = 0;i<n;i++){
    struct ln *curr;
    curr = aRes[str[i] - 'a']->head;
    while(curr){
      fprintf(ft,"%d",curr->data);
      curr = curr->link;
    }
    fprintf(ft," ");
  }
  fprintf(ft,"\n");
}

int main()
{
  FILE *fs,*ft;
  fs = fopen("input.txt","r");
  if (fs == NULL)
  {
    printf("Could not open input file.\n");
    exit(0);
  }
  ft = fopen("output.txt","w");
  if (ft == NULL)
  {
    printf("Could not open output file.\n");
    fclose(fs);
    exit(0);
  }
  char *str;
  str = (char *)malloc(sizeof(char)*1000000);
  while(fscanf(fs,"%s",str) != EOF)
    print_codes(str,ft);
  return 0;
}
