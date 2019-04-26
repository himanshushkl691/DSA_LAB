#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#define and &&
#define or ||
#define not !
#define RED 0
#define BLACK 1

int max(int a,int b)
{
    return ((a>b)?a:b);
}

struct t_node
{
    int item;
    int color;
    struct t_node *left,*right,*parent;
};

struct RBT
{
    struct t_node *root;
};

struct t_node *create(int item)
{
    struct t_node *n;
    n = (struct t_node *)malloc(sizeof(struct t_node));
    n->color = RED;
    n->item = item;
    n->left = n->right = n->parent = NULL;
    return n;
}

struct RBT *initialise()
{
    struct RBT *h;
    h = (struct RBT *)malloc(sizeof(struct RBT));
    h->root = NULL;
    return h;
}

struct t_node *leftRotate(struct t_node *x)
{
    struct t_node *y,*z;
    y = x->right;
    z = NULL;
    if (y)
    {
        z = y->right;
        y->parent = x->parent;
        x->right = y->left;
        if (y->left)
            y->left->parent = x;
        y->left = x;
        x->parent = y;
    }
    return y;
}

struct t_node *rightRotate(struct t_node *x)
{
    struct t_node *y,*z;
    y = x->left;
    z = NULL;
    if(y)
    {
        z = y->left;
        x->left = y->right;
        y->parent = x->parent;
        if (y->right)
            y->right->parent = x;
        x->parent = y;
        y->right = x;
    }
    return y;
}

void inorder(struct t_node *root,FILE *ft)
{
    if (root)
    {
        if(root->left)
        {
            fprintf(ft,"(");
            inorder(root->left,ft);
            fprintf(ft,")");
        }
        if(root->color == RED)
            fprintf(ft,"%dR",root->item);
        if(root->color == BLACK)
            fprintf(ft,"%dB",root->item);
        if(root->right)
        {
            fprintf(ft,"(");
            inorder(root->right,ft);
	        fprintf(ft,")");
        }
    }
}

struct t_node *RBT_FixUp(struct t_node *root,struct t_node *curr,FILE *ft)
{
    int flag = 0;
    while(curr->parent && curr->parent->color == RED)
    {
        flag = 1;
        if(curr->parent == curr->parent->parent->left)
        {
            struct t_node *y = curr->parent->parent->right;
            if(y && y->color == RED)
            {
                curr->parent->color = BLACK;
                y->color = BLACK;
                curr->parent->parent->color = RED;
                curr = curr->parent->parent;
            }
            else
            {
                if(curr == curr->parent->right)
                {
                    curr->parent->parent->left = leftRotate(curr->parent);
                    curr = curr->left;
                }
                curr->parent->color = BLACK;
                curr->color = RED;
                curr->parent->parent->color = RED;
                if(curr->parent->parent->parent)
                {
                    if(curr->parent->parent == curr->parent->parent->parent->left)
                        curr->parent->parent->parent->left = rightRotate(curr->parent->parent);
                    else
                        curr->parent->parent->parent->right = rightRotate(curr->parent->parent);
                }
                else
                    root = rightRotate(curr->parent->parent);
            }
        }
        else if(curr->parent == curr->parent->parent->right)
        {
            struct t_node *y = curr->parent->parent->left;
            if(y && y->color == RED)
            {
                curr->parent->color = BLACK;
                y->color = BLACK;
                curr->parent->parent->color = RED;
                curr = curr->parent->parent;
            }
            else
            {
                if(curr == curr->parent->left)
                {
                    curr->parent->parent->right = rightRotate(curr->parent);
                    curr = curr->right;
                }
                curr->parent->color = BLACK;
                curr->color = RED;
                curr->parent->parent->color = RED;
                if(curr->parent->parent->parent)
                {
                    if(curr->parent->parent == curr->parent->parent->parent->left)
                        curr->parent->parent->parent->left = leftRotate(curr->parent->parent);
                    else
                        curr->parent->parent->parent->right = leftRotate(curr->parent->parent);
                }
                else
                    root = leftRotate(curr->parent->parent);
            }
        }
    }
    root->color = BLACK;
    if(flag)
    {
        fprintf(ft,"(");
        inorder(root,ft);
        fprintf(ft,")\n");
    }    
    return root;
}

struct t_node *insert(struct t_node *root,int item,FILE *ft)
{
    struct t_node *newnode = create(item);
    if (!root)
    {
        root = newnode;
        root->color = BLACK;
        fprintf(ft,"(");
        inorder(root,ft);
        fprintf(ft,")\n");
        return root;
    }
    else
    {
        struct t_node *curr;
        curr = root;
        while(curr)
        {
            if (curr->item == item)
                return root;
            else if (curr->item < item)
            {
                if (curr->right)
                    curr = curr->right;
                else
                {
                    curr->right = newnode;
                    newnode->parent = curr;
                    break;
                }
            }
            else
            {
                if (curr->left)
                    curr = curr->left;
                else
                {
                    curr->left = newnode;
                    newnode->parent = curr;
                    break;
                }
            }        
        }
        fprintf(ft,"(");
        inorder(root,ft);
        fprintf(ft,")\n");
        root = RBT_FixUp(root,newnode,ft);
    }
    return root;
}

struct t_node *search(struct t_node *root,int key)
{
    if (!root)
        return NULL;
    if (root->item == key)
        return root;
    if (root->item > key)
        return search(root->left,key);
    if (root->item < key)
        return search(root->right,key);
}

int main()
{
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
    struct RBT *myset = initialise();
    int item;
    while(fscanf(fs,"%d",&item) != EOF)
        myset->root = insert(myset->root,item,ft);
    return 0;
}
