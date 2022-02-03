#include "PokerDefine.h"
#include "PokerRule.h"
#include "GameAI.h"
#include <time.h>

void PrintCards(CARD *cards)
{
	int i = 0;
	printf("Print Cards\n");
	for (i = 0; i < 5; i++)
	{
		PrintCard(&cards[i]);
	}
}

void DeleteCards(CARD *cards)
{
	int i = 0;
	for (i = 0; i < 5; i++)
	{
		DeleteCard(&cards[i]);
	}
}

void PrintRank(enum RankOfHands Rank)
{
	printf("\n");
	switch (Rank)
	{
	case StraightFlush:
		printf("��Ʈ����Ʈ �÷���\n"); break;
	case FourOfKind:
		printf("��ī��\n"); break;
	case FullHouse:
		printf("Ǯ�Ͽ콺\n"); break;
	case Flush:
		printf("�÷���\n"); break;
	case Straight:
		printf("��Ʈ����Ʈ\n"); break;
	case ThreeOfKind:
		printf("Ʈ����\n"); break;
	case TwoPair:
		printf("�����\n"); break;
	case OnePair:
		printf("�����\n"); break;
	case HighCard:
		printf("����ī��\n"); break;
	default:
		printf("���׹߻�\n"); break;
	}
}

void main()
{
	int i = 0;
	PLAYER player;
	CARDDECK deck;
	CARD cards[5];
	enum CardNumber HighNumber;

	srand(time(NULL));
	InitCardDeck(&deck);
	ShakeCardDeck(&deck);
	while (1)
	{
		InitPlayer(&player, 1);
		//ShakeCardDeck(&deck);
		DeleteCards(cards);

		CardSetToTable(&deck, cards);
		CardSetToTable(&deck, cards);
		CardSetToTable(&deck, cards);
		CardSetToTable(&deck, cards);
		CardSetToTable(&deck, cards);

		SortCard(cards, 5);
		PrintCards(cards);
		PrintRank(GetRanks(&player, cards, &HighNumber));
		printf("���̳ѹ� : %d\n", HighNumber);
		getch();
	}
}