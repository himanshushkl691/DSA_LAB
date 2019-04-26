#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <limits.h>
#define MAX 10000001

int min(int a,int b){
  return ((a>b)?b:a);
}

int max(int a,int b){
  return ((a>b)?a:b);
}

int tournament_tree_util(int *tournament,int *arr,int idx,int s,int e){
  if (s == e){
    tournament[idx] = arr[s];
    return arr[s];
  }
  int mid = (s + e)>>1;
  tournament[idx] = min(tournament_tree_util(tournament,arr,2 * idx + 1,s,mid),tournament_tree_util(tournament,arr,2 * idx + 2,mid+1,e));
  return tournament[idx];
}

void tournament_tree(int *arr,int n,FILE *ft)
{
  int size = 2 * n - 1;
  int *tournament;
  tournament = (int *)malloc(sizeof(int)*size);
  tournament_tree_util(tournament,arr,0,0,n-1);//builds tournament tree
  //print_array(tournament,size);
  //print second largest
  int idx = 0,mn = INT_MAX,root = tournament[0];
  int i = 0;
  while (i < 2 && idx < size - n){
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
    if (left < size && tournament[left] == root){
      idx = left;
      if (right < size)
	mn = tournament[right];
    }
    if (right < size && tournament[right] == root){
      idx = right;
      if (left < size)
	mn = tournament[left];
    }
    i++;
  }
  if(mn == INT_MAX)
    fprintf(ft,"%d\n",tournament[0]);
  else
    fprintf(ft,"%d\n",mn);
}

void print_array(int *arr,int n){
  for (int i = 0;i<n;i++){
    printf("%d ",arr[i]);
  }
  printf("\n");
}

void solve(char *str,FILE *ft)
{
  int n = strlen(str);
  int *res;
  int z = 0;
  res = (int*)malloc(sizeof(int)*0);
  for(int i = 0;i<n;i++){
    if (str[i]>='0' && str[i]<='9'){
      int num = 0;
      while (str[i]>='0' && str[i]<='9'){
	num = num * 10 + (str[i]-'0');
	i++;
      }
      i--;
      z++;
      res = (int *)realloc(res,sizeof(int)*z);
      res[z-1] = num;
    }
  }
  tournament_tree(res,z,ft);
}

int main()
{
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
  char *str;
  str = (char *)malloc(sizeof(char)*MAX);
  while(fscanf(fs," %[^\n]s",str)!=EOF)
    solve(str,ft);
  return 0;
}
