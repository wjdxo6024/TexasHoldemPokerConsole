#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRINGS 512

// 이중 연결 리스트

typedef struct _StringNode
{
	struct _StringNode* next;
	struct _StringNode* prev;
	char buffer[MAX_STRINGS];
} StringNode;

typedef struct _StringList
{
	StringNode* head;
	StringNode* last;
} StringList;

void Init(StringList* list);
void Quit(StringList* list);

int IsEmpty(StringList* list);
void PushLast(StringList* list, const char* string);
void PushFirst(StringList* list, const char* string); // Not Used
const char* PopFirst(StringList* list); // Not Used
const char* PopLast(StringList* list); // Not Used
const char* FindString(StringList* list, const char* string);
StringNode* FindFirstNodeByString(StringList* list, const char* string);
StringNode* FindNodeByString(StringNode* node, const char* string);
StringNode* GetHead(StringList* list);
StringNode* GetLast(StringList* list);

void PrintList(StringList* list);