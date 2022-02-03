#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define PHONENUMBER_SIZE 36
#define NAME_SIZE 36

typedef struct BookData
{
	char phoneNumber[PHONENUMBER_SIZE];
	char name[NAME_SIZE];
	struct BookData * left;
	struct BookData * right;
} BOOKDATA;

typedef struct BinaryTree
{
	struct BookData* root;
} BTree;

BOOKDATA* make_node(const char* phoneNumber, const char* name);
void print_node(BOOKDATA *node);
void insert_node(BOOKDATA **root, BOOKDATA *node);
void print_preorder(BOOKDATA *tree);
void print_inorder(BOOKDATA *tree);
void print_postorder(BOOKDATA *tree);
BOOKDATA *binary_search(BOOKDATA* tree, char *id);
BOOKDATA* delete_node(BOOKDATA* tree, char *id);
BOOKDATA* Find_ParentNode(BOOKDATA* node, char *id);
BOOKDATA* Find_LeftMinNode(BOOKDATA* node);
void CopyNodeData(BOOKDATA* node1, BOOKDATA* node2);
void CopyNodeDataAll(BOOKDATA* node1, BOOKDATA* node2);

void DeleteTree(BTree* tree);
void postorder_delete(BOOKDATA* node);

void SaveTree(BTree* tree, FILE* fp);
void postorder_save(BOOKDATA* node, FILE* fp);