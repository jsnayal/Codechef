// C program to insert_avl a node in AVL tree
#include<bits/stdc++.h>

// An AVL tree node

void fastscan(long int &number)
{
    //variable to indicate sign of input number
    bool negative = false;
    register long int c;

    number = 0;

    // extract current character from buffer
    c = getchar();
    if (c=='-')
    {
        // number is negative
        negative = true;

        // extract the next character from the buffer
        c = getchar();
    }

    // Keep on extracting characters if they are integers
    // i.e ASCII Value lies from '0'(48) to '9' (57)
    for (; (c>47 && c<58); c=getchar())
        number = number *10 + c - 48;

    // if scanned input has a negative sign, negate the
    // value of the input number
    if (negative)
        number *= -1;
}



struct node
{
    long int key;
    struct node *left;
    struct node *right;
    long int height;
    long int countn;
};

// A utility function to get maximum of two integers
long int maxm(long int a, long int b);

// A utility function to get height of the tree
long int height(struct node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

// A utility function to get maximum of two integers
long int maxm(long int a, long int b)
{
    return (a > b)? a : b;
}

/* Helper function that allocates a new node with the given key and
    NULL left and right pointers. */
struct node* newNode(long int key)
{
    struct node* node = (struct node*)
                        malloc(sizeof(struct node));
    node->key   = key;
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1;  // new node is initially added at leaf
    node->countn = 1;
    return(node);
}

// A utility function to right rotate subtree rooted with y
// See the diagram given above.
struct node *rightRotate(struct node *y)
{
    struct node *x = y->left;
    struct node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = maxm(height(y->left), height(y->right))+1;
    x->height = maxm(height(x->left), height(x->right))+1;

    // Return new root
    return x;
}

// A utility function to left rotate subtree rooted with x
// See the diagram given above.
struct node *leftRotate(struct node *x)
{
    struct node *y = x->right;
    struct node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    //  Update heights
    x->height = maxm(height(x->left), height(x->right))+1;
    y->height = maxm(height(y->left), height(y->right))+1;

    // Return new root
    return y;
}

// Get Balance factor of node N
long int getBalance(struct node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

struct node* insert_avl(struct node* node, long int key)
{
    /* 1.  Perform the normal BST rotation */
    if (node == NULL)
        return (newNode(key));

    // If key already exists in BST, icnrement count and return
    if (key == node->key)
    {
        (node->countn)++;
        return node;
    }

     /* Otherwise, recur down the tree */
    if (key < node->key)
        node->left  = insert_avl(node->left, key);
    else
        node->right = insert_avl(node->right, key);

    /* 2. Update height of this ancestor node */
    node->height = maxm(height(node->left), height(node->right)) + 1;

    /* 3. Get the balance factor of this ancestor node to check whether
       this node became unbalanced */
    long int balance = getBalance(node);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    /* return the (unchanged) node pointer */
    return node;
}

/* Given a non-empty binary search tree, return the node with minimum
   key value found in that tree. Note that the entire tree does not
   need to be searched. */
struct node * minValueNode(struct node* node)
{
    struct node* current = node;

    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;

    return current;
}

struct node* deleteNode(struct node* root, long int key)
{
    // STEP 1: PERFORM STANDARD BST DELETE

    if (root == NULL)
        return root;

    // If the key to be deleted is smaller than the root's key,
    // then it lies in left subtree
    if ( key < root->key )
        root->left = deleteNode(root->left, key);

    // If the key to be deleted is greater than the root's key,
    // then it lies in right subtree
    else if( key > root->key )
        root->right = deleteNode(root->right, key);

    // if key is same as root's key, then This is the node
    // to be deleted
    else
    {
        // If key is present more than once, simply decrement
        // count and return
        if (root->countn > 1)
        {
            (root->countn)--;
            return root;
        }
        // ElSE, delete the node

        // node with only one child or no child
        if( (root->left == NULL) || (root->right == NULL) )
        {
            struct node *temp = root->left ? root->left : root->right;

            // No child case
            if(temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else // One child case
             *root = *temp; // Copy the contents of the non-empty child

            free(temp);
        }
        else
        {
            // node with two children: Get the inorder successor (smallest
            // in the right subtree)
            struct node* temp = minValueNode(root->right);

            // Copy the inorder successor's data to this node
            root->key = temp->key;

            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->key);
        }
    }

    // If the tree had only one node then return
    if (root == NULL)
      return root;

    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root->height = maxm(height(root->left), height(root->right)) + 1;

    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to check whether
    //  this node became unbalanced)
    long int balance = getBalance(root);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left =  leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// A utility function to print preorder traversal of the tree.
// The function also prints height of every node
void preOrder(struct node *root)
{
    if(root != NULL)
    {
        printf("%ld(%ld) ", root->key, root->countn);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void down(long int *x, long int N)
{
    if((*x) >0)
    (*x)= (*x)-1;
    else
    (*x)=N-1;
}

void up(long int *x, long int N)
{
    if((*x) < N-1)
    (*x)= (*x)+1;
    else
    (*x)=0;
}


long int find_max(struct node *root)
{
    struct node *temp=root;
    while(temp->right !=NULL)
    {
        temp=temp->right;
    }
    return temp->key;
}

/* Drier program to test above function*/
int main()
{
    long int N,K,P;
//    scanf("%ld%ld%ld",&N,&K,&P);
    fastscan(N);
    fastscan(K);
    fastscan(P);
    long int A[100005];

    for(long int i=0;i<N;i++)
    {
        fastscan(A[i]);
    }

    long int no_of_ones[100005];

    long int startn,endn;
    long int o=0;

    endn=N-1;
    startn=endn-K+1;

    long int end_temp=endn;
    long int start_temp=startn;

    while(1)
    {
        long int ones=0;
        for(long int i=end_temp;i!=start_temp; )
        {
            ones+=A[i];
            down(&i,N);
        }
        ones+=A[start_temp];


        no_of_ones[o++]=ones;

        down(&start_temp,N);
        down(&end_temp,N);

        if(start_temp==startn && end_temp==endn)
        break;
    }
    /*for(int i=0;i<o;i++)
    {
        printf("%ld ",no_of_ones[i]);
    }
    printf("\n");*/
    //Calculating max ones for each shift to right

    struct node *root = NULL;

    long int max_ones_on_shift[100005];
    long int M;
    M=0;

    long int window_size=N-K+1;

    for(long int i=0;i<window_size;i++)
    {
        root = insert_avl(root,no_of_ones[i]);
    }

    long int maxn;

    maxn=find_max(root);
    max_ones_on_shift[M++]=maxn;

    //printf("M=%ld\n",M);
    startn=0;
    endn=N-K;
//printf("startn=%ld endn=%ld\n",startn,endn);
    start_temp=startn;
    end_temp=endn;

    while(1)
    {
        root=deleteNode(root,no_of_ones[start_temp]);

        long int end_temp_inc;

        if(end_temp==N-1)
        end_temp_inc=0;
        else
        end_temp_inc=end_temp+1;

        root=insert_avl(root,no_of_ones[end_temp_inc]);

        maxn=find_max(root);

        max_ones_on_shift[M++]=maxn;

//        printf("MAXN=%ld M=%ld\n",maxn,M);
        up(&start_temp,N);
        up(&end_temp,N);

        if(start_temp==startn && end_temp==endn)
        break;
    }

//printf("M=%ld\n",M);
/*    for(int i=0;i<M-1;i++)
    {
        printf("%ld ",max_ones_on_shift[i]);
    }*/


    char ch[100005];
    scanf("%s",ch);

    long int count_trans=0;
    for(long int i=0;ch[i]!='\0';i++)
    {
        if(ch[i]=='?')
        {
            printf("%ld\n",max_ones_on_shift[count_trans]);
        }
        else
        {
            count_trans++;
            if(count_trans>N-1)
            count_trans=0;
        }
    }
  return 0;
}
