#ifndef _POKERDEFINE_H_
#define _POKERDEFINE_H_
#define MAX_CARD_NUMBER 52
#define MAX_GAME_PLAYER_NUMBER 5
enum CardNumber { EmptyNumber, Ace, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King };
enum CardShape { EmptyShape, Clover, Diamond, Heart, Spade };
enum PlayerAction { None_Action, Fold, Call, Raise };
enum PlayerBlind { None_Blind, Small, Big };
enum RankOfHands { None_Rank, HighCard, OnePair, TwoPair, ThreeOfKind, Straight, Flush, FullHouse, FourOfKind, StraightFlush };

typedef struct Card
{
	enum CardNumber number;
	enum CardShape shape;
} CARD;

typedef struct CardDeck
{
	struct Card Cards[MAX_CARD_NUMBER];
	int top;
} CARDDECK;

typedef struct Rank
{
	enum RankOfHands DeckRank;
	enum CardNumber HighNumber;
};

typedef struct Player
{
	int isAI;
	char Name[32];
	struct Card Cards[5];
	int Money;
	int BettingMoney;
	enum PlayerAction State;
	enum RankOfHands PlayerRank; // �÷��̾� ����
	enum CardNumber PlayerCardMaxNumber; // ���� ������ ���� ���� ����
} PLAYER;


typedef struct PlayerTable
{
	struct Player players[MAX_GAME_PLAYER_NUMBER];
	int PlayerCount;
	int cur;
} PLAYERTABLE;

#endif