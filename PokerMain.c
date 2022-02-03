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
	printf("�ػ罺 Ȧ�� ��Ŀ ����\n");
	while (1)
	{
		printf("�ο� ���� ���� �ϼ���(2 ~ 5��) : ");
		scanf("%d", &Players);
		if (Players < 2 || Players > 5)
		{
			printf("�ο� ���� �߸��Ǿ����ϴ�. �ٽ��Է��ϼ���. : ");
			continue;
		}

		//--------------------------------------------------------

		system("cls");
		printf("������ �����մϴ�.\n");
		PlayGame(Players);

		//---------------------------------------------------------
		
		printf("����Ͻðڽ��ϱ�? (Y/N) : ");
		getchar();
		scanf("%c", &charInput);

		if (charInput == 'y' || charInput == 'Y')
		{
			continue;
		}
		else if (charInput == 'n' || charInput == 'N')
			break;
	}

	printf("������ �����մϴ�.\n");
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
		if (Players[i].State == Fold) // �̸� ������ ����� �Ѿ��.
		{
			continue;
		}

		PlayerBettedMoney = SelectAction(&Players[i], *CurrentBettingMoney, BeforeBettingMoney);
		*CurrentBettingMoney += PlayerBettedMoney;

		if(*BeforeBettingMoney < PlayerBettedMoney)
			*BeforeBettingMoney = PlayerBettedMoney;

		if (Players[i].State == Fold) // ���带 �������� ��� �߰��Ѵ�.
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

// ������ư���� �����Ͽ� �÷��̾ ���� ���� �������� �ľ��Ѵ�.
int CheckPlayersCanJoinGame(PLAYER* Players, int PlayerNum, int *DealerButton)
{
	int i;
	i = 0;
	while (i < PlayerNum)
	{
		if (Players[i].Money <= 0)
		{
			printf("%s�� ������ ������ �� �����ϴ�. �Ļ��߽��ϴ�.\n", Players[i].Name);
			Players[i].State = Fold;
			(*DealerButton)++;
		}
		i++;
	}

	return 1;
}

// �� �Ѹ� ���Ҵ��� �Ǵ��Ѵ�.
// ���� �帧 �󿡼� ��� ai�� ���� �й� �� �۵��Ѵ�.
int CheckOnlyOneLive(PLAYER* Players, int PlayerNum)
{
	int i = 0;
	int CannotJoinPlayerCount = 0;
	for (i = 0; i < PlayerNum; i++)
	{
		if (Players[i].Money <= 0)
			CannotJoinPlayerCount++;
	}

	if (CannotJoinPlayerCount == PlayerNum - 1) // �� �� ����
	{
		return 0;
	}

	return 1;
}

// �÷��̾ ������ ������ �� �ִ��� �Ǵ��Ѵ�. 
// �� �˰����� ai�� �ƴ� �÷��̾ ���� �Ұ��� ��� �����.
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
	// �ʱ�ȭ
	srand(time(NULL));

	// �÷��̾�� �ε��� 0������ �����ȴ�.
	for (i = 0; i < PlayerNum; i++)
	{
		if (i == 0)
			InitPlayer(&Players[i], 0);
		else
			InitPlayer(&Players[i], 1);

	}

	DealerButton = rand() % PlayerNum;

	GameRound = 1;

	// ���� ��ŸƮ
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

		printf("���� : %s, ���� : %s, �� : %s\n", &Players[DealerButton].Name,  &Players[SmallBlind].Name,
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
			if (HighRank == None_Rank) // ó�� ���� �� �ʱ�ȭ
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
		for (i = 0; i < PlayerNum; i++) // ���� ������ �ִ��� Ȯ��
		{
			if (Players[i].State == Fold)
				continue;

			PlayerRank = Players[i].PlayerRank;
			if (HighRank == PlayerRank && HighNumber == Players[i].PlayerCardMaxNumber)
			{
				printf("%s : ", Players[i].Name);
				PrintCardNumber(Players[i].PlayerCardMaxNumber);
				PrintRank(PlayerRank);

				// �迭�� ������� �ʰ� 8�ڸ����� ����Ѵ�. �� ����� �÷��̾ 8���� ����� �Ұ����ϴ�. (1, 2, 3, 4, 5, 6, 7, 8)
				Winner += i + 1;
				Winner *= 10;
				MultiWinnerCount++;
			}
		}

		// �� ���
		while (Winner != 0)
		{
			if(Winner % 10 != 0)
				Players[(Winner % 10) - 1].Money += CurrentBettingMoney / MultiWinnerCount;
			Winner /= 10;
		}
		//-------------------------------------------------

		// ����� ����
		while (1)
		{
			printf("���带 ����Ͻðڽ��ϱ�? Y/N : ");
			getchar();
			PlayerInput = getchar();
			if (PlayerInput == 'n' || PlayerInput == 'N')
			{
				printf("���带 �����մϴ�. ���� �޴��� ���ư��ϴ�.\n");
				getch();
				// ���� ����
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
				printf("�ٽ� �Է��ϼ���.\n");
			}
		}
		
	}

	// �÷��̾� ���� ������.
	if (Players[0].isAI == 0)
	{
		if (Players[0].Money > 0)
		{
			printf("%s�� ���ӿ��� �¸��ϼ̽��ϴ�.\n", Players[0].Name);
		}
		else
			printf("%s�� ���ӿ��� �й��ϼ̽��ϴ�.\n", Players[0].Name);
	}

	// ���� ����
	free(Players);
}

