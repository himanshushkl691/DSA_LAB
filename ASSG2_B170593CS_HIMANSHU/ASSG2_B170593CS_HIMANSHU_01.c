#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <math.h>
#define INF 1000000007

int c1,c2;

/**PRIME**/
int isPrime(int n)
{
  if (n == 2)
    return 1;
  if (n%2 == 0)
    return 0;
  else
  {
    for (int i = 3;i * i <=n;i+=2)
    {
      if (n % i == 0)
        return 0;
    }
  }
  return 1;
}

int find_prev_prime(int n)
{
  if (n == 1)
    return 1;
  else
  {
    for (int i = n ;i>=1;i--)
    {
      if (isPrime(i))
        return i;
    }
  }
}
/**PRIME FOUND**/

/**DOUBLY LINKED LIST DEFINITION**/
struct node{
  int data;
  struct node *next,*prev;
};

struct ll{
  int size;
  struct node *head,*tail;
};

struct node *create(int item)
{
  struct node *n;
  n = (struct node *)malloc(sizeof(struct node *));
  n->data = item;
  n->prev = n->next = NULL;
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

int getData(struct node *h)
{
  return h->data;
}

int getSize(struct ll *h)
{
  return h->size;
}


struct ll *push_front(struct ll *h,int item)
{
  struct node *newnode;
  newnode = create(item);
  if (!h->head)
  {
    h->head = newnode;
    h->tail = newnode;
  }
  else
  {
    newnode->next = h->head;
    h->head->prev = newnode;
    h->head = newnode;
  }
  h->size++;
  return h;
}

struct ll *push_back(struct ll *h,int item)
{
    struct node *newnode;
    newnode = create(item);
    if (!h->head)
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
    h->head = curr1;
    n->next = NULL;
    free(n);
  }
  else if (curr0 && !curr1)
  {
    curr0->next = NULL;
    n->prev = NULL;
    free(n);
  }
  else
  {
    curr0->next = n->next;
    n->next->prev = curr0;
    free(n);
  }
  h->size--;
  return h;
}

void print_ll(struct ll *h,FILE *ft)
{
  struct node *curr;
  curr = h->head;
  if (curr){
  while (curr->next)
  {
    if (getData(curr) != -INF)
        fprintf(ft,"%d ",getData(curr));
    curr = curr->next;
  }
  if (getData(curr)!= -INF)
    fprintf(ft,"%d",getData(curr));
  }
}
/**DOUBLY LINKED LIST DEFINED **/

/**HASH TABLE DEFINITION **/
struct ht{
  struct ll **arr;
  int size;
};

struct ht *hashTable(int m)
{
  struct ht *n;
  n = (struct ht *)malloc(sizeof(struct ht));
  n->arr = (struct ll *)malloc(sizeof(struct ll)*m);
  for (int i = 0;i<m;i++)
    n->arr[i] = initialise();
  n->size = m;
  return n;
}

int hash(int k,int m)
{
  return (k%m);
}

int linear_hash(int k,int m,int i)
{
  return ((hash(k,m) + i)%m);
}

int quadratic_hash(int k,int m,int i)
{
  return ((hash(k,m) + (c1 * i) + (c2 * i * i))%m);
}

int double_hash(int k,int m,int i)
{
  int h1 = hash(k,m);
  int h2 = find_prev_prime(m-1) - (k%find_prev_prime(m-1));
  return ((h1 + (i * h2))%m);
}
/** LINEAR PROBING **/
/**-INF represents deleted place **/
struct ht *linear_probing_insert(struct ht * h,int k,int m)
{
  int i = 0;
  while (i<m)
  {
    int h1 = linear_hash(k,m,i);//hash
    if (h->arr[h1]->head == NULL)
    {
      h->arr[h1] = push_back(h->arr[h1],k);
      return h;
    }
    if (h->arr[h1]->head && getData(h->arr[h1]->head) == -INF)
    {
      h->arr[h1]->head->data = k;
      return h;
    }
    i++;
  }
  return h;
}

struct node *linear_probing_search(struct ht * h,int k,int m)
{
  int i = 0;
  while (i<m)
  {
    int h1 = linear_hash(k,m,i);
    if (h->arr[h1]->head && getData(h->arr[h1]->head) == k)
      return h->arr[h1]->head;
    if (h->arr[h1]->head == NULL)
      return NULL;
    i++;
  }
}
/**LINEAR PROBING END**/

/**QUADRATIC PROBING**/
struct ht *quadratic_probing_insert(struct ht * h,int k,int m)
{
  int i = 0;
  while (i<m)
  {
    int h1 = quadratic_hash(k,m,i);
    if (h->arr[h1]->head == NULL)
    {
      h->arr[h1] = push_back(h->arr[h1],k);
      return h;
    }
    if (h->arr[h1]->head && getData(h->arr[h1]->head) == -INF)
    {
      h->arr[h1]->head->data = k;
      return h;
    }
    i++;
  }
  return h;
}

struct node *quadratic_probing_search(struct ht * h,int k,int m)
{
  int i = 0;
  while (i<m)
  {
    int h1 = quadratic_hash(k,m,i);
    if (h->arr[h1]->head && getData(h->arr[h1]->head) == k)
      return h->arr[h1]->head;
    if (h->arr[h1]->head == NULL)
      return NULL;
    i++;
  }
  return NULL;
}
/**QUADRATIC PROBING**/

/**DOUBLE HASHING**/
struct ht *double_hashing_insert(struct ht * h,int k,int m)
{
  int i = 0;
  while (i<m)
  {
    int h1 = double_hash(k,m,i);
    if (h->arr[h1]->head == NULL)
    {
      h->arr[h1] = push_back(h->arr[h1],k);
      return h;
    }
    if (h->arr[h1]->head && getData(h->arr[h1]->head) == -INF)
    {
      h->arr[h1]->head->data = k;
      return h;
    }
    i++;
  }
  return h;
}

struct node *double_hashing_search(struct ht * h,int k,int m)
{
  int i = 0;
  while (i<m)
  {
    int h1 = double_hash(k,m,i);
    if (h->arr[h1]->head && getData(h->arr[h1]->head) == k)
      return h->arr[h1]->head;
    if (h->arr[h1]->head == NULL)
      return NULL;
    i++;
  }
  return NULL;
}
/**DOUBLE HASHING END**/

/**CHAINING**/
struct ht *chaining_insert(struct ht * h,int k,int m)
{
  h->arr[hash(k,m)] = push_back(h->arr[hash(k,m)],k);
  return h;
}

struct node *chaining_search(struct ht * h,int k,int m)
{
  struct node *curr;
  curr = h->arr[hash(k,m)]->head;
  while(curr)
  {
    if (getData(curr) == k)
      return curr;
    curr = curr->next;
  }
  return curr;
}
/**CHAINING END**/

struct ht * insert(struct ht *h,int k,int m,char ch)
{
  switch(ch)
  {
    case 'a':
      if (!linear_probing_search(h,k,m))
        return linear_probing_insert(h,k,m);
      else
        return h;
      break;
    case 'b':
      if (!quadratic_probing_search(h,k,m))
        return quadratic_probing_insert(h,k,m);
      else
        return h;
      break;
    case 'c':
      if (!double_hashing_search(h,k,m))
        return double_hashing_insert(h,k,m);
      else
        return h;
      break;
    case 'd':
      if (!chaining_search(h,k,m))
        return chaining_insert(h,k,m);
      else
        return h;
      break;
  }
}

struct node* search(struct ht *h,int k,int m,char ch)
{
  switch(ch)
  {
    case 'a':
      return linear_probing_search(h,k,m);
      break;
    case 'b':
      return quadratic_probing_search(h,k,m);
      break;
    case 'c':
      return double_hashing_search(h,k,m);
      break;
    case 'd':
      return chaining_search(h,k,m);
      break;
  }
}

struct ht *delete(struct ht *h,int k,int m,char ch)
{
  switch(ch)
  {
    struct node *n;
    case 'a':
      n = search(h,k,m,'a');
      if (n)
      {
        n->data = -INF;
      }
      break;
    case 'b':
      n = search(h,k,m,'b');
      if (n)
      {
        n->data = -INF;
      }
      break;
    case 'c':
      n = search(h,k,m,'c');
      if (n)
      {
        n->data = -INF;
      }
      break;
    case 'd':
      n = search(h,k,m,'d');
      if (n)
      {
        h->arr[hash(k,m)] = erase(h->arr[hash(k,m)],n);
      }
      break;
  }
  return h;
}

void print_ht(struct ht *h,FILE *ft)
{
    for (int i = 0;i<h->size;i++)
    {
        fprintf(ft,"%d ",i);
        fprintf(ft,"(");
        print_ll(h->arr[i],ft);
        fprintf(ft,")\n");
    }
}
/** HASH TABLE DECLARED **/

int str_to_numb(int a,char *str)
{
    int numb = 0;
    int i = a;
    while (i<strlen(str) && str[i]>='0' && str[i]<='9')
    {
        numb = (10 * numb) + (str[i] - '0');
        i++;
    }
    return numb;
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
    struct ht *myhash;
    char option;
    fscanf(fs,"%c",&option);
    int m;
    fscanf(fs,"%d",&m);
    myhash = hashTable(m);
    if (option == 'b')
        fscanf(fs,"%d %d",&c1,&c2);
    char *str;
    str = (char *)malloc(sizeof(char)*1000001);
    while(fscanf(fs," %[^\n]s",str) != EOF)
    {
        if (str[0] == 't')
            return 0;
        else if (str[0] == 'i')
        {
            int item = str_to_numb(2,str);
            myhash = insert(myhash,item,m,option);
        }
        else if (str[0] == 'd')
        {
            int item = str_to_numb(2,str);
            myhash = delete(myhash,item,m,option);
        }
        else if (str[0] == 's')
        {
            int item = str_to_numb(2,str);
            if (search(myhash,item,m,option))
                fprintf(ft,"1\n");
            else
                fprintf(ft,"-1\n");
        }
        else if (str[0] == 'p')
        {
            print_ht(myhash,ft);
        }
        //str = (char *)malloc(sizeof(char)*1000001);
    }
    return 0;
}
