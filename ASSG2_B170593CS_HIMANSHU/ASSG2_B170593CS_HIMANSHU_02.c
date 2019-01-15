#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <string.h>
#define MAX 1000001
#define mod 1051

int power[MAX];

void buildPowers()
{
  power[0] = 1;
  for (int i = 1;i<MAX;i++) power[i] = (power[i-1]%mod * 256)%mod;
}

int hash(char *str,int n)
{
  int res = 0;
  for (int i = 0 ;i<n;i++)
    res += (power[n-i-1]%mod * (str[i])%mod)%mod;
  return res%mod;
}

int nexthash(char *s,int t,int idx,int m)
{
  int res = ((256%mod * (mod + t%mod - (power[m-1]%mod * (s[idx])%mod)%mod)%mod)%mod + (s[m+idx])%mod)%mod;
  return res;
}

void RKM(char *pat,char *txt,FILE *ft)
{
  int n = strlen(txt);
  int m = strlen(pat);
  int hash_text = hash(txt,m);
  int hash_pattern = hash(pat,m);
  int not_found = 1;
  if (hash_text == hash_pattern)
    {
      not_found = 0;
      fprintf(ft,"0 ");
    }
  for (int i = 1;i<=(n-m);i++)
    {
      hash_text = nexthash(txt,hash_text,i-1,m);
      if (hash_text == hash_pattern)
	{
	  int z = i;
	  int flag = 0;
	  for (int j = 0;j<m;j++,z++)
	    {
	      if (txt[z] != pat[j])
		{
		  flag = 1;
		  break;
		}
	    }
	  if (!flag)
	    {
	      not_found = 0;
	      fprintf(ft,"%d ",i);
	    }
	}
    }
  if (not_found)
    fprintf(ft,"-1");
  fprintf(ft,"\n");
}

char * text(char *str,int l,int r)
{
  char *res;
  res = (char *)malloc(sizeof(char)*MAX);
  int z = 0;
  for (int i = l;i<r;i++)
    {
       z++;
      res = (char *)realloc(res,sizeof(char)*z);
      res[z-1] = str[i];
    }
  return res;
}

char *pattern(char *str,int l,int r)
{
  char *res;
  res = (char *)malloc(sizeof(char)*0);
  int z = 0;
  for (int i = l;i<r;i++)
    {
      z++;
      res = (char *)realloc(res,sizeof(char)*z);
      res[z-1] = str[i];
    }
  return res;
}

void print(char *pat,char *txt,FILE *ft)
{
  RKM(pat,txt,ft);
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
  buildPowers();
  char *str,*pat,*txt;
  str = (char *)malloc(sizeof(char)*MAX);
  while (fscanf(fs," %[^\n]s",str) !=EOF)
    {
      if (str[0] == 'e')
	{
	  return 0;
	}
      else if (str[0] == 't')
	{
	  txt = text(str,3,strlen(str)-1);
	}
      else if (strcmp(str,"pr") == 0)
	{
	  print(pat,txt,ft);
	}
      else if (str[0] == 'p')
	{
	  pat = pattern(str,3,strlen(str)-1);
	}
      str = (char *)malloc(sizeof(char)*MAX);
    }
}
