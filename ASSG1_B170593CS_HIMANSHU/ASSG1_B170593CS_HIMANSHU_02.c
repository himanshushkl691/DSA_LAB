#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define upto(i,a,b,inc) for(int i = a;i<=b;i += inc)
#define downto(i,a,b,dec) for(int i = a;i>=b;i-=dec)
#define INF 1000000007
#define MAX 1000001

struct plate{
  char data;
  struct plate *link;
};

struct stack{
  int size;
  struct plate *top;
};

struct plate *create(char item){
  struct plate *n;
  n = (struct plate *)malloc(sizeof(struct plate));
  n->data = item;
  n->link = NULL;
  return n;
}

struct stack *initialise(){
  struct stack *n;
  n = (struct stack *)malloc(sizeof(struct stack));
  n->top = NULL;
  n->size = 0;
  return n;
}

int empty(struct stack *stk){
  return (stk->size == 0);
}

void push(struct stack *stk,char ch){
  struct plate *n;
  n = create(ch);
  if (!stk->top)
    stk->top = n;
  else{
    n->link = stk->top;
    stk->top = n;
  }
  stk->size++;
}

struct plate *pop(struct stack *stk){
  if (!empty(stk)){
    struct plate *res,*curr;
    res = stk->top;
    stk->top = res->link;
    stk->size--;
    return res;
  }
  else
    return stk->top;
}

char *append(char *str,char ch){
  int idx = strlen(str)+1;
  str = (char *)realloc(str,sizeof(char)*idx);
  str[idx-1] = ch;
  return str;
}

int precedence(char op0){
  if (op0 == '*' || op0 == '/')
    return 2;
  else if (op0 == '+' || op0 == '-')
    return 1;
  else if (op0 == '^')
    return 0;
}

void infixToPostfix(char *res,struct stack *stk,char *str){
  int i = 0;
  while (i<strlen(str) && str[i] != '\n'){
    char ch = str[i];
    if (ch >= 'a' && ch <='z'){
      res = append(res,ch);
    }
    else if (ch == '(')
      push(stk,ch);
    else if (ch == ')'){
      while (!empty(stk)){
	char tmp = pop(stk)->data;
	if (tmp != ')' && tmp != '(')
	 res = append(res,tmp);
	else if (tmp == '('){
	  break;
	}
      }
    }
    else if (ch == '*' || ch == '+' || ch == '-' || ch == '/' || ch == '^'){
      while (!empty(stk) && precedence(ch) <= precedence(stk->top->data) && stk->top->data != '(')
	res = append(res,pop(stk)->data);
      push(stk,ch);
    }
    i++;
  }
  while (!empty(stk)){
    res = append(res,pop(stk)->data);
  }
}

void Print(char *str,FILE *ft){
  fprintf(ft,"%s\n",str);
}

int main(){
  FILE *fs,*ft;
  fs = fopen("input.txt","r");
  if (fs == NULL){
    printf("Could not open input file\n");
    exit(0);
  }
  ft = fopen("output.txt","w");
  if (ft == NULL){
    printf("Could not open output file\n");
    fclose(fs);
    exit(0);
  }
  struct stack *stk;
  stk = initialise();
  char *str,*res;
  str = (char *)malloc(sizeof(char)*MAX);
  while (fscanf(fs," %[^\n]s",str) !=EOF){
    res = (char *)malloc(sizeof(char)*0);
    infixToPostfix(res,stk,str);
    Print(res,ft);
    free(str);
    str = (char *)malloc(sizeof(char)*MAX);
  }
  return 0;
}
