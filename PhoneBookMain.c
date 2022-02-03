#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include "BinaryTree.h"


int Initialize(BTree* tree);  // 파일을 불러오고 트리를 생성
void PrintAll(BTree* tree);
void Enroll(BTree* tree);
void Search(BTree* tree);
void Delete(BTree* tree);
void Replace(BTree* tree);
int Quit(BTree* tree); // 트리에 있는 데이터를 저장한다. 그리고 트리를 해제

int main()
{
	BTree PhoneBook;
	char InputBuffer[128];
	int InputMenu = 0;
	PhoneBook.root = NULL;
	if (!Initialize(&PhoneBook))
	{
		printf("초기화 중 에러가 발생하였습니다.\n");
		return 1;
	}

	while (1)
	{
		system("cls");
		printf("전화번호부 프로그램입니다.\n");
		printf("(0) 전체 출력\n");
		printf("(1) 등록\n");
		printf("(2) 탐색\n");
		printf("(3) 삭제\n");
		printf("(4) 교체\n");
		printf("(5) 종료\n");
		printf("원하시는 메뉴를 선택하세요 : ");
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
			printf("잘못된 입력입니다. 다시 입력하세요.\n");
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
		// 파일이 존재하지 않으면 파일을 만든다.
		fp = fopen(path, "w+");
		close(fp);
	}
	
	fp = fopen(path, "r");
	while (1)
	{
		fscanf(fp, "%s %s", Name, PhoneNumber);
		if (feof(fp))
		{
			printf("파일의 데이터를 전부 읽기 완료했습니다.\n");
			break;
		}

		insert_node(&tree->root, make_node(Name, PhoneNumber));
	}

	printf("불러오기를 완료했습니다.");
	fclose(fp);
	return 1;
}

void PrintAll(BTree* tree)
{
	print_inorder(tree->root);
	printf("아무 키나 누르면 메뉴로 돌아갑니다.\n");
	getch();
}

void Enroll(BTree* tree)
{
	char NameBuffer[128];
	char PhoneBuffer[128];
	system("cls");

	printf("전화번호 부에 데이터를 입력합니다. 메뉴로 돌아가고 싶으면 !q를 입력하세요.\n");
	while (1)
	{
		printf("등록할 이름을 입력하세요. :");
		scanf("%s", &NameBuffer);

		if (strlen(NameBuffer) >= NAME_SIZE)
		{
			printf("이름이 너무 깁니다.\n");
			continue;
		}

		if (!strcmp(NameBuffer, "!q"))
		{
			printf("메뉴로 돌아갑니다. 아무 키나 입력하세요.\n");
			getch();
			return;
		}

		break;
	}

	while (1)
	{
		printf("등록할 전화번호를 입력하세요. :");
		scanf("%s", &PhoneBuffer);

		if (strlen(PhoneBuffer) >= PHONENUMBER_SIZE)
		{
			printf("전화번호가 너무 깁니다.\n");
			continue;
		}

		if (!strcmp(PhoneBuffer, "!q"))
		{
			printf("메뉴로 돌아갑니다. 아무 키나 입력하세요.\n");
			getch();
			return;
		}

		break;
	}

	insert_node(&tree->root, make_node(NameBuffer, PhoneBuffer));

	printf("등록이 완료되었습니다. 메뉴로 돌아갑니다.\n");
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
		printf("전화번호부가 비었습니다. 메뉴로 돌아갑니다.\n");
		getch();
		return;
	}

	printf("이름을 입력하여 전화번호를 출력하도록 검색합니다.\n");
	printf("이름을 입력하세요. : ");
	scanf("%s", &NameBuffer);

	data = binary_search(tree->root, &NameBuffer);
	if (data == NULL)
	{
		printf("%s의 이름을 가진 전화번호를 찾지 못했습니다.\n", NameBuffer);
	}
	else
	{
		printf("%s의 전화번호 %s\n", data->name, data->phoneNumber);
	}

	printf("아무 키나 누르면 메뉴로 돌아갑니다.\n");
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
		printf("전화번호부가 비었습니다. 메뉴로 돌아갑니다.\n");
		getch();
		return;
	}

	printf("이름을 입력하여 데이터를 제거합니다.\n");
	printf("이름을 입력하세요. : ");
	scanf("%s", &NameBuffer);

	data = binary_search(tree->root, &NameBuffer);
	if (data == NULL)
	{
		printf("%s의 이름을 가진 전화번호를 찾지 못했습니다.\n", NameBuffer);
	}
	else
	{
		printf("%s : %s를 삭제합니다.\n", data->name, data->phoneNumber);
		tree->root = delete_node(tree->root, &NameBuffer);
	}

	printf("아무 키나 누르면 메뉴로 돌아갑니다.\n");
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
		printf("전화번호부가 비었습니다. 메뉴로 돌아갑니다.\n");
		getch();
		return;
	}

	printf("이름을 입력하여 데이터를 교체합니다.\n");
	printf("이름을 입력하세요. : ");
	scanf("%s", &NameBuffer);

	data = binary_search(tree->root, &NameBuffer);
	if (data == NULL)
	{
		printf("%s의 이름을 가진 전화번호를 찾지 못했습니다.\n", NameBuffer);
	}
	else
	{
		printf("찾았습니다!\n");
		printf("%s의 전화번호 %s\n", data->name, data->phoneNumber);

		while (1)
		{
			printf("등록할 전화번호를 입력하세요.(!q : 메인메뉴) :");
			scanf("%s", &PhoneNumberBuffer);

			if (strlen(PhoneNumberBuffer) >= PHONENUMBER_SIZE)
			{
				printf("전화번호가 너무 깁니다.\n");
				continue;
			}

			if (!strcmp(PhoneNumberBuffer, "!q"))
			{
				printf("메뉴로 돌아갑니다. 아무 키나 입력하세요.\n");
				getch();
				return;
			}

			break;
		}

		strcpy(data->phoneNumber, PhoneNumberBuffer);

		printf("교체 완료했습니다. \n");
		printf("%s의 전화번호 %s\n", data->name, data->phoneNumber);
	}

	printf("아무 키나 누르면 메뉴로 돌아갑니다.\n");
	getch();
	return;
}

int Quit(BTree* tree)
{
	FILE* fp;
	fp = fopen(".\\Save.txt", "w");
	if (fp == NULL)
	{
		perror("파일을 열 수 없습니다.");
		return 1;
	}

	SaveTree(tree, fp);
	DeleteTree(tree);
	fclose(fp);
	return 0;
}