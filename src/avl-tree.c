/*
https://www.geeksforgeeks.org/avl-tree-set-1-insertion/
https://www.geeksforgeeks.org/avl-tree-set-2-deletion/

a) Left Left Case
T1, T2, T3 and T4 are subtrees.
         z                                      y
        / \                                   /   \
       y   T4      Right Rotate (z)          x      z
      / \          - - - - - - - - ->      /  \    /  \ 
     x   T3                               T1  T2  T3  T4
    / \
  T1   T2

b) Left Right Case
     z                               z                           x
    / \                            /   \                        /  \ 
   y   T4  Left Rotate (y)        x    T4  Right Rotate(z)    y      z
  / \      - - - - - - - - ->    /  \      - - - - - - - ->  / \    / \
T1   x                          y    T3                    T1  T2 T3  T4
    / \                        / \
  T2   T3                    T1   T2

c) Right Right Case
  z                                y
 /  \                            /   \ 
T1   y     Left Rotate(z)       z      x
    /  \   - - - - - - - ->    / \    / \
   T2   x                     T1  T2 T3  T4
       / \
     T3  T4

d) Right Left Case
   z                            z                            x
  / \                          / \                          /  \ 
T1   y   Right Rotate (y)    T1   x      Left Rotate(z)   z      y
    / \  - - - - - - - - ->     /  \   - - - - - - - ->  / \    / \
   x   T4                      T2   y                  T1  T2  T3  T4
  / \                              /  \
T2   T3                           T3   T4
*/

// C program to delete a node from AVL Tree
#include<stdio.h>
#include<stdlib.h>

// An AVL tree node
typedef struct _Node {
  int key;
  struct _Node *left;
  struct _Node *right;
  int height;
} Node;

// A utility function to get height of the tree
int
height(Node *n){
  if (n == NULL)
    return 0;
  return n->height;
}

// A utility function to get maximum of two integers
#define max(a, b) ((a > b) ? a : b)

/* Helper function that allocates a new node with the given key and
    NULL left and right pointers. */
Node*
newNode(int key)
{
  Node* node = (Node*) malloc(sizeof(Node));
  node->key = key;
  node->left = NULL;
  node->right = NULL;
  // new node is initially added at leaf
  node->height = 1;
  return node;
}

// A utility function to right rotate subtree rooted with r
// See the diagram given above.
Node*
rightRotate(Node *r)
{
  Node *x = r->left;
  Node *temp = x->right;

  // Perform rotation
  x->right = r;
  r->left = temp;

  // Update heights
  r->height = max(height(r->left), height(r->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;

  // Return new root
  return x;
}

// A utility function to left rotate subtree rooted with r
// See the diagram given above.
Node*
leftRotate(Node *r)
{
  Node *x = r->right;
  Node *temp = x->left;

  // Perform rotation
  x->left = r;
  r->right = temp;

  // Update heights
  r->height = max(height(r->left), height(r->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;

  // Return new root
  return x;
}

// Get Balance factor of node n
int
getBalance(Node *n)
{
  if (n == NULL)
    return 0;
  return height(n->left) - height(n->right);
}

/* Given a non-empty binary search tree, return the
   node with minimum key value found in that tree.
   Note that the entire tree does not need to be
   searched. */
Node*
minValueNode(Node *n)
{
  Node *current = n;
  // loop down to find the leftmost leaf
  while (current->left != NULL)
    current = current->left;

  return current;
}

Node*
insert(Node* node, int key)
{
  // 1. Perform the normal BST ratation
  if (node == NULL)
    return newNode(key);

  if (key < node->key)
    node->left = insert(node->left, key);
  else if (key > node->key)
    node->right = insert(node->right, key);
  else // Equal keys not allowed
    return node;

  // 2. Update height of this ancestor node
  node->height = max(height(node->left),
                     height(node->right)) + 1;

  // 3. Get the balance factor of this ancestor node
  // to check whether this node become unbalanced
  int balance = getBalance(node);

  // If this node becomes unbalanced, then there are 4 caces

  // Left Left Case
  if (balance > 1 && key < node->left->key)
    return rightRotate(node);
  // Right Right Case
  if (balance < -1 && key > node->right->key)
    return leftRotate(node);
  // Left Right Case
  if (balance > 1 && key > node->left->key)
  {
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }
  // Right Left Case
  if (balance < -1 && key < node->right->key)
  {
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }

  return node;
}

// Recursive function to delete a node with given key
// from subtree with given root. It returns root of
// the modified subtree.
Node*
deleteNode(Node* root, int key)
{
  // 1. Perform standard BST delete
  if (root == NULL)
    return root;

  // If the key to be deleted is smaller than the root's key,
  // then it lies in left subtree
  if (key < root->key)
    root->left = deleteNode(root->left, key);
  // If the key to be deleted is greater than the root's key,
  // then is lies in right subtree
  else if (key > root->key)
    root->right = deleteNode(root->right, key);
  // If key is same as root's key,
  // then this is the node to be deleted
  else
  {
    // node with only one child or no child
    if ((root->left == NULL) || (root->right == NULL))
    {
      Node *temp = root->left ? root->left : root->right;
      // No child case
      if (temp == NULL) {
        temp = root;
        root = NULL;
      }
      // One child case
      else
        // Copy the contents of the non-empty child
        root = temp;

      free(temp);
    }
    else
    {
      // node with two children: Get the inorder
      // successor (smallest in the right subtree)
      Node *temp = minValueNode(root->right);

      // Copy the inorder successor's data to this node
      root->key = temp->key;

      // Delete the inorder successor
      root->right = deleteNode(root->right, temp->key);
    }
  }

  // If the tree had only one node then return
  if (root == NULL)
    return root;

  // 2. Update height of the current node
  root->height = max(height(root->left),
                     height(root->right)) + 1;

  // 3. Get the balance factor of this node
  // (to check whether this node become unbalanced)
  int balance = getBalance(root);

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

// A utility function to print preorder traversal of
// the tree.
// The function also prints height of every node
void
preOrder(Node *root)
{
  if (root != NULL)
  {
    printf("%d ", root->key);
    preOrder(root->left);
    preOrder(root->right);
  }
}

// Driver program to test above function
int main()
{
  Node *root = NULL;

  // Constructing tree given in the above figure
  root = insert(root, 9);
  root = insert(root, 5);
  root = insert(root, 10);
  root = insert(root, 0);
  root = insert(root, 6);
  root = insert(root, 11);
  root = insert(root, -1);
  root = insert(root, 1);
  root = insert(root, 2);

  /* The constructed AVL Tree would be
          9
         /  \
        1    10
      /  \     \
     0    5     11
    /    /  \
   -1   2    6
  */

  printf("Preorder traversal of the constructed AVL tree is \n");
  preOrder(root);
  printf("\n");

  root = deleteNode(root, 10);
  root = deleteNode(root, 20);

  /* The AVL Tree after deletion of 10
          1
         /  \
        0    9
      /     /  \
     -1    5     11
         /  \
        2    6
  */

  printf("Preorder traversal after deletion of 10 \n");
  preOrder(root);
  printf("\n");

  return 0;
}

// Preorder traversal of the constructed AVL tree is
// 9 1 0 -1 5 2 6 10 11
// Preorder traversal after deletion of 10
// 1 0 -1 9 5 2 6 11
