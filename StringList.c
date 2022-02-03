#include "StringList.h"

void Init(StringList* list)
{
	StringNode * Head;
	Head = malloc(sizeof(StringNode));
	memset(Head, 0, sizeof(StringNode));
	Head->prev = NULL;
	Head->next = NULL;
	strcpy(Head->buffer, "//Start");

	list->head = Head;
	list->last = Head;
}

void Quit(StringList* list)
{
	StringNode* Curr = list->head;
	StringNode* Next = NULL;
	while (Curr != NULL)
	{
		Next = Curr->next;
		free(Curr);
		Curr = Next;
	}
}

int IsEmpty(StringList* list)
{
	if (list->head == NULL && list->last == NULL)
	{
		return 1;
	}
	else
		return 0;
}

void PushLast(StringList* list, const char* string)
{
	StringNode* Curr = list->head;
	StringNode* Next = Curr->next;

	StringNode* New = NULL;

	if (list == NULL || strlen(string) > MAX_STRINGS)
		return;

	New = malloc(sizeof(StringNode));
	memset(New, 0, sizeof(New));
	strcpy(New->buffer, string);

	if (list->last != NULL) // Head <-> LastNode <-> NULL
	{
		list->last->next = New;
		New->next = NULL;
		New->prev = list->last;
		list->last = New;
	}
	else // NULL <- Head -> NULL, 첫 초기화에서 넣을 때.
 	{
		Curr->next = New;
		New->next = NULL;
		New->prev = Curr;
		list->last = New;
	}

}

void PushFirst(StringList* list, const char* string)
{
	if (list->last != NULL)
	{

	}
	else // NULL <- Head -> NULL, 첫 초기화에서 넣을 때.
	{
		// NULL <- Head -> Last -> NULL
	}
}

const char* PopFirst(StringList* list)
{

}

const char* PopLast(StringList* list)
{

}

const char* FindString(StringList* list, const char* string)
{
	return FindNodeByString(list, string)->buffer;
}

StringNode* FindFirstNodeByString(StringList* list, const char* string)
{
	StringNode* Curr = list->head->next;
	while (Curr != NULL)
	{
		if (strstr(Curr->buffer, string) != NULL)
		{
			return Curr;
		}
		Curr = Curr->next;
	}

	return NULL;
}

StringNode* FindNodeByString(StringNode* node, const char* string)
{
	StringNode* Curr = node->next;
	while (Curr != NULL)
	{
		if (strstr(Curr->buffer, string) != NULL)
		{
			return Curr;
		}
		Curr = Curr->next;
	}

	return NULL;
}

StringNode* GetHead(StringList* list)
{
	return list->head;
}

StringNode* GetLast(StringList* list)
{
	return list->last;
}

void PrintList(StringList* list)
{
	StringNode* Curr = list->head->next;
	while (Curr != NULL)
	{
		printf("%s\n\n", Curr->buffer);
		Curr = Curr->next;
	}
}