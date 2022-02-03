#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include "StringList.h"
#include "NewsParser.h"

int Menu_FileOpen(char* string, StringList* list);
int Menu_Search(StringList* list);
int Menu_Explan();

int main()
{
	StringList List;
	int ch = 0;
	char Path[100];

	int IsLoadComplete = 0;

	Init(&List);

	setlocale(LC_ALL, "ko-KR");

	while (1)
	{
		system("cls");
		printf("�ȳ��Ͻʴϱ�? HTML �ļ��Դϴ�.\n");
		printf("���ϴ� �޴��� �����ϼ���.\n");
		printf("(1) ���Ϸε�\n");
		printf("(2) �˻��ϱ�\n");
		printf("(3) ���α׷� ����\n");
		printf("(4) ����\n");

		if (IsLoadComplete)
		{
			printf("���� �ε� �� ���� : %s\n", Path);
		}

		printf("�Է� : ");
		fflush(stdin);
		ch = getche();

		switch (ch)
		{
		case '1':
			IsLoadComplete = Menu_FileOpen(Path, &List);
			break;
		case '2':
			if (IsLoadComplete)
			{
				Menu_Search(&List);
			}
			else
			{
				printf("������ �ε� ���� �ʾҽ��ϴ�. ������ ���� �ε��ϼ���.\n");
				getch();
			}
			break;
		case '3':
			Menu_Explan();
			break;
		case '4':
			// ����Ʈ ���� �� ���� �ݱ�
			Quit(&List);
			return 0; // ����
		default:
		{
			printf("\n�߸��� �Է� �Դϴ�. Ű�� �Է��ϼ���.");
			getch();
			break;
		}
		}
		
	}
}

int Menu_FileOpen(char* string, StringList* list)
{
	char FileName[128];
	char TempFileName[128];
	while (1)
	{
		fflush(stdin);
		printf("\n�ҷ��� ������ �̸��� �Է��ϼ��� :");
		gets(FileName);

		if (!strcmp(FileName, "!q"))
		{
			printf("\n�޴��� ���ư��ϴ�.\n");
			return 0;
		}

		strcpy(TempFileName, FileName);
		if (strstr(FileName, ".html") == NULL)
		{
			strcat(FileName, ".html");
		}

		if (_access(FileName, 0) != NULL)
		{
			printf("%s�� ���� ������ �����ϴ�.\n", FileName);
			printf("�ٽ� �Է��ϼ���. (Ű�� ������ �ٽ� �Է��մϴ�.)\n");
			printf("���Ḧ ���Ͻø� !q�� �Է��ϼ���.\n");
			getch();
			continue;
		}

		// ���� ������ �����ϸ� �Ľ� ����

		Quit(list); // ������ ����Ʈ�� �����Ű�� �ٽ� �ʱ�ȭ
		Init(list);

		if (!ParsingHTML(FileName)) // ������ ���
		{
			printf("������ �Ľ��ϴµ� ������ �߻��߽��ϴ�.\n");
			getch();
			continue;
		}

		strcat(TempFileName, ".txt");

		if (!OpenParsedText(TempFileName, list))
		{
			printf("������ �����ϴµ� ������ �߻��߽��ϴ�.\n");
			getch();
			continue;
		}

		strcpy(string, TempFileName);
		break; // �Ľ��� �Ϸ�Ǿ����Ƿ� ����
	}

	return 1;
}

int Menu_Search(StringList* list)
{
	char inputBuffers[READ_SIZE];
	StringNode* TempNode;
	system("cls");
	while (1)
	{
		printf("���ϴ� �����̳� �ܾ �Է��ϼ���. \n");
		printf("!q : �޴��� ���ư���\n");
		printf("!a : ��ü ���\n");
		printf("\n\n�Է� : ");

		gets(inputBuffers);

		if (!strcmp(inputBuffers, "!q"))
		{
			printf("�޴��� ���ư��ϴ�. �ƹ�Ű�� ��������\n");
			getch();
			return 1;
		}

		if (!strcmp(inputBuffers, "!a")) // ��ü ���
		{
			PrintList(list);
			continue;
		}

		if (strcmp(inputBuffers, ""))
		{
			TempNode = list->head;
			while (TempNode != NULL)
			{
				TempNode = FindNodeByString(TempNode, inputBuffers);
				if (TempNode != NULL)
				{
					if (TempNode->prev != list->head)
						printf("- %s\n\n\n", TempNode->prev->buffer);

					printf("- %s\n\n\n", TempNode->buffer);

					if (TempNode->next != NULL)
						printf("- %s\n\n\n", TempNode->next->buffer);
				}
				else
					continue;
			}
		}
	}
	return 0;
}

int Menu_Explan()
{
	system("cls");

	printf("-���α׷� ����-\n");
	printf("�� ���α׷��� ���� ������ ���� Ư¡�� �����ϴ�.\n");
	printf("1. HTML �Ľ����α׷����μ� Naver, Daum, Nate�� ���� ������ �����մϴ�.\n");
	printf("2. ���� �÷����� ���� �ٸ��� �����մϴ�.\n");
	printf("3. ������ ���� ���α׷��� ��ġ�� ������ �������� ����ϴ�.\n");
	printf("4. Naver�� Nate������ �߰��� �� ������ ���� ���ּž� �մϴ�.\n");
	printf("���� ���������� �ҽ��� �ٸ� �̸����� ������, �ҽ� ������ ctrl + a, ctrl + c�մϴ�.\n");
	printf("���� �ռ� ������ html�� ���� ctrl + v �� �����մϴ�,\n");

	printf("\nŰ�� �Է��ϸ� �޴��� ���ư��ϴ�.");
	getch();
	return 0;
}