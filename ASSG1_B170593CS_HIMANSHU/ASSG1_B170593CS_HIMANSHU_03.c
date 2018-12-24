#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef long long ll;
#define upto(i,a,b,inc) for(int i = a;i<=b;i+=inc)
#define downto(i,a,b,dec) for(int i = a;i>=b;i-=dec)
#define MAX 10000001
#define INF 1000000007
#define br printf("\n")

struct plate{
	int data;
	struct plate *link;
};

struct stack{
	int size;
	struct plate *top;
};

struct plate *create(int item)
{
	struct plate *n;
	n = (struct plate *)malloc(sizeof(struct plate));
	n->data = item;
	n->link = NULL;
	return n;
}

struct stack *initialise()
{
	struct stack *n;
	n = (struct stack *)malloc(sizeof(struct stack));
	n->top = NULL;
	n->size = 0;
	return n;
}

int empty(struct stack *h)
{
	return (h->size == 0);
}

int top(struct stack *h)
{
	return (h->top->data);
}

void push(struct stack* h,int item)
{
	struct plate *n;
	n = create(item);
	if (h->top == NULL)
		h->top = n;
	else
	{
		n->link = h->top;
		h->top = n;
	}
	h->size++;
}

struct plate *pop(struct stack *h)
{
	if (!empty(h))
	{
		struct plate *curr;
		curr = h->top;
		h->top = curr->link;
		h->size--;
		return curr;
	}
	else
		return h->top;
}

int exception = 0;
void evaluatePostfix(struct stack *stk,char *str){
  int i = 0;
  while (i<strlen(str) && str[i] != '\n'){
    char ch = str[i];
    if (ch != ' ' && ch >= '0' && ch <= '9'){
      int numb = 0;
      while (ch >= '0' && ch <= '9'){
	numb = (10 * numb) + (ch - '0');
	i++;
	ch = str[i];
      }
      i--;
      push(stk,numb);
    }
    else if (ch != ' '){
      int b = pop(stk)->data;
      int a = pop(stk)->data;
      if (ch == '+')
	push(stk,a+b);
      else if (ch == '-')
	push(stk,a-b);
      else if (ch == '*')
	push(stk,a*b);
      else if (ch == '/'){
	if (b == 0){
	  exception = 1;
	  break;
	}
	push(stk,a/b);
      }
      else if (ch == '^')
	push(stk,a^b);
    }
    i++;
  }
}

int Print(struct stack *stk){
  int a = pop(stk)->data;
  return a;
}

int main()
{
	struct stack *stk;
	stk = initialise();
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
		exit(0);
	}
	char *str;
	str = (char *)malloc(sizeof(char)*MAX);
	int flag = 0;
	while (fscanf(fs," %[^\n]s",str)!= EOF){
	  exception = 0;
	  evaluatePostfix(stk,str);
	  if (exception){
	    while (!empty(stk))
	      pop(stk);
	    fprintf(ft,"INVALID INPUT\n");
	  }
	  else
	    fprintf(ft,"%d\n",Print(stk));
	  free(str);
	  str = (char *)malloc(sizeof(char)*MAX);
	}
	fclose(fs);
	fclose(ft);
}
