#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//MERGE SORT
void Merge(int *arr,int l,int mid,int r)
{
    int *a,*b;
    int sizea = mid - l + 1;
    int sizeb = r - mid;
    a = (int *)malloc(sizeof(int)*sizea);
    b = (int *)malloc(sizeof(int)*sizeb);
    int idx = 0;
    for (int i = l;i<=mid;i++)
        a[idx++] = arr[i];
    idx = 0;
    for(int i = mid + 1;i<=r;i++)
        b[idx++] = arr[i];
    int i = 0,j = 0;
    idx = l;
    while(i<sizea && j<sizeb)
    {
        if(a[i] < b[j])
            arr[idx++] = a[i],i++;
        else
            arr[idx++] = b[j],j++;
    }
    if(i<sizea)
       while(i<sizea)
            arr[idx++] = a[i],i++;
    if(j<sizeb)
        while(j<sizeb)
            arr[idx++] = b[j],j++;
}
void MergeSort(int *arr,int l,int r)
{
    if(l<r)
    {
        int mid = (l+r)>>1;
        MergeSort(arr,l,mid);
        MergeSort(arr,mid+1,r);
        Merge(arr,l,mid,r);
    }
}
//MERGE SORT END

//BINARY SEARCH
int BinarySearch(int *arr,int n,int key)
{
    int l = 0,r = n;
    while((r-l)>1)
    {
        int mid = (l + r)>>1;
        if(key>=arr[mid])
            l = mid;
        else
            r = mid;
    }
    if(arr[l] == key)
        return l;
    else
        return -1;
}
//BINARY SEARCH END

//VECTOR DEFINITION
struct vector
{
	int *arr;
	int capacity;
	int size;
};

struct vector *initialise_vector()
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
//VECTOR DEFINITION END

/////////////////////////
//DYNAMIC BINARY SEARCH//
/////////////////////////
struct DBS
{
    struct vector *arr[32];
    int size;
};

struct DBS *initialise_dbs()
{
    struct DBS *mydbs;
    mydbs = (struct DBS *)malloc(sizeof(struct DBS));
    mydbs->size = 0;
    for(int i = 0;i<32;i++)
        mydbs->arr[i] = initialise_vector();
    return mydbs;
}

struct DBS *Insert(struct DBS *h,int item)
{
    h->size++;
    int right_bit = 0;
    for(int z = 0;z<32;z++)
    {
        if((h->size)&(1<<z))
        {
            right_bit = z;
            break;
        }
    }
    struct vector *a;
    a = initialise_vector();
    a = Append(a,item);
    for(int i = 0;i<right_bit;i++)
    {
        for(int j = 0;j<(h->arr[i]->size);j++)
            a = Append(a,h->arr[i]->arr[j]);
        h->arr[i] = initialise_vector();
    }
    MergeSort(a->arr,0,a->size-1);
    h->arr[right_bit] = a;
    return h;
}

int Search(struct DBS *mydbs,int k)
{
    int idx = -1;
    for(int i = 0;i<32;i++)
    {
        if(mydbs->arr[i]->size)
        {
            idx = BinarySearch(mydbs->arr[i]->arr,mydbs->arr[i]->size,k);
            if(idx != -1)
                break;
        }
    }
    if(idx!=-1)
        return idx;
    else
        return -1;
}

void PrintDBS(struct DBS *h,FILE *ft)
{
    for(int i = 0;i<32;i++)
    {
        if(h->arr[i]->size)
        {
            for(int j = 0;j<h->arr[i]->size;j++)
                fprintf(ft,"%d ",h->arr[i]->arr[j]);
        }
    }
    fprintf(ft,"\n");
}
/////////////////////////////
//DYNAMIC BINARY SEARCH END//
/////////////////////////////

int main()
{
    struct DBS *mydbs;
    mydbs = initialise_dbs();
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
    char ch;
    while(fscanf(fs,"%c",&ch) != EOF)
    {
        int x;
        if(ch == 'x')
            return 0;
        else if(ch == 'i')
        {
            fscanf(fs,"%d",&x);
            mydbs = Insert(mydbs,x);
        }
        else if(ch == 'p')
        {
            PrintDBS(mydbs,ft);
        }
        else if (ch == 's')
        {
            fscanf(fs,"%d",&x);
            int idx = Search(mydbs,x);
            if(idx != -1)
                fprintf(ft,"%d\n",idx+1);
            else
                fprintf(ft,"NIL\n");
        }
    }
    return 0;
}