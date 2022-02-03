#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include "BinaryTree.h"


int Initialize(BTree* tree);  // ������ �ҷ����� Ʈ���� ����
void PrintAll(BTree* tree);
void Enroll(BTree* tree);
void Search(BTree* tree);
void Delete(BTree* tree);
void Replace(BTree* tree);
int Quit(BTree* tree); // Ʈ���� �ִ� �����͸� �����Ѵ�. �׸��� Ʈ���� ����

int main()
{
	BTree PhoneBook;
	char InputBuffer[128];
	int InputMenu = 0;
	PhoneBook.root = NULL;
	if (!Initialize(&PhoneBook))
	{
		printf("�ʱ�ȭ �� ������ �߻��Ͽ����ϴ�.\n");
		return 1;
	}

	while (1)
	{
		system("cls");
		printf("��ȭ��ȣ�� ���α׷��Դϴ�.\n");
		printf("(0) ��ü ���\n");
		printf("(1) ���\n");
		printf("(2) Ž��\n");
		printf("(3) ����\n");
		printf("(4) ��ü\n");
		printf("(5) ����\n");
		printf("���Ͻô� �޴��� �����ϼ��� : ");
		scanf("%d", &InputMenu);

		switch (InputMenu)
		{
		case 0:
			PrintAll(&PhoneBook);
			break;
		case 1:
			Enroll(&PhoneBook);
			break;
		case 2:
			Search(&PhoneBook);
			break;
		case 3:
			Delete(&PhoneBook);
			break;
		case 4:
			Replace(&PhoneBook);
			break;
		case 5:
			Quit(&PhoneBook);
			return 0;

		default:
			printf("�߸��� �Է��Դϴ�. �ٽ� �Է��ϼ���.\n");
			getch();
			continue;
		}
	}
	return 0;
}

int Initialize(BTree* tree)
{
	FILE* fp;
	char *path = ".\\Save.txt";
	char stringBuffer[256];
	char PhoneNumber[36];
	char Name[36];
	char *token;
	if (_access(path, 0) != 0)
	{
		// ������ �������� ������ ������ �����.
		fp = fopen(path, "w+");
		close(fp);
	}
	
	fp = fopen(path, "r");
	while (1)
	{
		fscanf(fp, "%s %s", Name, PhoneNumber);
		if (feof(fp))
		{
			printf("������ �����͸� ���� �б� �Ϸ��߽��ϴ�.\n");
			break;
		}

		insert_node(&tree->root, make_node(Name, PhoneNumber));
	}

	printf("�ҷ����⸦ �Ϸ��߽��ϴ�.");
	fclose(fp);
	return 1;
}

void PrintAll(BTree* tree)
{
	print_inorder(tree->root);
	printf("�ƹ� Ű�� ������ �޴��� ���ư��ϴ�.\n");
	getch();
}

void Enroll(BTree* tree)
{
	char NameBuffer[128];
	char PhoneBuffer[128];
	system("cls");

	printf("��ȭ��ȣ �ο� �����͸� �Է��մϴ�. �޴��� ���ư��� ������ !q�� �Է��ϼ���.\n");
	while (1)
	{
		printf("����� �̸��� �Է��ϼ���. :");
		scanf("%s", &NameBuffer);

		if (strlen(NameBuffer) >= NAME_SIZE)
		{
			printf("�̸��� �ʹ� ��ϴ�.\n");
			continue;
		}

		if (!strcmp(NameBuffer, "!q"))
		{
			printf("�޴��� ���ư��ϴ�. �ƹ� Ű�� �Է��ϼ���.\n");
			getch();
			return;
		}

		break;
	}

	while (1)
	{
		printf("����� ��ȭ��ȣ�� �Է��ϼ���. :");
		scanf("%s", &PhoneBuffer);

		if (strlen(PhoneBuffer) >= PHONENUMBER_SIZE)
		{
			printf("��ȭ��ȣ�� �ʹ� ��ϴ�.\n");
			continue;
		}

		if (!strcmp(PhoneBuffer, "!q"))
		{
			printf("�޴��� ���ư��ϴ�. �ƹ� Ű�� �Է��ϼ���.\n");
			getch();
			return;
		}

		break;
	}

	insert_node(&tree->root, make_node(NameBuffer, PhoneBuffer));

	printf("����� �Ϸ�Ǿ����ϴ�. �޴��� ���ư��ϴ�.\n");
	getch();
	return ;
}

void Search(BTree* tree)
{
	char NameBuffer[256];
	BOOKDATA* data;
	system("cls");

	if (tree->root == NULL)
	{
		printf("��ȭ��ȣ�ΰ� ������ϴ�. �޴��� ���ư��ϴ�.\n");
		getch();
		return;
	}

	printf("�̸��� �Է��Ͽ� ��ȭ��ȣ�� ����ϵ��� �˻��մϴ�.\n");
	printf("�̸��� �Է��ϼ���. : ");
	scanf("%s", &NameBuffer);

	data = binary_search(tree->root, &NameBuffer);
	if (data == NULL)
	{
		printf("%s�� �̸��� ���� ��ȭ��ȣ�� ã�� ���߽��ϴ�.\n", NameBuffer);
	}
	else
	{
		printf("%s�� ��ȭ��ȣ %s\n", data->name, data->phoneNumber);
	}

	printf("�ƹ� Ű�� ������ �޴��� ���ư��ϴ�.\n");
	getch();
	return;
}

void Delete(BTree* tree)
{
	char NameBuffer[256];
	BOOKDATA* data;
	system("cls");

	if (tree->root == NULL)
	{
		printf("��ȭ��ȣ�ΰ� ������ϴ�. �޴��� ���ư��ϴ�.\n");
		getch();
		return;
	}

	printf("�̸��� �Է��Ͽ� �����͸� �����մϴ�.\n");
	printf("�̸��� �Է��ϼ���. : ");
	scanf("%s", &NameBuffer);

	data = binary_search(tree->root, &NameBuffer);
	if (data == NULL)
	{
		printf("%s�� �̸��� ���� ��ȭ��ȣ�� ã�� ���߽��ϴ�.\n", NameBuffer);
	}
	else
	{
		printf("%s : %s�� �����մϴ�.\n", data->name, data->phoneNumber);
		tree->root = delete_node(tree->root, &NameBuffer);
	}

	printf("�ƹ� Ű�� ������ �޴��� ���ư��ϴ�.\n");
	getch();
	return;
}

void Replace(BTree* tree)
{
	char NameBuffer[256];
	char PhoneNumberBuffer[256];
	BOOKDATA* data;
	system("cls");

	if (tree->root == NULL)
	{
		printf("��ȭ��ȣ�ΰ� ������ϴ�. �޴��� ���ư��ϴ�.\n");
		getch();
		return;
	}

	printf("�̸��� �Է��Ͽ� �����͸� ��ü�մϴ�.\n");
	printf("�̸��� �Է��ϼ���. : ");
	scanf("%s", &NameBuffer);

	data = binary_search(tree->root, &NameBuffer);
	if (data == NULL)
	{
		printf("%s�� �̸��� ���� ��ȭ��ȣ�� ã�� ���߽��ϴ�.\n", NameBuffer);
	}
	else
	{
		printf("ã�ҽ��ϴ�!\n");
		printf("%s�� ��ȭ��ȣ %s\n", data->name, data->phoneNumber);

		while (1)
		{
			printf("����� ��ȭ��ȣ�� �Է��ϼ���.(!q : ���θ޴�) :");
			scanf("%s", &PhoneNumberBuffer);

			if (strlen(PhoneNumberBuffer) >= PHONENUMBER_SIZE)
			{
				printf("��ȭ��ȣ�� �ʹ� ��ϴ�.\n");
				continue;
			}

			if (!strcmp(PhoneNumberBuffer, "!q"))
			{
				printf("�޴��� ���ư��ϴ�. �ƹ� Ű�� �Է��ϼ���.\n");
				getch();
				return;
			}

			break;
		}

		strcpy(data->phoneNumber, PhoneNumberBuffer);

		printf("��ü �Ϸ��߽��ϴ�. \n");
		printf("%s�� ��ȭ��ȣ %s\n", data->name, data->phoneNumber);
	}

	printf("�ƹ� Ű�� ������ �޴��� ���ư��ϴ�.\n");
	getch();
	return;
}

int Quit(BTree* tree)
{
	FILE* fp;
	fp = fopen(".\\Save.txt", "w");
	if (fp == NULL)
	{
		perror("������ �� �� �����ϴ�.");
		return 1;
	}

	SaveTree(tree, fp);
	DeleteTree(tree);
	fclose(fp);
	return 0;
}