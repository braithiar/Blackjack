/*
* Need to continue to hide dealer card until its turn.
* Need auto win for player/dealer natural 21.
*/

#include "Card.h"
#include "Deck.h"
#include "Player.h"
#include <iostream>
#include <limits>
#include <vector>

using stream_size = std::numeric_limits<std::streamsize>;

void playBJ(Player& player, Player& dealer, Deck& deck);
void playerLogic(Player& player, Player& dealer, Deck& deck);
void dealerLogic(Player& dealer, Player& player, Deck& deck);
bool checkPlayAgain();
bool isGameOver(Player& player, Player& dealer);
bool isNatural21(Player& player, Player& dealer);
void handsOutput(Player& player, Player& dealer);

int main()
{
	Player player{};
	Player dealer{ true };
	Deck deck{};

	playBJ(player, dealer, deck);

	return 0;
}

void playBJ(Player& player, Player& dealer, Deck& deck)
{
	std::wcout <<
		"==========================================================================\n" <<
		"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n" <<
		"||                                                                      ||\n" <<
		"|| Welcome to Blackjack, the shittiest of games! Whoever is closest to  ||\n" <<
		"|| 21, without going over, wins. You will automatically win if you're   ||\n" <<
		"|| dealt a natural 21 (blackjack). However, this applies to the dealer, ||\n" <<
		"|| as well!                                                             ||\n" <<
		"||                                                                      ||\n" <<
		"||                              GOOD LUCK!                              ||\n" <<
		"||                                                                      ||\n" <<
		"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n" <<
		"==========================================================================\n\n";

	bool bQuit{ false };

	while (!bQuit)
	{
		bool bGameOver{ false };

		deck.shuffle();
		
		//Deal
		for (int dealTwo{ 0 }; dealTwo < 2; ++dealTwo)
		{
			player.drawCard(deck);
			dealer.drawCard(deck);
		}

		handsOutput(player, dealer);

		//Check nat 21
		if (player.isNatural21() || dealer.isNatural21())
			bGameOver = isNatural21(player, dealer);

		//Player turn
		if (!bGameOver)
		{
			playerLogic(player, dealer, deck);
			bGameOver = isGameOver(player, dealer);
		}

		//Dealer turn
		if (!bGameOver)
		{
			dealerLogic(dealer, player, deck);
			bGameOver = isGameOver(player, dealer);
		}

		std::wcout << "\n__________________________________________________________\n" <<
			"\tGames Won: [" << player.getWins() << "]\t" <<
			"Games Lost: [" << player.getLosses() << "]\t" <<
			"Draws: [" << player.getDraws() << "]\n\n";

		bQuit = !checkPlayAgain();

		if (!bQuit)
		{
			player.reset();
			dealer.resetDealer();
		}
	}
}

void handsOutput(Player& player, Player& dealer)
{
	std::wcout << "\nYour hand:\t";
	player.printHand();
	std::wcout << "\tValue: " << player.getScore() << "\nDealer's hand:\t";
	dealer.printHand();
	if (!dealer.getIsDealer())
		std::wcout << "\tValue: " << dealer.getScore() << '\n';
	else
		std::wcout << '\n';
}

bool isGameOver(Player& player, Player& dealer)
{
	
	if (player.isBust())
	{
		std::wcout << "\nBust! You lose!\n\n";
		player.plusLoss();

		return true;
	}
	else if (!dealer.getIsDealer())
	{
		if (dealer.isBust())
		{
			std::wcout << "\nDealer bust! You win!\n\n";
			player.plusWin();

			return true;
		}
		else if (player.getScore() > dealer.getScore())
		{
			std::wcout << "\nYou win!\n\n";
			player.plusWin();

			return true;
		}
		else if (player.getScore() < dealer.getScore())
		{
			std::wcout << "\nYou lose!\n\n";
			player.plusLoss();

			return true;
		}
		else if (player.getScore() == dealer.getScore())
		{
			std::wcout << "\nIt's a draw!\n\n";
			player.plusDraw();

			return true;
		}
		else
			return false;
	}
	else
		return false;
}

bool isNatural21(Player& player, Player& dealer)
{
	if (player.isNatural21() && !dealer.isNatural21())
	{
		std::wcout << "\nYou drew a natural 21! You win!\n\n";
		player.plusWin();

		return true;
	}
	else if (dealer.isNatural21() && !player.isNatural21())
	{
		dealer.dealerReveal();
		handsOutput(player, dealer);

		std::wcout << "\nDealer drew a natural 21! You lose!\n\n";
		player.plusLoss();

		return true;
	}
	else if (player.isNatural21() && dealer.isNatural21())
	{
		dealer.dealerReveal();
		handsOutput(player, dealer);

		std::wcout << "\nYou both drew 21! It's a draw!\n\n";
		player.plusDraw();

		return true;
	}
	else
		return false;
}

void playerLogic(Player& player, Player& dealer, Deck& deck)
{
	bool bGetInput{ true };

	while (bGetInput)
	{
		std::wcout << "\t(H)it or (S)tand? ";

		wchar_t pResponse{};
		std::wcin >> pResponse;
		std::wcin.ignore(stream_size::max(), '\n');

		if (pResponse != 'h' && pResponse != 'H' &&
			pResponse != 's' && pResponse != 'S' ||
			std::wcin.fail())
		{
			std::wcout << "\n\tThat was not valid input! Please, try again...\n";
			std::wcin.clear();
			std::wcin.ignore(stream_size::max(), '\n');
		}

		if (pResponse == 'h' || pResponse == 'H')
		{
			std::wcout << "\n\t<><><><><>\n\tYou hit...\n\t<><><><><>\n";
			player.drawCard(deck);
			bGetInput = !(player.isBust());
		}
		else if (pResponse == 's' || pResponse == 'S')
		{
			std::wcout << "\n\t<><><><><><>\n\tYou stand...\n\t<><><><><><>\n";
			bGetInput = false;
		}

		if(bGetInput)
			handsOutput(player, dealer);
	}
}

void dealerLogic(Player& dealer, Player& player, Deck& deck)
{
	bool bGetInput = true;

	//Flip dealer's card
	dealer.dealerReveal();

	std::wcout << "\n\n\n\n\n";
	handsOutput(player, dealer);

	while (bGetInput)
	{			
		std::wcout << "=========================================================" <<
			"\n\tDealer's turn. Press enter to continue...\n" <<
			"=========================================================";		

		wchar_t sGarbage[1];
		std::wcin.getline(sGarbage, 1);

		if (dealer.willDealerHit())
		{
			std::wcout << "============================\n\tDealer hits.\n============================\n";

			dealer.drawCard(deck);
			bGetInput = !(dealer.isBust());
		}
		else
		{
			std::wcout << "==============================\n\tDealer stands.\n==============================";

			bGetInput = false;
		}

		handsOutput(player, dealer);
	}
}

bool checkPlayAgain()
{
	bool bGetInput{ true };

	while (bGetInput)
	{
		std::wcout << "\tPlay again (Y/N)? ";		

		wchar_t pResponse{};
		std::wcin >> pResponse;

		if (pResponse != 'y' && pResponse != 'Y' &&
			pResponse != 'n' && pResponse != 'N' ||
			std::wcin.fail())
		{
			std::wcout << "\n\tThat was not valid input! Please, try again...\n";
			std::wcin.clear();
			std::wcin.ignore(stream_size::max(), '\n');
		}

		if (pResponse == 'y' || pResponse == 'Y')
			return true;
		else if (pResponse == 'n' || pResponse == 'N')
			return false;
	}

	return false;
}