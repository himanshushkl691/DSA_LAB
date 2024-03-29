#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#define INF 1000000007

int modInv(int x,int y,int mod)
{
    int res = 1;
    x = x%mod;
    while(y>0)
    {
        if (y&1)
        {
            res = (1LL*res*x)%mod;
        }
        y = y>>1;
        x = (1LL*x*x)%mod;
    }
    return res;
}

void swap(int *a,int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

/**PAIR DEFINED**/
struct pair
{
  int x,y;
};

struct pair *make_pair(int x,int y)
{
    struct pair *p;
    p = (struct pair*)malloc(sizeof(struct pair));
    p->x = x;
    p->y = y;
    return p;
}
/**PAIR**/

/**DOUBLY LINKED LIST**/
struct node{
  struct pair *p;
  struct node *next,*prev;
};

struct ll{
  struct node *head,*tail;
  int size;
};

struct node *create(struct pair *point)
{
  struct node *n;
  n = (struct node *)malloc(sizeof(struct node));
  n->p = point;
  n->next = NULL;
  n->prev = NULL;
  return n;
}

struct ll *initialise()
{
  struct ll *n;
  n = (struct ll*)malloc(sizeof(struct ll));
  n->head = n->tail = NULL;
  n->size = 0;
  return n;
}

struct pair * getData(struct node *n)
{
  return n->p;
}

int getSize(struct ll *n)
{
  return n->size;
}

struct ll *push_front(struct ll *h,struct pair *point)
{
  struct node *n;
  n = create(point);
  if (!h->head)
  {
    h->head = n;
    h->tail = n;
    }
  else
    {
      n->next = h->head;
      h->head->prev = n;
      h->head = n;
    }
  h->size++;
  return h;
}

struct ll *push_back(struct ll *h,struct pair *item)
{
    struct node *newnode;
    newnode = create(item);
    if (!h->tail)
    {
        h->head = newnode;
        h->tail = newnode;
    }
    else
    {
        newnode->prev = h->tail;
        h->tail->next = newnode;
        h->tail = newnode;
    }
    h->size++;
    return h;
}

struct ll *erase(struct ll *h,struct node *n)
{
  struct node *curr0,*curr1;
  curr0 = n->prev;
  curr1 = n->next;
  if (!curr0 && !curr1)
    {
      h->head = NULL;
      free(n);
    }
  else if (!curr0 && curr1)
    {
      curr1->prev = NULL;
      n->next = NULL;
      h->head = curr1;
      free(n);
    }
  else if(curr0 && !curr1)
    {
      curr0->next = NULL;
      n->prev = NULL;
      free(n);
    }
  else
    {
      curr0->next = curr1;
      curr1->prev = curr0;
      n->next = NULL;
      n->prev = NULL;
      free(n);
    }
  h->size--;
  return h;
}

void print_ll(struct ll *h)
{
  struct node *curr;
  curr = h->head;
  while (curr)
    {
      printf("(%d, %d) ",getData(curr)->x,getData(curr)->y);
      curr = curr->next;
    }
  printf("\n");
}
/**DOUBLY LINKED LIST(OF PAIRS)**/

/**HASH TABLE **/
struct ht{
  struct ll **arr;
  int size;
};

struct ht *hashTable(int m)
{
  struct ht *n;
  n = (struct ht *)malloc(sizeof(struct ht));
  n->arr = (struct ll*)malloc(sizeof(struct ll)*m);
  for (int i = 0;i<m;i++)
    n->arr[i] = initialise();
  n->size = m;
  return n;
}
int hash(int x,int y,int m)
{
    int tmp = (((x+y+1)*(x+y)*modInv(2,m-2,m))%m + y%m)%m;
    return tmp;
}

struct node *search(struct ht *h,struct pair *p)
{
    struct node *curr;
    curr = h->arr[hash(p->x,p->y,h->size)]->head;
    while (curr)
    {
        if (p->x == getData(curr)->x && p->y == getData(curr)->y)
        {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

struct ht *store(struct ht *h,struct pair *p)
{
    if (!search(h,p)){
    struct node *curr;
    curr = create(p);
    h->arr[hash(p->x,p->y,h->size)] = push_front(h->arr[hash(p->x,p->y,h->size)],p);
    }
    return h;
}

struct ht *delete(struct ht *h,struct pair *p)
{
    struct node *del;
    del = search(h,p);
    if (del)
    {
        h->arr[hash(p->x,p->y,h->size)] = erase(h->arr[hash(p->x,p->y,h->size)],del);
    }
    return h;
}
/**HASH TABLE DEFINED**/

void print(struct ht *h,FILE *ft)
{
    struct ht *temp;
    temp = hashTable(h->size);
    for (int i = 0;i<h->size;i++)
    {
        struct node * curr;
        curr = h->arr[i]->head;
        while (curr)
        {
            temp = store(temp,getData(curr));
            curr = curr->next;
        }
    }
    for (int i = 0;i<temp->size;i++)
    {
        struct node *curr;
        curr = temp->arr[i]->head;
        while(curr)
        {
            struct node *itr;
            struct pair *p0 = getData(curr);
            int x0 = p0->x;
            int y0 = p0->y;
	    struct node *z;
	    z = curr->next;
            struct pair *p1 = make_pair(y0,x0);
            itr = search(temp,p1);
            if (itr)
            {
                fprintf(ft,"(%d, %d)\n",p0->x,p0->y);
                temp = delete(temp,p1);
            }
            temp = delete(temp,p0);
            curr = z;
        }
    }
}

struct pair *str_to_pair(int a,char *str)
{
    int i = a;
    int numb = 0;
    int x,y;
    while (i<strlen(str) && str[i]>='0' && str[i]<='9')
    {
        numb  = (10 * numb) + (str[i]-'0');
        i++;
    }
    x = numb;
    while (i<strlen(str))
    {
        numb = 0;
        while (i<strlen(str) && str[i]>='0' && str[i]<='9')
        {
            numb = (10 * numb) + (str[i] - '0');
            i++;
        }
        i++;
    }
    y = numb;
    struct pair *p;
    p = (struct pair *)malloc(sizeof(struct pair));
    p->x = x;
    p->y = y;
    return p;
}

/**DRIVER FUNCTION**/
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
    struct ht *myhash;
    myhash = hashTable(100000);
    char *str;
    str = (char *)malloc(sizeof(char)*1000000);
    while(fscanf(fs," %[^\n]s",str) != EOF)
    {
        if (str[0] == 'e')
            return 0;
        else if (str[0] == 's')
        {
            struct pair *p;
            p = str_to_pair(3,str);
            myhash = store(myhash,p);
        }
        else if (str[0] == 'p')
	{
            print(myhash,ft);
        }
    }
    return 0;
}
