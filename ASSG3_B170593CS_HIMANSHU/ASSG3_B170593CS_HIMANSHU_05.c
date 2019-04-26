#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct vector
{
	int *arr;
	int capacity;
	int size;
};

struct vector *initialise()
{
	struct vector *n;
	n = (struct vector *)malloc(sizeof(struct vector));
	n->size = 0;
	n->capacity = 2;
	n->arr = (int *)malloc(sizeof(int) * (n->capacity));
	return n;
}

struct vector *Append(struct vector *h,int x)
{
	if (h->size == h->capacity)
	{
		int *new_array = (int *)malloc(sizeof(int) * (2 * h->capacity));
		for (int i = 0;i<h->size;i++)
			new_array[i] = h->arr[i];
		h->capacity = 2 * (h->capacity);
		h->arr = new_array;
	}
	h->arr[h->size] = x;
	h->size++;
	return h;
}

struct vector *Concatenate(struct vector *a,struct vector *b)
{
	for (int i = 0;i<b->size;i++)
		a = Append(a,b->arr[i]);
	return a;
}

int Member(struct vector *h,int x)
{
	for (int i = 0;i<h->size;i++)
	{
		if (x == h->arr[i])
			return 1;
	}
	return 0;
}

int Length(struct vector *h)
{
	return h->size;
}

void Slice(struct vector *h,int a,int b,FILE *ft)
{
	if ((a-1)>=0 && (a-1)<(h->size) && (b-1)>=0 && (b-1)<(h->size))
	{
		for (int i = a-1;i<=b-1;i++)
			fprintf(ft,"%d ",h->arr[i]);
		fprintf(ft,"\n");
	}
}

void Print(struct vector *h,FILE *ft)
{
	for(int i = 0;i<1 && i<h->size;i++)
		fprintf(ft,"(%d",h->arr[i]);
	for (int i = 1;i<h->size;i++)
		fprintf(ft," %d",h->arr[i]);
	fprintf(ft,")\n");
}

struct vector *str_to_array(struct vector *myarr,char *str,int i)
{
	struct vector *newh;
	newh = initialise();
	int n = strlen(str);
	while(i<n && str[i]!=')')
	{
		if (str[i]>='0' && str[i]<='9')
		{
			int numb = 0;
			while(i<n && str[i]>='0' && str[i]<='9')
			{
				numb = 10 * numb + (str[i] - '0');
				i++;
			}
			newh = Append(newh,numb);
			continue;
		}
		i++;
	}
	return newh;
}

int str_to_numb(char *str,int i)
{
	int n = strlen(str),numb = 0;
	while(i<n && str[i]>='0' && str[i]<='9')
	{
		numb = 10 * numb + (str[i] - '0');
		i++;
	}
	return numb;
}

int main()
{
	struct vector *myarr;
	myarr = initialise();
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
		printf("Could not open ouput file.\n");
		fclose(fs);
		exit(0);
	}
	char *str;
	str = (char *)malloc(sizeof(char) * 1000001);
	while(fscanf(fs," %[^\n]s",str) != EOF)
	{
		if (str[0] == 'a')
		{
			myarr = initialise();
			myarr = str_to_array(myarr,str,2);
			int i = 0;
			while(i<strlen(str) && str[i]!=')')
				i++;
			i++;
			myarr = Append(myarr,str_to_numb(str,i+1));
			Print(myarr,ft);
		}
		else if (str[0] == 'c')
		{
			struct vector *myarr0,*myarr1;
			myarr0 = initialise();
			myarr1 = initialise();
			myarr0 = str_to_array(myarr0,str,2);
			int i = 0;
			while(i<strlen(str) && str[i]!=')')
				i++;
			i++;
			myarr1 = str_to_array(myarr1,str,i+1);
			myarr = initialise();
			myarr = Concatenate(myarr0,myarr1);
			Print(myarr,ft);
		}
		else if (str[0] == 'm')
		{
			myarr = initialise();
			myarr = str_to_array(myarr,str,2);
			int i = 0;
			while(i<strlen(str) && str[i]!=')')
				i++;
			i++;
			int key = str_to_numb(str,i+1),flag = 0;
			for (int i = 0;i<myarr->size;i++)
				if(myarr->arr[i] == key)
				{
					flag = 1;
					fprintf(ft,"1\n");
					break;
				}
			if(!flag)
				fprintf(ft,"0\n");
		}
		else if(str[0] == 'l')
		{
			myarr = initialise();
			myarr = str_to_array(myarr,str,2);
			fprintf(ft,"%d\n",Length(myarr));			
		}
		else if(str[0] == 's')
		{
			myarr = initialise();
			myarr = str_to_array(myarr,str,2);
			int i = 0;
			while(i<strlen(str) && str[i]!=')')
				i++;
			i++;
			int a = str_to_numb(str,i+1);
			i++;
			while(i<strlen(str) && str[i]>='0' && str[i]<='9')
				i++;
			i++;
			int b = str_to_numb(str,i);
			Slice(myarr,a,b,ft);
		}
		else if(str[0] == 'x')
			return 0;
	}
}
