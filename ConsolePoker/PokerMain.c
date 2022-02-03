#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>
#include "PokerRule.h"

void PlayGame(int PlayerNum);
int BettingPhase(PLAYER* Players, int* CurrentFoldCount, int* CurrentBettingMoney, int* BeforeBettingMoney, int PlayerNum, int BigBlind);
int SetBlindPlayer(PLAYER* Players, int PlayerNum, int *Blind);
int CheckPlayersCanJoinGame(PLAYER* Players, int PlayerNum, int *DealerButton);
int CheckOnlyOneLive(PLAYER* Players, int PlayerNum);
int CheckPlayerLive(PLAYER* Players);

int main()
{
	int Players = 0;
	char charInput = '\0';
	printf("텍사스 홀덤 포커 게임\n");
	while (1)
	{
		printf("인원 수를 설정 하세요(2 ~ 5명) : ");
		scanf("%d", &Players);
		if (Players < 2 || Players > 5)
		{
			printf("인원 수가 잘못되었습니다. 다시입력하세요. : ");
			continue;
		}

		//--------------------------------------------------------

		system("cls");
		printf("게임을 시작합니다.\n");
		PlayGame(Players);

		//---------------------------------------------------------
		
		printf("계속하시겠습니까? (Y/N) : ");
		getchar();
		scanf("%c", &charInput);

		if (charInput == 'y' || charInput == 'Y')
		{
			continue;
		}
		else if (charInput == 'n' || charInput == 'N')
			break;
	}

	printf("게임을 종료합니다.\n");
	return 0;
}

int BettingPhase(PLAYER* Players, int* CurrentFoldCount, int* CurrentBettingMoney, int* BeforeBettingMoney, int PlayerNum, int BigBlind)
{
	int i = 0;
	int BettedPlayerCount = 0;
	int PlayerBettedMoney;

	if (*CurrentFoldCount == PlayerNum - 1)
		return 1;

	for (i = (BigBlind + 1) % PlayerNum; BettedPlayerCount < PlayerNum; i = (i + 1) % PlayerNum, BettedPlayerCount++)
	{
		if (Players[i].State == Fold) // 미리 폴드한 사람은 넘어간다.
		{
			continue;
		}

		PlayerBettedMoney = SelectAction(&Players[i], *CurrentBettingMoney, BeforeBettingMoney);
		*CurrentBettingMoney += PlayerBettedMoney;

		if(*BeforeBettingMoney < PlayerBettedMoney)
			*BeforeBettingMoney = PlayerBettedMoney;

		if (Players[i].State == Fold) // 폴드를 결정했을 경우 추가한다.
		{
			(*CurrentFoldCount)++;

			if (*CurrentFoldCount == PlayerNum - 1)
				return 1;
		}
	}

	return 0;
}

int SetBlindPlayer(PLAYER* Players, int PlayerNum, int *Blind)
{
	int Count = 0;
	while (Count != PlayerNum)
	{
		if (Players[*Blind].State == Fold)
			*Blind = (*Blind + 1) % PlayerNum;
		else
			return 1;

		Count++;
	}

	return 0;
}

// 딜러버튼부터 시작하여 플레이어가 게임 참가 가능한지 파악한다.
int CheckPlayersCanJoinGame(PLAYER* Players, int PlayerNum, int *DealerButton)
{
	int i;
	i = 0;
	while (i < PlayerNum)
	{
		if (Players[i].Money <= 0)
		{
			printf("%s는 게임을 진행할 수 없습니다. 파산했습니다.\n", Players[i].Name);
			Players[i].State = Fold;
			(*DealerButton)++;
		}
		i++;
	}

	return 1;
}

// 단 한명 남았는지 판단한다.
// 현재 흐름 상에서 모든 ai가 게임 패배 시 작동한다.
int CheckOnlyOneLive(PLAYER* Players, int PlayerNum)
{
	int i = 0;
	int CannotJoinPlayerCount = 0;
	for (i = 0; i < PlayerNum; i++)
	{
		if (Players[i].Money <= 0)
			CannotJoinPlayerCount++;
	}

	if (CannotJoinPlayerCount == PlayerNum - 1) // 한 명만 생존
	{
		return 0;
	}

	return 1;
}

// 플레이어가 게임을 진행할 수 있는지 판단한다. 
// 이 알고리즘은 ai가 아닌 플레이어가 진행 불가일 경우 벗어난다.
int CheckPlayerLive(PLAYER* Players)
{
	if (Players[0].State == Fold && Players[0].Money <= 0)
		return 0;
	else
		return 1;
}

void PlayGame(int PlayerNum)
{
	CARDDECK cardDeck;
	CARD comunityCard[5];
	int GameRound = 1;
	int CurrentBettingMoney = 0;
	int PlayerRaiseMoney = 0;
	int CurrentFoldCount = 0;

	int DealerButton;
	int SmallBlind;
	int BigBlind;
	int LivedPlayerCount;

	int BettedPlayerCount = 0;
	int BeforeBettingMoney = 0;

	long long Winner = 0;
	int MultiWinnerCount;

	enum RankOfHands HighRank = None_Rank;
	enum CardNumber HighNumber = EmptyNumber;
	enum RankOfHands PlayerRank;
	enum PlayerState PlayerState;

	char PlayerInput;

	int i;
	PLAYER* Players;
	Players = malloc(sizeof(PLAYER) * PlayerNum);
	// 초기화
	srand(time(NULL));

	// 플레이어는 인덱스 0번으로 고정된다.
	for (i = 0; i < PlayerNum; i++)
	{
		if (i == 0)
			InitPlayer(&Players[i], 0);
		else
			InitPlayer(&Players[i], 1);

	}

	DealerButton = rand() % PlayerNum;

	GameRound = 1;

	// 게임 스타트
	while (1)
	{
		HighNumber = EmptyNumber;
		HighRank = None_Rank;

		InitCardDeck(&cardDeck);
		ShakeCardDeck(&cardDeck);
		memset(comunityCard, 0, sizeof(comunityCard));
		system("cls");
		printf("Game %d Round\n", GameRound);

		// Blind Phase
		printf("Blind Phase\n");

		CheckPlayersCanJoinGame(Players, PlayerNum, &DealerButton);
		if (!CheckPlayerLive(Players))
		{
			break;
		}

		if (!CheckOnlyOneLive(Players, PlayerNum))
		{
			break;
		}

		SmallBlind = (DealerButton + 1) % PlayerNum;
		if (!SetBlindPlayer(Players, PlayerNum, &SmallBlind))
		{
			break;
		}

		BigBlind = (SmallBlind + 1) % PlayerNum;
		if (!SetBlindPlayer(Players, PlayerNum, &BigBlind))
		{
			break;
		}

		printf("딜러 : %s, 스몰 : %s, 빅 : %s\n", &Players[DealerButton].Name,  &Players[SmallBlind].Name,
			 &Players[BigBlind].Name);

		CurrentBettingMoney = BlindPhase(&Players[SmallBlind], &Players[BigBlind]);
		BeforeBettingMoney = Players[BigBlind].BettingMoney;
		// Give Card Phase -----------------------------
		for (i = 0; i < PlayerNum; i++)
		{
			GiveCard(&cardDeck, &Players[i]);
			GiveCard(&cardDeck, &Players[i]);
		}
		//----------------------------------------------

		// Fold Phase ----------------------------------
		printf("Fold Phase\n");
		CardSetToTable(&cardDeck, comunityCard);
		CardSetToTable(&cardDeck, comunityCard);
		CardSetToTable(&cardDeck, comunityCard);

		printf("All Betting Money : %d $\n", CurrentBettingMoney);
		printf("Before Betting Money : %d $\n", BeforeBettingMoney);
		for (i = 0; i < 3; i++)
		{
			PrintCard(&comunityCard[i]);
		}
		printf("\n");

		if (BettingPhase(Players, &CurrentFoldCount, &CurrentBettingMoney, &BeforeBettingMoney, PlayerNum, BigBlind))
			goto RESULT;
		//-----------------------------------------------

		// Turn Phase -----------------------------------
		printf("Turn Phase\n");
		CardSetToTable(&cardDeck, comunityCard);

		printf("All Betting Money : %d $\n", CurrentBettingMoney);
		printf("Before Betting Money : %d $\n", BeforeBettingMoney);

		for (i = 0; i < 4; i++)
		{
			PrintCard(&comunityCard[i]);
		}
		printf("\n");

		if (BettingPhase(Players, &CurrentFoldCount, &CurrentBettingMoney, &BeforeBettingMoney, PlayerNum, BigBlind))
			goto RESULT;

		//------------------------------------------------

		// River Phase -----------------------------------
		printf("River Phase\n");
		CardSetToTable(&cardDeck, comunityCard);

		printf("All Betting Money : %d $\n", CurrentBettingMoney);
		printf("Before Betting Money : %d $\n", BeforeBettingMoney);

		for (i = 0; i < 5; i++)
		{
			PrintCard(&comunityCard[i]);
		}
		printf("\n");

		if (BettingPhase(Players, &CurrentFoldCount, &CurrentBettingMoney, &BeforeBettingMoney, PlayerNum, BigBlind))
			goto RESULT;

		//------------------------------------------------
		// Result Phase

	RESULT:
		printf("The Result\n");
		for (i = 0; i < PlayerNum; i++)
		{
			if (Players[i].State == Fold)
				continue;

			WhatRanks(&Players[i], comunityCard);
		}

		for (i = 0; i < PlayerNum; i++)
		{
			if (Players[i].State == Fold)
				continue;

			PlayerRank = Players[i].PlayerRank;
			if (HighRank == None_Rank) // 처음 시작 시 초기화
			{
				HighRank = PlayerRank;
				HighNumber = Players[i].PlayerCardMaxNumber;
			}
			else
			{
				if (HighRank < PlayerRank)
				{
					HighRank = PlayerRank;
					HighNumber = Players[i].PlayerCardMaxNumber;
				}
				else if (HighRank == PlayerRank)
				{
					if (HighNumber < Players[i].PlayerCardMaxNumber)
						HighNumber = Players[i].PlayerCardMaxNumber;
				}
			}
		}

		printf("\n- Round Winners --\n");
		MultiWinnerCount = 0;
		for (i = 0; i < PlayerNum; i++) // 공통 순위가 있는지 확인
		{
			if (Players[i].State == Fold)
				continue;

			PlayerRank = Players[i].PlayerRank;
			if (HighRank == PlayerRank && HighNumber == Players[i].PlayerCardMaxNumber)
			{
				printf("%s : ", Players[i].Name);
				PrintCardNumber(Players[i].PlayerCardMaxNumber);
				PrintRank(PlayerRank);

				// 배열을 사용하지 않고 8자리수를 사용한다. 이 방법은 플레이어가 8명을 벗어나면 불가능하다. (1, 2, 3, 4, 5, 6, 7, 8)
				Winner += i + 1;
				Winner *= 10;
				MultiWinnerCount++;
			}
		}

		// 돈 계산
		while (Winner != 0)
		{
			if(Winner % 10 != 0)
				Players[(Winner % 10) - 1].Money += CurrentBettingMoney / MultiWinnerCount;
			Winner /= 10;
		}
		//-------------------------------------------------

		// 재시작 여부
		while (1)
		{
			printf("라운드를 계속하시겠습니까? Y/N : ");
			getchar();
			PlayerInput = getchar();
			if (PlayerInput == 'n' || PlayerInput == 'N')
			{
				printf("라운드를 종료합니다. 메인 메뉴로 돌아갑니다.\n");
				getch();
				// 게임 종료
				free(Players);
				return ;
			}
			else if (PlayerInput == 'y' || PlayerInput == 'Y')
			{
				GameRound++;
				DealerButton = (DealerButton + 1) % PlayerNum;
				CurrentFoldCount = 0;

				for (i = 0; i < PlayerNum; i++)
					InitPlayerRoundStart(&Players[i]);

				break;
			}
			else
			{
				printf("다시 입력하세요.\n");
			}
		}
		
	}

	// 플레이어 승패 밝히기.
	if (Players[0].isAI == 0)
	{
		if (Players[0].Money > 0)
		{
			printf("%s는 게임에서 승리하셨습니다.\n", Players[0].Name);
		}
		else
			printf("%s는 게임에서 패배하셨습니다.\n", Players[0].Name);
	}

	// 게임 종료
	free(Players);
}

