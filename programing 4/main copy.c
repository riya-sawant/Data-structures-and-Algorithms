#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "leak_detector_c.h"

#define MAXLEN 31

FILE * output;

typedef struct itemNode
{
    int count;
    char name[MAXLEN];
    struct itemNode * left;
    struct itemNode* right;

}itemNode;

typedef struct treeNameNode
{
    char treeName[MAXLEN];
    struct treeNameNode * left;
    struct treeNameNode* right;
    itemNode * theTree;

}treeNameNode;

// scanning and creating larger tree
treeNameNode * createTreeNameNode(char name[]);
treeNameNode * fillNameTree(treeNameNode * root, int N);
treeNameNode * insert(treeNameNode * root, treeNameNode * node);

// scanning and creating smaller tree
itemNode * createitemNode(char itemName[], int count);
itemNode * fillItemTree(treeNameNode * treeRoot, itemNode * itemRoot, int I);
itemNode * buildItem(itemNode * root, itemNode * newNode);

// searching trees for values
treeNameNode * searchNameNode(treeNameNode * root, char treeName[]);
itemNode * searchItem(itemNode * root, char itemName[]);

// query functions
void search(treeNameNode * root);
int countNode(itemNode *root, char itemName[]);
void item_before(treeNameNode * root);
int calcHeight(itemNode * root);
void height_balance(treeNameNode * root);
int addAllCount(itemNode * root);
void count(treeNameNode * root);
itemNode * minVal(itemNode * root);
itemNode * deleteItem(itemNode * root, char itemName[]);
void reduce(treeNameNode * root);
void delete(treeNameNode * root);
void freeNode(itemNode *root);
void freeTree(treeNameNode * root);
void delete_name(treeNameNode * root);

// traversing tree
void inorder(treeNameNode * root);
void subTree(itemNode * root);
void traverse_in_traverse(treeNameNode * root);

// queries
void queryOptions(treeNameNode * root, int Q);

int main() {

    // memory leak check
    //atexit(report_mem_leak);

    struct treeNameNode * root = NULL;
    struct itemNode * itemRoot = NULL;
    output = fopen("out.txt", "w");

    int N, I, Q;

    scanf("%d %d %d", &N, &I, &Q);

    root = fillNameTree(root, N);

    fillItemTree(root, itemRoot, I);

    //prints 
    inorder(root);
    printf("\n");
    fprintf(output, "\n");
    traverse_in_traverse(root);

    //queries
    queryOptions(root, Q);

    // closes file
    fclose(output);

    return 0;
}

treeNameNode * createTreeNameNode(char name[])
{
    treeNameNode * node = malloc(sizeof(treeNameNode));

    strcpy(node->treeName, name);

    node->left = NULL;
    node->right = NULL;
    node->theTree = NULL;

    return node;
}

treeNameNode * fillNameTree(treeNameNode * root, int N)
{
    char name[MAXLEN];

    for(int i = 0; i < N; i++)
    {
        scanf("%s", name);
        treeNameNode * newNode = createTreeNameNode(name);
        root = insert(root, newNode);
    }

    return root;
}

struct treeNameNode *insert(treeNameNode * root, treeNameNode * node)
{
   if(root ==NULL)
    {
        return root = node;
    }
    if(strcmp(root->treeName, node->treeName) > 0)
    {
        if(root->left != NULL)
        {
            root->left = insert(root->left, node);
        }
        else
        {
          root->left = node;
        }
    }
    else
    {
        if(root->right != NULL)
        {
          root->right = insert(root->right, node);
        }
        else
        {
          root->right = node;
        }     
    }

  return root;
}
itemNode * createitemNode(char itemName[], int count)
{
    //struct itemNode * node = malloc(sizeof(itemNode));
  struct itemNode* node;
    node = malloc(sizeof(itemNode));

    strcpy(node->name, itemName);
    node->count = count;

    node->left = NULL;
    node->right = NULL;

    return node;
}
void inorder(treeNameNode * root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%s ", root->treeName); 
        fprintf(output, "%s ", root->treeName);
        inorder(root->right);
    }
}
itemNode * fillItemTree(treeNameNode * treeRoot, itemNode * itemRoot, int I)
{
    treeNameNode * tree = NULL;
    char treeName[MAXLEN];
    char name[MAXLEN];
    int i;
    int count;

    for(int i = 0; i < I; i++)
    {
        scanf("%s", treeName);

        tree = searchNameNode(treeRoot, treeName);

        scanf("%s %d", name, &count);
        
        itemNode * newNode = createitemNode(name, count);

        tree->theTree = buildItem(tree->theTree, newNode);
    }
    return tree->theTree;
}

itemNode * buildItem(itemNode * root, itemNode * newNode)
{
    if(root == NULL)
        return root = newNode;

    if(strcmp(root->name, newNode->name) > 0)
    {
        if(root->left != NULL)
            root->left = buildItem(root->left, newNode);
        else
            root->left = newNode;
    }
    else
    {
        if(root->right != NULL)
            root->right = buildItem(root->right, newNode);
        else
            root->right = newNode;
    }
    return root;
}

treeNameNode * searchNameNode(treeNameNode * root, char treeName[])
{
    if(root != NULL)
    {
        if(strcmp(root->treeName, treeName) == 0)
            return root;

        else if(strcmp(root->treeName, treeName) > 0)
            return searchNameNode(root->left, treeName);

        else if(strcmp(root->treeName, treeName) < 0)
            return searchNameNode(root->right, treeName);

        else
            return NULL;
    }

    return NULL;
}

itemNode * searchItem(itemNode * root, char itemName[])
{
    if(root != NULL)
    {
        if(strcmp(root->name, itemName) == 0)
            return root;

        else if(strcmp(root->name, itemName) > 0)
            return searchItem(root->left, itemName);

        else if(strcmp(root->name, itemName) < 0)
            return searchItem(root->right, itemName);

        else
            return NULL;
    }

    return NULL;
}

void search(treeNameNode * root)
{
    treeNameNode * tree = NULL;
    char tName[MAXLEN];
    char iName[MAXLEN];

    scanf("%s", tName);

    tree = searchNameNode(root, tName);

    if(tree == NULL)
    {
        printf("%s does not exist\n", tName);
        fprintf(output, "%s does not exist\n", tName);
    }

    scanf("%s", iName);

    if(tree != NULL)
    {
        itemNode * node = searchItem(tree->theTree, iName);

        if(node != NULL)
        {
            printf("%d %s found in %s\n", node->count, iName, tName);
            fprintf(output, "%d %s found in %s\n", node->count, iName, tName);
        }
        else
        {
            printf("%s not found in %s\n", iName, tName);
            fprintf(output, "%s not found in %s\n", iName, tName);
        }
    }
}

int countNode(itemNode *root, char itemName[])
{
    if(root == NULL)
        return 0;

    if (strcmp(root->name, itemName) == 0)
        return 1;

    else if(strcmp(root->name, itemName) > 0)
        return countNode(root->left, itemName) + 1;

    else
        return countNode(root->right, itemName) + 1;
}

void item_before(treeNameNode * root)
{
    char treeName[MAXLEN];
    char itemName[MAXLEN];
    int count;

    scanf("%s %s", treeName, itemName);

    treeNameNode * tree = searchNameNode(root, treeName);
    count = countNode(tree->theTree, itemName);

    printf("item before %s: %d\n", itemName, count + 1);
    fprintf(output, "item before %s: %d\n", itemName, count + 1);
}

int calcHeight(itemNode * root)
{
    if(root == NULL)
        return -1;
    
    int left_height = calcHeight(root->left);
    int right_height = calcHeight(root->right);

    return left_height > right_height ? left_height + 1: right_height + 1;
}

void height_balance(treeNameNode * root)
{
    char treeName[MAXLEN];
    scanf("%s", treeName);

    treeNameNode * tree = searchNameNode(root, treeName);
    int left, right, height;

    if (tree->theTree->left == NULL || tree->theTree->right == NULL)
        left = -1;

    left = calcHeight(tree->theTree->left);
    right = calcHeight(tree->theTree->right);

    height = abs(right - left);

    if(height > 1)
    {
        printf("%s: left height %d, right height %d, difference %d, not balanced\n", treeName, left, right, height);
        fprintf(output, "%s: left height %d, right height %d, difference %d, not balanced\n", treeName, left, right, height);
    }
    else
    {
        printf("%s: left height %d, right height %d, difference %d, balanced\n", treeName, left, right, height);
        fprintf(output, "%s: left height %d, right height %d, difference %d, balanced\n", treeName, left, right, height);
    }
}

int addAllCount(itemNode * root) 
{
    if (root != NULL)
        return root->count + addAllCount(root->left) + addAllCount(root->right);
    else
        return 0;
}

void count(treeNameNode * root)
{
    char treeName[MAXLEN];
    scanf("%s", treeName);

    treeNameNode * tree = searchNameNode(root, treeName);
    int count;

    if(tree == NULL)
    {
        printf("%s does not exist\n", treeName);
        fprintf(output, "%s does not exist\n", treeName);
    }
    else
    {
        count = addAllCount(tree->theTree);
        printf("%s count %d\n", treeName, count);
        fprintf(output, "%s count %d\n", treeName, count);
    }
}

itemNode * minVal(itemNode * root)
{
    if (root->left == NULL)
        return root;
    else
        return minVal(root->left);
}

itemNode * deleteItem(itemNode * root, char itemName[])
{
    if(root == NULL)
		return root;

    if(strcmp(root->name, itemName) > 0)
        root->left = deleteItem(root->left, itemName);

    else if(strcmp(root->name, itemName) < 0)
        root->right = deleteItem(root->right, itemName);

    else
    {
        if(root->left == NULL) 
        {
            itemNode * temp = root->right;
            strcpy(root->name, "");
            root->count = 0;
            freeNode(root);
            return temp;
        }
        else if(root->right == NULL) 
        {
            itemNode * temp = root->left;
            strcpy(root->name, "");
            root->count = 0;
            freeNode(root);
            return temp;
        }
        
        itemNode * temp = minVal(root->right);
    
        strcpy(root->name, temp->name);
        root->count = temp->count;
    
        root->right = deleteItem(root->right, temp->name);
    }
    return root;
}

void reduce(treeNameNode * root)
{
    char treeName[MAXLEN], itemName[MAXLEN];
    int count;

    scanf("%s %s %d", treeName, itemName, &count);

    treeNameNode * tree = searchNameNode(root, treeName);

    if(tree != NULL)
    {
        itemNode * temp = searchItem(tree->theTree, itemName);

        if(temp->count > 0)
        {
            temp->count -= count;

            printf("%s reduced\n", itemName);
            fprintf(output, "%s reduced\n", itemName);
        }

        if(temp->count <= 0)
            deleteItem(tree->theTree, itemName);
    }
}

void delete(treeNameNode * root)
{
    char treeName[MAXLEN], itemName[MAXLEN];

    scanf("%s %s", treeName, itemName);

    treeNameNode * tree = searchNameNode(root, treeName);

    if(tree == NULL)
    {
        printf("%s does not exist\n", treeName);
        fprintf(output, "%s does not exist\n", treeName);
    }
    else
    {
        deleteItem(tree->theTree, itemName);
        printf("%s deleted from %s\n", itemName, treeName);
        fprintf(output, "%s deleted from %s\n", itemName, treeName);
    }
}

void freeNode(itemNode * root)
{
    if(root != NULL)
    {
        freeNode(root->left);
        freeNode(root->right);
        free(root);
    }
}

void freeTree(treeNameNode * root)
{
    if(root != NULL)
    {
        freeTree(root->left);
        freeTree(root->right);
        freeNode(root->theTree);
        free(root);
    }
}

void delete_name(treeNameNode * root)
{
    char treeName[MAXLEN];

    scanf("%s", treeName);

    treeNameNode *tree = searchNameNode(root, treeName);
    strcpy(tree->treeName, "");
    freeTree(tree);
    printf("%s deleted\n", treeName);
    fprintf(output, "%s deleted\n", treeName);
    
}



void subTree(itemNode * root)
{
    if (root != NULL)
    {
        subTree(root->left);
        printf("%s ", root->name);
        fprintf(output, "%s ", root->name);
        subTree(root->right);
    }
}

void traverse_in_traverse(treeNameNode * root)
{
    if (root != NULL)
    {
        traverse_in_traverse(root->left);
        printf("===%s===\n", root->treeName);
        fprintf(output, "===%s===\n", root->treeName);
        subTree(root->theTree);
        printf("\n");
        fprintf(output, "\n");
        traverse_in_traverse(root->right);
    }
}

void queryOptions(treeNameNode * root, int Q)
{
    char option[MAXLEN];

    for(int i = 0; i < Q; i++)
    {
        scanf("%s", option);

        if(strcmp(option, "search") == 0)
            search(root);

        if(strcmp(option, "item_before") == 0)
            item_before(root);

        if(strcmp(option, "height_balance") == 0)
            height_balance(root);

        if(strcmp(option, "count") == 0)
            count(root);

        if(strcmp(option, "reduce") == 0)
            reduce(root);

        if(strcmp(option, "delete") == 0)
            delete(root);

        if(strcmp(option, "delete_name") == 0)
            delete_name(root);
    }
}