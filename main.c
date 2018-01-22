// main.c
// contains declaration and implementation of  binary tree methods and a simple application
// Tina Tsui, Dalton Burke

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// node of binary tree, need left and right pointers, and also counters for this application
struct bin_tree {
  char data[128];
  int count;
  struct bin_tree * right, * left;
};

typedef struct bin_tree node;

//Prototype
void delTree(node *tree);
void insert(node ** tree, char* val);
void toOutput(node * tree, FILE *fileOutput);


int main(int argc, char **argv) {

  // Make sure parameters are correct, instructions on if they are not
  if(argc != 3)
  {
    printf("Usage:\t%s <input_filename> <output_filename>\n", argv[0]);
    printf("Ex:\t%s input02.txt output03.txt\n", argv[0]);
    return 1;
  }

  char* input_filename = argv[1];
  char* output_filename = argv[2];
  printf("Input filename: %s\nOutput filename: %s\n", input_filename, output_filename);


  node *root;
  node *temp;
  root = NULL;

  FILE *fileInput = fopen(input_filename, "r");//Open the file to read mode

  char buffer[128];
  char* fmt = "%127s";
  while(fscanf(fileInput, fmt, buffer) > 0)
    insert(&root, buffer);

  fclose(fileInput);

  //Store data into the Output file.
  FILE *fileOutput = fopen (output_filename, "w");//Open the file to write mode
  toOutput(root, fileOutput);//Store to file
  fclose(fileOutput);//Close the file after saving

  /* Deleting all nodes of tree */
  delTree(root);

  printf("Done!\n");

  return 0;
}


// clear tree from memory
void delTree(node *tree)
{
  if (tree)
  {
    delTree(tree->left);//Delete left
    delTree(tree->right);//Delete right
    free(tree);//Free the tree
  }
}


// insert string to tree, if it's already there just increment the counter
void insert(node ** tree, char* val)
{
  node *temp = NULL;
  if(!(*tree))//If there is no tree, created a head/parent.
  {
    temp = (node *)malloc(sizeof(node));
    temp->left = temp->right = NULL;
    strcpy(temp->data, val);
    temp->count = 1;
    *tree = temp;
    return;
  }

  if(strcmp(val, (*tree)->data) < 0)//If tree is already created, add a child to left
    insert(&(*tree)->left, val);

  else if(strcmp(val, (*tree)->data) > 0)//If tree is already created, add a child to right.
    insert(&(*tree)->right, val);

  else if(strcmp(val, (*tree)->data) == 0)
    (*tree)->count = (*tree)->count + 1;
}


// in order traversal of binary tree and output to file
void toOutput(node * tree, FILE *fileOutput)
{
  if (tree)
  {
    toOutput (tree->left, fileOutput);//recursive call to save left child
    fprintf (fileOutput, "%s: %d\n", tree->data, tree->count);//Save the data to file
    toOutput (tree->right, fileOutput);//recursive call to save right child
  }
}
