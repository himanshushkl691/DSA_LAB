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

void swap(struct node **tmp0,struct node **tmp1){
  struct node *tmp;
  tmp = *tmp0;
  *tmp0 = *tmp1;
  *tmp1 = tmp;
}

struct node *mirror(struct node *root){
  if (root){
    root->left = mirror(root->left);
    root->right = mirror(root->right);
    swap(&root->left,&root->right);
  }
  return root;
}

void setLevel(struct node *root,int l){
  if (root){
    setLevel(root->left,l+1);
    root->level = l;
    setLevel(root->right,l+1);
  }
}

void print_tree(struct node *root){
  if (root){
    printf("%d(",root->data);
    print_tree(root->left);
    printf(")(");
    print_tree(root->right);
    printf(")");
  }
}

int main(){
  struct BT *myset;
  myset = initialise();
  char ch;
  scanf("%c",&ch);
  //c create_tree(str,node*,si)
  //p print_tree(node *)
  //m mirror(node *)
  //s terminate
  while(1){
    if (ch == 's'){
      printf("\n");
      break;
    }
    else if(ch == 'c'){
      char *str;
      str = (char *)malloc(sizeof(char)*MAX);
      scanf(" %[^\n]s",str);
      char *tmp;
      tmp = (char *)malloc(sizeof(char)*0);
      int size = strlen(str),zidx = 0;
      for (int i = 0;i<size;i++){
	if (str[i] != ' ' && str[i] != '\n'){
	zidx++;
	tmp = (char *)realloc(tmp,sizeof(char)*zidx);
	tmp[zidx - 1] = str[i];
	}
      }
      myset = initialise();
      myset->root = create_tree(tmp,myset->root,1);
    }
    else if (ch == 'p'){
      print_tree(myset->root);
      br;
    }
    else if (ch == 'm'){
      myset->root = mirror(myset->root);
    }
    scanf("%c",&ch);
  }
  return 0;
}
