#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include "StringList.h"
#define READ_SIZE 512
#define TOKEN ">"

typedef enum _TextFormat { FAIL, ANSI, UTF_8, UTF_16, Unicode } TextFormat;
typedef enum _NewsSite { DEFAULT, NAVER, DAUM, NATE } NewsSiteState;

int ParsingHTML(const char* filePath); // HTML을 읽고 TXT로 파싱
int OpenParsedText(const char* filePath, StringList* list);
NewsSiteState OpenFile(FILE** file, const char* filePath); // 텍스트파일 설정 확인

NewsSiteState CheckNewsState(FILE* file);

int ReadUNICODE(FILE* file, const char* filePath, NewsSiteState NewsSite);
int ReadANSI(FILE* file, const char* filePath, NewsSiteState NewsSite);
int ReadUTF8(FILE* file, const char* filePath, NewsSiteState NewsSite);

void Naver(FILE* file, const char* filePath);
void Nate(FILE* file, const char* filePath);
void Daum(FILE* file, const char* filePath);

char* DeleteTag(char* String);
wchar_t* DeleteTagWCHAR(wchar_t* String);
char* DeleteTagBlank(char String[]);
wchar_t* DeleteTagWCHARBlank(wchar_t String[]);
