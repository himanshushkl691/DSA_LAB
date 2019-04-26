#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct dsu
{
	int parent[1000001];
	int rnk[1000001];
	int op;
};

struct dsu *initialise()
{
	struct dsu * n;
	n = (struct dsu *)malloc(sizeof(struct dsu));
	for (int i = 0;i<1000001;i++)
		n->parent[i] = 0;
	for (int i = 0;i<1000001;i++)
		n->rnk[i] = 0;
	n->op = 0;
	return n;
}

void MAKE_SET(struct dsu *h,int x)
{
	h->parent[x] = x;
	h->rnk[x] = 0;
}
//////////////////////////////////////
//PATH COMPRESSION AND UNION BY RANK//
//////////////////////////////////////
int FIND_SET_BOTH(struct dsu *h,int x)
{
	h->op++;
	if (!h->parent[x])
		return -1;
	if (x != h->parent[x])
		h->parent[x] = FIND_SET_BOTH(h,h->parent[x]);
	return h->parent[x];
}
int UNION_BOTH(struct dsu *h,int x,int y)
{
	int a = FIND_SET_BOTH(h,x);
	int b = FIND_SET_BOTH(h,y);
	if (a!=-1 && b!=-1 && a!=b)
	{
		if (h->rnk[a] < h->rnk[b])
		{
			h->parent[a] = b;
			return b;
		}
		else
		{
			h->parent[b] = a;
			if (h->rnk[a] == h->rnk[b])
				h->rnk[a]++;
			return a;
		}
	}
	else if (a!=-1 && b!=-1 && a==b)
		return a;
	else if(a==-1 || b==-1)
		return -1;
}
///////////////////////
//ONLY UNION BY RANK///
///////////////////////
int FIND_SET_RANK(struct dsu *h,int x)
{
	h->op++;
	if (!h->parent[x])
		return -1;
	while(x != h->parent[x])
	{
		h->op++;
		x = h->parent[x];
	}
	return x;
}
int UNION_RANK(struct dsu *h,int x,int y)
{
	int a = FIND_SET_RANK(h,x);
	int b = FIND_SET_RANK(h,y);
	if (a!=-1 && b!=-1 && a!=b)
	{
		if (h->rnk[a] < h->rnk[b])
		{
			h->parent[a] = b;
			return b;
		}
		else
		{
			h->parent[b] = a;
			if (h->rnk[a] == h->rnk[b])
				h->rnk[a]++;
			return a;
		}
	}
	else if (a!=-1 && b!=-1 && a==b)
		return a;
	else if (a==-1 || b==-1)
		return -1;
}
//////////////////////////
//ONLY PATH COMPRESSION///
//////////////////////////
int UNION_COMP(struct dsu *h,int x,int y)
{
	int a = FIND_SET_BOTH(h,x);
	int b = FIND_SET_BOTH(h,y);
	if (a!=-1 && b!=-1 && a!=b)
	{
		h->parent[b] = a;
		return a;
	}
	else if (a!=-1 && b!=-1 && a==b)
		return a;
	else if (a==-1 || b==-1)
		return -1;
}
//////////////////////
////NONE OF THE TWO///
//////////////////////
int FIND_SET_NONE(struct dsu *h,int x)
{
	h->op++;
	if (!h->parent[x])
		return -1;
	while(x != h->parent[x])
	{
		h->op++;
		x = h->parent[x];
	}
	return x;
}
int UNION_NONE(struct dsu *h,int x,int y)
{
	int a = FIND_SET_NONE(h,x);
	int b = FIND_SET_NONE(h,y);
	if (a!=-1 && b!=-1 && a!=b)
	{
		h->parent[b] = a;
		return a;
	}
	else if (a!=-1 && b!=-1 && a==b)
		return a;
	else if (a==-1 || b==-1)
		return -1;
}

int str_to_num(char *str,int i)
{
	int n = strlen(str);
	int numb = 0;
	while(i<n && str[i]>='0' && str[i]<='9')
	{
		numb = 10 * numb + (str[i] - '0');
		i++;
	}
	return numb;
}

int main()
{
	struct dsu *a,*b,*c,*d;
	a = initialise();
	b = initialise();
	c = initialise();
	d = initialise();
	FILE *fs,*ft;
	fs = fopen("input.txt","r");
	if(!fs)
	{
		printf("Could not open input file.\n");
		exit(0);
	}
	ft = fopen("output.txt","w");
	if(!ft)
	{
		printf("Could not open output file.\n");
		fclose(fs);
		exit(0);
	}
	char *str;
	str = (char *)malloc(sizeof(char) * 1000001);
	while(fscanf(fs," %[^\n]s",str) != EOF)
	{
		int x,y;
		if (str[0] == 'm')
		{
			x = str_to_num(str,2);
			if (!a->parent[x] && !b->parent[x] && !c->parent[x] && !d->parent[x])
			{
				fprintf(ft,"%d\n",x);
				MAKE_SET(a,x);
				MAKE_SET(b,x);
				MAKE_SET(c,x);
				MAKE_SET(d,x);
			}
			else
				fprintf(ft,"PRESENT\n");
		}
		else if (str[0] == 'f')
		{
			x = str_to_num(str,2);
			int check = FIND_SET_NONE(a,x);
			if (check != -1)
				fprintf(ft,"%d ",check);
			else
				fprintf(ft,"NOT FOUND ");
			check = FIND_SET_RANK(b,x);
			if(check != -1)
				fprintf(ft,"%d ",check);
			else
				fprintf(ft,"NOT FOUND ");
			check = FIND_SET_BOTH(c,x);
			if (check != -1)
				fprintf(ft,"%d ",check);
			else
				fprintf(ft,"NOT FOUND ");
			check = FIND_SET_BOTH(d,x);
			if (check != -1)
				fprintf(ft,"%d ",check);
			else
				fprintf(ft,"NOT FOUND");
			fprintf(ft,"\n");
		}
		else if (str[0] == 'u')
		{
			int x = str_to_num(str,2);
			int i = 2;
			while(i<strlen(str) && str[i]>='0' && str[i]<='9')
				i++;
			i++;
			int y = str_to_num(str,i);
			int check = UNION_NONE(a,x,y);
			if (check != -1)
				fprintf(ft,"%d ",check);
			else
				fprintf(ft,"ERROR ");
			check = UNION_RANK(b,x,y);
			if(check != -1)
				fprintf(ft,"%d ",check);
			else
				fprintf(ft,"ERROR ");
			check = UNION_COMP(c,x,y);
			if (check != -1)
				fprintf(ft,"%d ",check);
			else
				fprintf(ft,"ERROR ");
			check = UNION_BOTH(d,x,y);
			if (check != -1)
				fprintf(ft,"%d ",check);
			else
				fprintf(ft,"ERROR ");
			fprintf(ft,"\n");

		}
		else if (str[0] == 's')
		{
			fprintf(ft,"%d %d %d %d\n",a->op,b->op,c->op,d->op);	
			return 0;
		}
	}
	return 0;
}
