#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef long long ll;
#define upto(i,a,b,inc) for(int i = a;i<=b;i+=inc)
#define downto(i,a,b,dec) for(int i = a;i>=b;i-=dec)
#define read(arr,myset,n) upto(i,0,n-1,1){scanf("%d",&arr[i]);myset->root = insert(myset->root,arr[i]);}
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

void preorder(struct node *root){
  if (root){
    printf("%d(",root->data);
    preorder(root->left);
    printf(")(");
    preorder(root->right);
    printf(")");
  }
}

int main()
{
  int n;
  scanf("%d",&n);
  int *arr;
  arr = (int *)malloc(sizeof(int) * n);
  struct BST *myset;
  struct node *itr;
  myset = initialise();
  read(arr,myset,n);
  printf("(");
  preorder(myset->root);
  printf(")");
  br;
  return 0;
}
