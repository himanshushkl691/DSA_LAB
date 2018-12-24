#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef long long ll;
#define upto(i,a,b,inc) for(int i = a;i<=b;i+=inc)
#define downto(i,a,b,dec) for(int i = a;i>=b;i-=dec)
#define MAX 10000001
#define INF 1000000007
#define br printf("\n")

struct node{
  int data;
  struct node *left,*right,*parent;
};

struct BST{
  struct node *root;
};

struct node *create(int item){
  struct node *tmp;
  tmp = (struct node *)malloc(sizeof(struct node));
  tmp->data = item;
  tmp->left = tmp->right = tmp->parent =  NULL;
  return tmp;
}

struct BST *initialise(){
  struct BST *n;
  n = (struct BST *)malloc(sizeof(struct BST));
  n->root = NULL;
  return n;
}

int data(struct node *h){
  return h->data;
}

struct node *insert(struct node *root,int item)
{
  if (!root)
    {
      struct node *n;
      n = create(item);
      root = n;
    }
  else if (item <= data(root))
    {
      struct node *tmp;
      tmp = insert(root->left,item);
      root->left = tmp;
      tmp->parent = root;
    }
  else if (item > data(root))
    {
      struct node *tmp;
      tmp = insert(root->right,item);
      root->right = tmp;
      tmp->parent = root;
    }
  return root;
}

struct node *search(struct node *root,int key){
  if (!root)
    return root;
  else if (key == data(root))
    return root;
  else if(key <= data(root))
    return search(root->left,key);
  else
    return search(root->right,key);
}

struct node *findMin(struct node *root){
  struct node *curr;
  curr = root;
  if (!curr)
    return curr;
  while (curr->left)
    curr = curr->left;
  return curr;
}

struct node *findMax(struct node *root){
  struct node *curr;
  curr = root;
  if (!curr)
    return curr;
  while (curr->right)
    curr = curr->right;
  return curr;
}

struct node *predecessor(struct node *root,struct node *key){
  if (!key)
    return NULL;
  if (key->left)
    return findMax(key->left);
  int mx = -1;
  struct node *res,*curr;
  res = NULL;curr = root;
  while (curr != key){
    if (data(curr)<=data(key) && data(key)>=mx){
      res = curr;
      mx = data(curr);
    }
    if (data(key)<=data(curr))
      curr = curr->left;
    else
      curr = curr->right;
  }
  if (mx == -1)
    return NULL;
  return res;
}


struct node *successor(struct node *root,struct node *key){
  if (!key)
    return NULL;
  if (key->right)
    return findMin(key->right);
  int mn = INF;
  struct node *curr,*res;
  res = NULL;curr = root;
  while (curr != key){
    if (data(curr)>=data(key) && data(key)<=mn){
      res = curr;
      mn = data(curr);
    }
    if (data(key)<=data(curr))
      curr = curr->left;
    else
      curr = curr->right;
  }
  if (mn == INF)
    return NULL;
  return res;
}

struct node *delete(struct node *root,struct node *key){
  struct node *y,*x;
  if (key->left == NULL || key->right == NULL){
    y = key;
  }
  else
    y = successor(root,key);
  if (y->left)
    x = y->left;
  else
    x = y->right;
  if (x)
    x->parent = y->parent;
  if (y->parent == NULL)
    root = x;
  else if (y == y->parent->left)
    y->parent->left = x;
  else if(y == y->parent->right)
    y->parent->right = x;
  if(key != y)
    key->data = y->data;
  free(y);
  return root;
}

void preorder(struct node *root,FILE *ft){
  if (root){
    fprintf(ft,"%d ",root->data);
    preorder(root->left,ft);
    preorder(root->right,ft);
  }
}

void inorder(struct node *root,FILE *ft){
  if (root){
    inorder(root->left,ft);
    fprintf(ft,"%d ",root->data);
    inorder(root->right,ft);
  }
}

void postorder(struct node *root,FILE *ft){
  if (root){
    postorder(root->left,ft);
    postorder(root->right,ft);
    fprintf(ft,"%d ",root->data);
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
      printf("Could not open output file\n");
      fclose(fs);
      exit(0);
    }
  char s1[4];
  struct BST *myset;
  struct node *itr;
  myset = initialise();
  //stop stopping
  //insr insertion
  //srch searching
  //minm minimum
  //maxm maximum
  //pred predecessor
  //succ successor
  //delt delete
  //inor inorder
  //prer preorder
  //post postorder
  while(1){
  fscanf(fs,"%s",s1);
  if (strcmp(s1,"stop") == 0)
    return 0;
  else if (strcmp(s1,"insr") == 0)
    {
      int a;
      fscanf(fs,"%d",&a);
      myset->root = insert(myset->root,a);
    }
  else if(strcmp(s1,"srch") == 0)
    {
      int key;
      fscanf(fs,"%d",&key);
      itr = search(myset->root,key);
      if (itr)
	fprintf(ft,"FOUND\n");
      else
	fprintf(ft,"NOT FOUND\n");
    }
  else if (strcmp(s1,"minm") == 0)
    {
      itr = findMin(myset->root);
      if (itr)
	fprintf(ft,"%d\n",data(itr));
      else
	fprintf(ft,"NIL\n");
    }
  else if (strcmp(s1,"maxm") == 0)
    {
      itr = findMax(myset->root);
      if (itr)
	fprintf(ft,"%d\n",data(itr));
      else
	fprintf(ft,"NIL\n");
    }
  else if (strcmp(s1,"pred") == 0)
    {
      int key;
      fscanf(fs,"%d",&key);
      itr = search(myset->root,key);
      if (itr)
	{
	  struct node *pr;
	  pr = predecessor(myset->root,itr);
	  if (pr == NULL)
	    fprintf(ft,"NIL\n");
	  else
	    fprintf(ft,"%d\n",data(pr));
	}
      else
	fprintf(ft,"NOT FOUND\n");
    }
  else if (strcmp(s1,"succ") == 0)
    {
      int key;
      fscanf(fs,"%d",&key);
      itr = search(myset->root,key);
      if (itr)
	{
	  struct node *su;
	  su = successor(myset->root,itr);
	  if (su == NULL)
	    fprintf(ft,"NIL\n");
	  else
	    fprintf(ft,"%d\n",data(su));
	}
      else
	fprintf(ft,"NOT FOUND\n");
    }
  else if (strcmp(s1,"delt") == 0)
    {
      int key;
      fscanf(fs,"%d",&key);
      itr = search(myset->root,key);
      myset->root = delete(myset->root,itr);
    }
  else if (strcmp(s1,"inor") == 0)
    {
      inorder(myset->root,ft);
      fprintf(ft,"\n");
    }
  else if (strcmp(s1,"prer") == 0)
    {
      preorder(myset->root,ft);
      fprintf(ft,"\n");
    }
  else if (strcmp(s1,"post") == 0)
    {
      postorder(myset->root,ft);
      fprintf(ft,"\n");
    }
}
  return 0;
}
