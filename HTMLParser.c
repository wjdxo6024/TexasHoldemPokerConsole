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
		printf("안녕하십니까? HTML 파서입니다.\n");
		printf("원하는 메뉴를 선택하세요.\n");
		printf("(1) 파일로드\n");
		printf("(2) 검색하기\n");
		printf("(3) 프로그램 설명\n");
		printf("(4) 종료\n");

		if (IsLoadComplete)
		{
			printf("현재 로드 된 파일 : %s\n", Path);
		}

		printf("입력 : ");
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
				printf("파일이 로드 되지 않았습니다. 파일을 먼저 로드하세요.\n");
				getch();
			}
			break;
		case '3':
			Menu_Explan();
			break;
		case '4':
			// 리스트 종료 및 파일 닫기
			Quit(&List);
			return 0; // 종료
		default:
		{
			printf("\n잘못된 입력 입니다. 키를 입력하세요.");
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
		printf("\n불러올 파일의 이름을 입력하세요 :");
		gets(FileName);

		if (!strcmp(FileName, "!q"))
		{
			printf("\n메뉴로 돌아갑니다.\n");
			return 0;
		}

		strcpy(TempFileName, FileName);
		if (strstr(FileName, ".html") == NULL)
		{
			strcat(FileName, ".html");
		}

		if (_access(FileName, 0) != NULL)
		{
			printf("%s을 가진 파일이 없습니다.\n", FileName);
			printf("다시 입력하세요. (키를 누르면 다시 입력합니다.)\n");
			printf("종료를 원하시면 !q를 입력하세요.\n");
			getch();
			continue;
		}

		// 만약 파일이 존재하면 파싱 시작

		Quit(list); // 기존의 리스트를 종료시키고 다시 초기화
		Init(list);

		if (!ParsingHTML(FileName)) // 에러일 경우
		{
			printf("파일을 파싱하는데 에러가 발생했습니다.\n");
			getch();
			continue;
		}

		strcat(TempFileName, ".txt");

		if (!OpenParsedText(TempFileName, list))
		{
			printf("파일을 오픈하는데 에러가 발생했습니다.\n");
			getch();
			continue;
		}

		strcpy(string, TempFileName);
		break; // 파싱이 완료되었으므로 종료
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
		printf("원하는 문장이나 단어를 입력하세요. \n");
		printf("!q : 메뉴로 돌아가기\n");
		printf("!a : 전체 출력\n");
		printf("\n\n입력 : ");

		gets(inputBuffers);

		if (!strcmp(inputBuffers, "!q"))
		{
			printf("메뉴로 돌아갑니다. 아무키나 누르세요\n");
			getch();
			return 1;
		}

		if (!strcmp(inputBuffers, "!a")) // 전체 출력
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

	printf("-프로그램 설명-\n");
	printf("이 프로그램은 현재 다음과 같은 특징을 가집니다.\n");
	printf("1. HTML 파싱프로그램으로서 Naver, Daum, Nate의 뉴스 파일을 지원합니다.\n");
	printf("2. 뉴스 플랫폼에 따라 다르게 동작합니다.\n");
	printf("3. 파일은 현재 프로그램이 위치한 폴더를 기준으로 삼습니다.\n");
	printf("4. Naver와 Nate뉴스를 추가할 때 다음과 같이 해주셔야 합니다.\n");
	printf("뉴스 페이지에서 소스를 다른 이름으로 저장후, 소스 내용을 ctrl + a, ctrl + c합니다.\n");
	printf("이후 앞서 저장한 html를 열고 ctrl + v 후 저장합니다,\n");

	printf("\n키를 입력하면 메뉴로 돌아갑니다.");
	getch();
	return 0;
}