#include "NewsParser.h"
NewsSiteState OpenFile(FILE** file, const char* filePath)
{
	NewsSiteState format;
	*file = fopen(filePath, "r+");
	if (file != NULL) // 열었다.
	{
		format = CheckNewsState(*file);

		fseek(*file, 0L, SEEK_SET);
	}
	else
		format = DEFAULT;

	return format;
}

NewsSiteState CheckNewsState(FILE* file)
{
	char Buffers[READ_SIZE];

	while (!feof(file))
	{
		fgets(Buffers, READ_SIZE, file);
		if (strstr(Buffers, "naver") != NULL) // 네이버
		{
			return NAVER;
		}
		else if (strstr(Buffers, "nate") != NULL)
		{
			return NATE;
		}
		else if (strstr(Buffers, "daum") != NULL)
		{
			return DAUM;
		}
		else // 찾지 못했다면
		{
			continue;
		}
	}

	return DEFAULT;
}

int ParsingHTML(const char* filePath)
{
	FILE *file = NULL;
	NewsSiteState NewsSite;
	int FileHandle = 1;

	int IsSwitch = 0;
	int MaxPrint = 60;
	int index = 0;

	NewsSite = OpenFile(&file, filePath);
	switch (NewsSite)
	{
	//case DEFAULT:
	//	ReadUNICODE(file, filePath, textFormat);
	//	break;
	case DAUM:
		ReadUTF8(file, filePath, NewsSite);
		break;
	case NAVER:
	case NATE:
		ReadANSI(file, filePath, NewsSite);
		break;
	default:
		fclose(file);
		return 0; // FAIL
	}

	if (file != NULL)
		fclose(file);

	return 1;
}

int OpenParsedText(const char* filePath, StringList* list)
{
	char buffers[READ_SIZE];
	char* Token;
	FILE *inputFile;
	inputFile = fopen(filePath, "r");

	if (inputFile == NULL)
		return 0;

	while (!feof(inputFile))
	{
		fgets(buffers, READ_SIZE, inputFile);
		if (strstr(buffers, ">") != NULL)
		{
			continue;
		}
		else
		{
			Token = strtok(buffers, "\n");
			while (Token != NULL)
			{
				PushLast(list, Token);

				Token = strtok(NULL, "\n");
			}
		}
	}

	fclose(inputFile);
	return 1;
}

int ReadUNICODE(FILE* file, const char* filePath, NewsSiteState NewsSite)
{

}

int ReadANSI(FILE* file, const char* filePath, NewsSiteState NewsSite)
{
	char buffers[READ_SIZE];
	char* token;
	int ch = 0;
	int HTMLtag = 0;

	switch (NewsSite)
	{
	case NAVER:
		Naver(file, filePath);
		break;
	case NATE:
		Nate(file, filePath);
		break;
	}

	return 1;
}

int ReadUTF8(FILE* file, const char* filePath, NewsSiteState NewsSite)
{
	wchar_t buffers[READ_SIZE];
	wchar_t* token;
	int ch = 0;
	int HTMLtag = 0;

	// UTF-8로 다시 열기
	fclose(file);
	file = fopen(filePath, "r+,ccs=UTF-8");
	if (file == NULL)
		return 0;

	Daum(file, filePath);

	return 1;
}

// Ansi
void Naver(FILE* file, const char* filePath)
{
	FILE* outputFile;
	char outputFileBuffer[128];

	char buffers[READ_SIZE];
	char* strResult;

	strcpy(outputFileBuffer, strtok(filePath, "."));
	strcat(outputFileBuffer, ".txt");
	outputFile = fopen(outputFileBuffer, "w");

	if (outputFile == NULL)
		return;

	while (!feof(file)) // 타이틀 가져오기
	{
		fgets(buffers, READ_SIZE, file);
		strResult = strstr(buffers, "<title>");
		if (strResult != NULL)
		{
			strcpy(buffers, strResult);
			break;
		}
		else
			continue;
	}

	if (feof(file))
		return;

	fputs(DeleteTag(buffers), outputFile);

	while (!feof(file)) // 본문 까지 내려감.
	{
		fgets(buffers, READ_SIZE, file);
		if (strstr(buffers, "함수 추가") != NULL) // 이후 본문 등장
		{
			break;
		}
		else
			continue;
	}

	if (feof(file))
		return;

	while (!feof(file)) // 본문 파싱
	{
		fgets(buffers, READ_SIZE, file);
		if (strstr(buffers, "본문 내용") == NULL)
		{
			DeleteTagBlank(buffers);
			fputs(buffers, outputFile);
			continue;
		}
		else
		{
			break;
		}
	}


	fclose(outputFile);
}

// Ansi
void Nate(FILE* file, const char* filePath)
{
	FILE* outputFile;
	char outputFileBuffer[128];
	strcpy(outputFileBuffer, strtok(filePath, "."));
	strcat(outputFileBuffer, ".txt");
	outputFile = fopen(outputFileBuffer, "w");

	char buffers[READ_SIZE];
	char* strResult;

	if (outputFile == NULL)
		return;

	while (!feof(file)) // 타이틀 가져오기
	{
		fgets(buffers, READ_SIZE, file);
		strResult = strstr(buffers, "<title>");
		if (strResult != NULL)
		{
			strcpy(buffers, strResult);
			break;
		}
		else
			continue;
	}

	if (feof(file))
		return;

	fputs(DeleteTag(buffers), outputFile);
	while (!feof(file)) // 본문 까지 내려감.
	{
		fgets(buffers, READ_SIZE, file);
		if (strstr(buffers, "<!-- 기사 내용 -->") != NULL) // 이후 본문 등장
		{
			break;
		}
		else
			continue;
	}

	if (feof(file))
		return;

	while (!feof(file)) // 본문 파싱
	{
		fgets(buffers, READ_SIZE, file);
		if (strstr(buffers, "/*") == NULL)
		{
			DeleteTagBlank(buffers);
			fputs(buffers, outputFile);
			continue;
		}
		else
		{
			break;
		}
	}
	fclose(outputFile);
}

// UTF-8
void Daum(FILE* file, const char* filePath)
{
	FILE* outputFile;
	char outputFileBuffer[128];
	char charBuffers[READ_SIZE + 1];
	wchar_t buffers[READ_SIZE + 1];
	wchar_t* TempStr;
	// 파일 출력
	strcpy(outputFileBuffer, strtok(filePath, "."));
	strcat(outputFileBuffer, ".txt");
	outputFile = fopen(outputFileBuffer, "w");

	if (outputFile == NULL)
		return;

	while (!feof(file)) // 타이틀 가져오기
	{
		fgetws(buffers, READ_SIZE, file);
		TempStr = wcsstr(buffers, L"<title>");
		if (TempStr != NULL)
		{
			wcscpy(buffers, TempStr);
			break;
		}
		else
			continue;
	}

	if (feof(file))
		return;

	TempStr = DeleteTagWCHAR(buffers);
	charBuffers[wcstombs(charBuffers, TempStr, READ_SIZE)] = '\0';
	fputs(charBuffers, outputFile);

	while (!feof(file)) // 본문 까지 내려감.
	{
		fgetws(buffers, READ_SIZE, file);
		if (wcsstr(buffers, L"<section") != NULL) // 이후 본문 등장
		{
			break;
		}
		else
			continue;
	}

	if (feof(file))
		return;

	while (!feof(file)) // 본문 파싱
	{
		fgetws(buffers, READ_SIZE, file);
		if (wcsstr(buffers, L"</section>") == NULL)
		{
			TempStr = DeleteTagWCHAR(buffers);
			/*swprintf(buffers, wcslen(TempStr), L"%s\n", TempStr);*/
			charBuffers[wcstombs(charBuffers, TempStr, READ_SIZE + 1)] = '\0';
			fputs(charBuffers, outputFile);
			continue;
		}
		else
		{
			break;
		}
	}

	fclose(outputFile);
}

char* DeleteTag(char* String)
{
	int pos = 0;
	char* Token;
	char* OnlyString;
	int isTag = 0;
	Token = strtok(String, ">");
	while (1)
	{
		Token = strtok(NULL, ""); //자르고 나머지를 얻는다.
		if (Token == NULL)
			return "";

		pos = strcspn(Token, "<");

		if (pos == 0) // 즉 바로 다음이다. <br></br>
		{
			Token = strtok(Token, ">");
			continue;
		}
		else // 내용이 존재한다.
		{
			Token = strtok(Token, "<");
			break;
		}
	}
	
	return Token;
}

char* DeleteTagBlank(char String[])
{
	int i = 0;
	int isTag = 0;
	while (String[i] != '\0')
	{
		if (String[i] == '<')
			isTag = 1;
		else if (String[i] == '>')
		{
			isTag = 0;
			String[i] = ' ';
		}

		if (isTag)
		{
			String[i] = ' ';
		}

		i++;
	}

	return String;
}

wchar_t* DeleteTagWCHAR(wchar_t* String)
{
	wchar_t* Token;
	wchar_t* ptr = NULL;
	wchar_t* OnlyString;
	Token = wcstok(String, L">", ptr);

	Token = wcstok(NULL, L"<", ptr);

	if (Token == NULL)
		return L"";

	return Token;
}

wchar_t* DeleteTagWCHARBlank(wchar_t String[])
{
	int i = 0;
	int isTag = 0;
	while (String[i] != L'\0')
	{
		if (String[i] == L'<')
			isTag = 1;
		else if (String[i] == L'>')
		{
			isTag = 0;
			String[i] = L'\n';
		}

		if (isTag)
		{
			String[i] = L' ';
		}

		i++;
	}

	return String;
}