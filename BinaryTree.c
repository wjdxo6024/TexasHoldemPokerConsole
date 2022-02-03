#include "BinaryTree.h"

BOOKDATA* make_node(const char* name, const char* phoneNumber)
{
	BOOKDATA* tempData;
	tempData = (BOOKDATA*)malloc(sizeof(BOOKDATA));
	strcpy(tempData->phoneNumber, phoneNumber);
	strcpy(tempData->name, name);
	tempData->left = NULL;
	tempData->right = NULL;
	return tempData;
}

void print_node(BOOKDATA *node)
{
	printf("%s %s\n", node->name, node->phoneNumber);
}

void insert_node(BOOKDATA **root, BOOKDATA *node)
{
	BOOKDATA *tree = *root;
	if (*root == NULL)
	{
		*root = node;
	}
	else if (strcmp((*root)->name, node->name) > 0)
	{
		insert_node(&(*root)->left, node);
	}
	else
	{
		insert_node(&(*root)->right, node);
	}
}

void print_preorder(BOOKDATA *tree)
{
	if (tree == NULL) return;
	print_node(tree);
	print_preorder(tree->left);
	print_preorder(tree->right);
}

void print_inorder(BOOKDATA *tree)
{
	if (tree == NULL) return;
	print_inorder(tree->left);
	print_node(tree);
	print_inorder(tree->right);
}

void print_postorder(BOOKDATA *tree)
{
	if (tree == NULL) return;
	print_postorder(tree->left);
	print_postorder(tree->right);
	print_node(tree);
}

BOOKDATA *binary_search(BOOKDATA *tree, char *name)
{
	if (tree == NULL) return NULL;
	if (strcmp(tree->name, name) == 0)
		return tree;
	else if (strcmp(tree->name, name) > 0)
		return binary_search(tree->left, name);
	else
		return binary_search(tree->right, name);
}

BOOKDATA* delete_node(BOOKDATA *tree, char *name)
{
	BOOKDATA* DeleteNode;
	BOOKDATA* DeleteParentNode;
	BOOKDATA* MinNode;
	BOOKDATA* MinParentNode;
	BOOKDATA* Temp;
	DeleteNode = binary_search(tree, name);

	if (DeleteNode != NULL) // 찾았다.
	{
		DeleteParentNode = Find_ParentNode(tree, name);
		if (DeleteParentNode == NULL) // 루트 노드를 제거해야 한다.
		{
			if (DeleteNode->left != NULL && DeleteNode->right != NULL) // 자식 노드가 모두 존재할 경우
			{
				MinNode = Find_LeftMinNode(DeleteNode->right);
				MinParentNode = Find_ParentNode(DeleteNode, MinNode->name);
				CopyNodeData(DeleteNode, MinNode);

				//if (ChildNode->right != NULL)
				//	ChildParentNode->right = ChildNode->right;
				if (MinParentNode->left == MinNode)
				{
					if (MinNode->right != NULL)
						MinParentNode->left = MinNode->right;
					else
						MinParentNode->left = NULL;
				}
				else
				{
					if (MinNode->right != NULL)
						MinParentNode->right = MinNode->right;
					else
						MinParentNode->right = NULL;
				}

				free(MinNode);
			}
			else if (DeleteNode->left != NULL) // 왼쪽 자식만 존재할 경우
			{
				tree = DeleteNode->left;
				free(DeleteNode);
			}
			else if (DeleteNode->right != NULL) // 오른쪽 자식만 존재할 경우
			{
				tree = DeleteNode->right;
				free(DeleteNode);
			}
			else // 루트 노드 혼자일 경우
			{
				tree = NULL;
				free(DeleteNode);
			}
		}
		else
		{
			if (DeleteNode->left != NULL && DeleteNode->right != NULL) // 자식 노드가 모두 존재 할 경우
			{
				MinNode = Find_LeftMinNode(DeleteNode->right);
				MinParentNode = Find_ParentNode(DeleteNode, MinNode->name);
				CopyNodeData(DeleteNode, MinNode);

				if (MinParentNode->left == MinNode)
				{
					if (MinNode->right != NULL)
						MinParentNode->left = MinNode->right;
					else
						MinParentNode->left = NULL;
				}
				else
				{
					if (MinNode->right != NULL)
						MinParentNode->right = MinNode->right;
					else
						MinParentNode->right = NULL;
				}

				free(MinNode);
			}
			else if (DeleteNode->left != NULL) // 왼쪽 자식만 존재할 경우
			{
				Temp = DeleteNode->left;
				CopyNodeDataAll(DeleteNode, DeleteNode->left);
				free(Temp);
			}
			else if (DeleteNode->right != NULL) // 오른쪽 자식만 존재할 경우
			{
				Temp = DeleteNode->right;
				CopyNodeDataAll(DeleteNode, DeleteNode->right);
				free(Temp);
			}
			else // 없을 경우
			{
				if (DeleteParentNode->right != NULL && strcmp(DeleteParentNode->right->name, DeleteNode->name) == 0)
				{
					DeleteParentNode->right = NULL;
				}
				else if (DeleteParentNode->left != NULL && strcmp(DeleteParentNode->left->name, DeleteNode->name) == 0)
				{
					DeleteParentNode->left = NULL;
				}
				

				free(DeleteNode);
			}
		}
	}
	else // 찾지 못했다.
	{
		printf("Cannot Find Node.\n");
	}

	return tree;
}

BOOKDATA* Find_LeftMinNode(BOOKDATA* node)
{
	if(node != NULL && node->left != NULL)
	{
		return Find_LeftMinNode(node->left);
	}
	else
	{
		return node;
	}
}

BOOKDATA* Find_ParentNode(BOOKDATA* node, char *name)
{
	if (node == NULL) return NULL;
	if ((node->left != NULL && strcmp(node->left->name, name) == 0 )|| (node->right != NULL && (strcmp(node->right->name, name) == 0)))
		return node;
	else if (strcmp(node->phoneNumber, name) > 0)
		return Find_ParentNode(node->left, name);
	else
		return Find_ParentNode(node->right, name);
}

void CopyNodeData(BOOKDATA* node1, BOOKDATA* node2)
{
	strcpy(node1->phoneNumber, node2->phoneNumber);
	strcpy(node1->name, node2->name);
}

void CopyNodeDataAll(BOOKDATA* node1, BOOKDATA* node2)
{
	CopyNodeData(node1, node2);
	node1->left = node2->left;
	node1->right = node2->right;
}

void DeleteTree(BTree* tree)
{
	if(tree->root != NULL)
		postorder_delete(tree->root);
}

void postorder_delete(BOOKDATA* node)
{
	if (node == NULL) return NULL;
	postorder_delete(node->left);
	postorder_delete(node->right);
	free(node);
}

void SaveTree(BTree* tree, FILE* fp)
{
	if(tree->root != NULL)
		postorder_save(tree->root, fp);
}

void postorder_save(BOOKDATA* node, FILE* fp)
{
	char Buffer[256];
	if (node == NULL) return;
	postorder_save(node->left, fp);
	postorder_save(node->right, fp);

	strcpy(Buffer, node->name);
	strcat(Buffer, " ");
	strcat(Buffer, node->phoneNumber);
	strcat(Buffer, "\n");
	fputs(Buffer, fp);
}