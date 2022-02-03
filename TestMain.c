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
		printf("스트레이트 플러쉬\n"); break;
	case FourOfKind:
		printf("포카드\n"); break;
	case FullHouse:
		printf("풀하우스\n"); break;
	case Flush:
		printf("플러쉬\n"); break;
	case Straight:
		printf("스트레이트\n"); break;
	case ThreeOfKind:
		printf("트리플\n"); break;
	case TwoPair:
		printf("투페어\n"); break;
	case OnePair:
		printf("원페어\n"); break;
	case HighCard:
		printf("하이카드\n"); break;
	default:
		printf("버그발생\n"); break;
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
		printf("하이넘버 : %d\n", HighNumber);
		getch();
	}
}