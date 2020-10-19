#include <stdio.h>
#include <iostream>
#include "avl.hpp"
using namespace std;

#define IS_ROOT 0
#define IS_LEFT 1
#define IS_RIGHT 2

//helper to get height for node
int height(AvlNode *x)
{
  if(x == NULL)
    return 0;
  return x->height;
}

int max(int a, int b);

int max(int a, int b)
{
  return (a > b)? a : b;
}

//int min(int a, int b)

//finding minimum helper function
AvlNode* findMin(AvlNode* x)
{
  if(x == NULL)
    return NULL;
  else if(x->left == NULL)
    return x;
  else
  {
    return findMin(x->left);
  }
  
}

//right rotate
AvlNode* rightRotate(AvlNode * & node1)
{
  AvlNode* node2 = node1->left;
  node1->left = node2->right;
  node2->right = node1;

  node1->height = max(height(node1->left), height(node1->right)) + 1;
  node2->height = max(height(node2->left), node1->height) + 1;

  return node2;
}

//left rotate
AvlNode* leftRotate(AvlNode * & x)
{
  AvlNode* y = x->right;
  x->right = y->left;
  y->left = x;

  x->height = max(height(x->left), height(x->right)) + 1;
  y->height = max(height(x->right), x->height) + 1;

  return y;

}

//rl rotate
AvlNode* doubleLeftRotate(AvlNode * & x)
{
  x->right = rightRotate(x->right);
  return leftRotate(x);
}

//lr rotate
AvlNode* doubleRightRotate(AvlNode * & x)
{
  x->left = leftRotate(x->left);
  return rightRotate(x);
}

//getting balance value for tree
int getBalance(AvlNode *node)
{
  if(node == NULL)
  {
    return 0;
  }
  return height(node->left) - height(node->right);
}

/**
 * Internal method to insert into a subtree.
 * x is the item to insert.
 * t is the node that roots the subtree.
 * Set the new root of the subtree.
 */
void insert( const int & info, AvlNode * & root )
{
  if (root == NULL)
    root = new AvlNode (info, NULL, NULL);
  
  //inserts into tree
  if(root != NULL)
  {
    if(info < root->element)
      insert(info, root->left);
    else if (info > root->element)
      insert(info, root->right);
    else
    {
      root->element = info;
    }
  }
  
  //calculate height
  root->height = 1 + max(height(root->left), height(root->right));

  int balance = getBalance(root);

  //checks if a rotate is required based on balance
  if ((balance > 1) && info < root->left->element)
  {
    root = rightRotate(root);
  }
  
  if(balance < -1 && info < root->right->element)
  {
    root = doubleLeftRotate(root);
    
  }

  if((balance > 1 ) && info > root->left->element)
  {
    root = doubleRightRotate(root);
    
  }

  
  if(balance < -1 && info > root->right->element)
  {
    root = leftRotate(root);
  }

}

/**
 * Internal method to remove from a subtree.
 * info is the item to remove.
 * root is the node that roots the subtree.
 * Set the new root of the subtree.
 */
void remove( const int & info, AvlNode * & root ) {
  AvlNode* temp;

  if(root == NULL)
  {
    return;
  }
  else if(info < root->element)
  {
    remove(info, root->left);
  }
  else if(info > root->element)
  {
    remove(info, root->right);
  }

  else if(root->left && root->right)
  {
    temp = findMin(root->right);
    root->element = temp->element;
    remove(root->element, root->right);
  }

  else
  {
    temp = root;
    if(root->left == NULL)
    {
      root = root->right;
    }
    else if(root->right == NULL)
    {
      root = root->left;
    }
    delete temp;
  }
  if(root == NULL)
  {
    return;
  }

  root->height = max(height(root->left), height(root->right)) + 1;

  if(height(root->left) - height(root->right) == 2)
  {
    // right right case
    if(height(root->left->left) - height(root->left->right) == 1)
      root = leftRotate(root);
    // right left case
    else
      root = doubleLeftRotate(root);
  }
  // If right node is deleted, left case
  else if(height(root->right) - height(root->left) == 2)
  {
    // left left case
    if(height(root->right->right) - height(root->right->left) == 1)
      root = rightRotate(root);
    // left right case
    else
      root = doubleRightRotate(root);
  }
  
}


/*
 * You will probably neesd auxiliary mathods to 
 *  - find the minimum of tree
 *  - rotate (single and double, in both directions
 *  - balance am AVL  tree
 */

/*
 * Print methods, do not change
 */
void print(AvlNode *root, int level, int type) {
  if (root == NULL) {
    return;
  }
  if (type == IS_ROOT) {
    std::cout << root -> element << "\n";
  } else {
    for (int i = 1; i < level; i++) {
      std::cout << "| ";
    }
    if (type == IS_LEFT) {
      std::cout << "|l_" << root -> element << "\n";
    } else {
      std::cout << "|r_" << root -> element << "\n";
    }
  }
  if (root -> left != NULL) {
    print(root -> left, level + 1, IS_LEFT);
  }
  if (root -> right != NULL) {
    print(root -> right, level + 1, IS_RIGHT);
  }
}
void print(AvlNode *root) {
  print(root, 0, IS_ROOT);
}
/*
 * END Print methods, do not change
 */


/* 
 * Main method, do not change
 */
int main(int argc, const char * argv[]) {
  AvlNode *root = NULL;
  std::string filename = argv[1];
  freopen(filename.c_str(), "r", stdin);
  std::string input;
  int data;
  while(std::cin >> input){
    if (input == "insert"){
      std::cin>>data;
      insert(data, root);
    } else if(input == "delete"){
      std::cin>>data;
      remove(data, root);
    } else if(input == "print"){
      print(root);
      std::cout << "\n";
    } else{
      std::cout<<"Data not consistent in file";
      break;
    }
  }
  return 0;
}
/*
 * END main method
 */
