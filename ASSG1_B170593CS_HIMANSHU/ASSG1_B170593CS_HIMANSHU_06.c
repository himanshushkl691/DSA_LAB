#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef long long ll;
#define upto(i,a,b,inc) for(int i = a;i<=b;i+=inc)
#define downto(i,a,b,dec) for(int i = a;i>=b;i-=dec)
#define MAX 10000001
#define INF 1000000007
#define br printf("\n")

int max(int a,int b){
  return ((a>=b)?a:b);
}

struct node{
  int data;
  int h;
  int level;
  struct node *left,*right,*parent;
};

struct BT{
  struct node *root;
};

struct node *create(int item){
  struct node *tmp;
  tmp = (struct node *)malloc(sizeof(struct node));
  tmp->data = item;
  tmp->h  = tmp->level = 0;
  tmp->left = tmp->right = tmp->parent =  NULL;
  return tmp;
}

struct BT *initialise(){
  struct BT *n;
  n = (struct BT *)malloc(sizeof(struct BT));
  n->root = NULL;
  return n;
}

int data(struct node *h){
  return h->data;
}

int height(struct node *curr){
  if (!curr)
    return -1;
  else{
    if (curr->left && curr->right)
      return max(curr->left->h,curr->right->h) + 1;
    else if (curr->left)
      return curr->left->h + 1;
    else if (curr->right)
      return curr->right->h + 1;
    else
      return 0;
  }
}

void fixHeight(struct node *curr){
  if (curr->left && curr->right)
    curr->h = max(height(curr->left),height(curr->right)) + 1;
  else if (curr->left)
    curr->h = height(curr->left) + 1;
  else if (curr->right)
    curr->h = height(curr->right) + 1;
  else
    curr->h = 0;
}

void setHeight(struct node *curr){
  while (curr){
    fixHeight(curr);
    curr = curr->parent;
  }
}

int findIdx(char *str,int si){
  int cnt = 0;
  if (si<strlen(str)-1 && str[si] == '('){
    cnt++;
    si++;
  }
  while (si<strlen(str)-1 && cnt != 0){
    if (str[si] == '(')
      cnt++;
    else if (str[si] == ')')
      cnt--;
    si++;
  }
  if (si == strlen(str))
    return -1;
  else
    return si;
}

struct node *create_tree(char *str,struct node *root,int si){
  if(si<strlen(str) - 1){
  if (str[si] == ')')
    return NULL;
  else{
    struct node *newnode,*tmp0,*tmp1;
    int numb = 0;
    while(str[si] >= '0' && str[si] <= '9'){
      numb = (10 * numb) + (str[si] - '0');
      si++;
    }
    si--;
    newnode = create(numb);
    root = newnode;
    int idx = findIdx(str,si+1);
    tmp0 = create_tree(str,root->left,si+2);
    root->left = tmp0;
    if (tmp0){
      tmp0->parent = root;
      setHeight(root);
    }
    tmp1 = create_tree(str,root->right,idx+1);
    root->right = tmp1;
    if (tmp1){
      tmp1->parent = root;
      setHeight(root);
    }
  }
  return root;
  }
  else
    return NULL;
}

int diameter(struct node *root){
  if (!root)
    return 0;
  else
    return max(2 + height(root->left) + height(root->right),max(diameter(root->left),diameter(root->right)));
}

int*maxwidthUtil(struct node *root,int *arr,int m){
  if (root){
    arr[m - root->level]++;
    maxwidthUtil(root->left,arr,m);
    maxwidthUtil(root->right,arr,m);
    return arr;
  }
}

int maxwidth(struct node *root){
  int *arr,mx = 0;
  arr = (int *)malloc(sizeof(int)*(height(root)+1));
  upto(i,0,height(root),1)
    arr[i] = 0;
  arr = maxwidthUtil(root,arr,height(root));
  upto(i,0,height(root),1)
    mx = max(mx,arr[i]);
  return mx;
}

void setLevel(struct node *root,int l){
  if (root){
    setLevel(root->left,l+1);
    root->level = l;
    setLevel(root->right,l+1);
  }
}

void preorder(struct node *root,FILE *ft){
  if (root){
    fprintf(ft,"%d ",root->data);
    preorder(root->left,ft);
    preorder(root->right,ft);
  }
}

char *append(char *str,char ch){
  int idx = strlen(str)+1;
  str = (char *)realloc(str,sizeof(char)*idx);
  str[idx-1] = ch;
  return str;
}

int main(){
  FILE *fs,*ft;
  fs = fopen("input.txt","r");
  if (fs == NULL){
    printf("Could not open input file.\n");
    exit(0);
  }
  ft = fopen("output.txt","w");
  if (ft == NULL){
    printf("Could not open output file.\n");
    fclose(fs);
    exit(0);
  }
  struct BT *myset;
  myset = initialise();
  char *str,*tmp;
  tmp = (char *)malloc(sizeof(char)*MAX);
  str = (char *)malloc(sizeof(char)*0);
  fscanf(fs," %[^\n]s",tmp);
  int i = 0,z = 0;
  while (i<strlen(tmp)){
    if((tmp[i] >= '0' && tmp[i]<='9') ||tmp[i] == ')' || tmp[i] == '('){
      z++;
      str = (char *)realloc(str,sizeof(char)*z);
      str[z-1] = tmp[i];
    }
    i++;
  }
  myset->root = create_tree(str,myset->root,1);
  setLevel(myset->root,0);
  fprintf(ft,"%d %d %d\n",height(myset->root),diameter(myset->root),maxwidth(myset->root));
  fclose(fs);
  fclose(ft);
  return 0;
}
