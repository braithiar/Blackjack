/*
* Need to continue to hide dealer card until its turn.
* Need auto win for player/dealer natural 21.
*/

#include "Cards.h"
#include <cstddef>
#include <iostream>
#include <array>
#include <algorithm>
#include <random>
#include <ctime>
#include <io.h>
#include <fcntl.h>
#include <limits>

void printCard(const cCards_t& thisCard);
deck_array createDeck();
void printDeck(const deck_array& aDeck);
void printHands(hands_t& hands);
void shuffleDeck(deck_array& aDeck);
card_value_t getNonAceValue(const cCards_t& card);
card_value_t getAceValue(const card_value_t& sum, bool& ace);
void getCardValue(hands_t& hands, std::size_t index, const who_t who);
void initDeal(deck_array& deck, card_count_t& dealt, hands_t& hands);
void playerLogic(hands_t& hands, deck_array& deck, card_count_t& dealt);
void dealerLogic(hands_t& hands, deck_array& deck, card_count_t& dealt);
void getCard(hands_t& hands, deck_array& deck, card_count_t& dealt, const who_t who);
bool checkBust(hands_t& hands, const who_t who);
bool checkGameOver(hands_t& hands);
bool checkPlayAgain();

void playBJ()
{
	auto gameDeck{ createDeck() };
	hands_t hands{};
	card_count_t cDealt{ 1 };
	bool bQuit{ false };

	while (!bQuit)
	{
		shuffleDeck(gameDeck);
		initDeal(gameDeck, cDealt, hands);

		bool bGameOver{ false };
		
		printHands(hands);									//Print initial hands; Second dealer card hidden.

		playerLogic(hands, gameDeck, cDealt);				//Player goes first. Continues until bust or player stands.
		bGameOver = checkGameOver(hands);					//Check if player is bust before continuing to dealer.

		if (!bGameOver)
		{
			dealerLogic(hands, gameDeck, cDealt);			//Dealer goes until 17 or great, or bust.
			checkGameOver(hands);							//Dump returned bool value and display game results.
		}

		bQuit = checkPlayAgain();
	}
}

int main()
{
	_setmode(_fileno(stdout), _O_U16TEXT);

	playBJ();

	return 0;
}

void printCard(const cCards_t& thisCard)
{
	switch (thisCard.rank)
	{
		case cRank_t::ACE:
			std::wcout << 'A';
			break;
		case cRank_t::TWO:
			std::wcout << '2';
			break;
		case cRank_t::THREE:
			std::wcout << '3';
			break;
		case cRank_t::FOUR:
			std::wcout << '4';
			break;
		case cRank_t::FIVE:
			std::wcout << '5';
			break;
		case cRank_t::SIX:
			std::wcout << '6';
			break;
		case cRank_t::SEVEN:
			std::wcout << '7';
			break;
		case cRank_t::EIGHT:
			std::wcout << '8';
			break;
		case cRank_t::NINE:
			std::wcout << '9';
			break;
		case cRank_t::TEN:
			std::wcout << "10";
			break;
		case cRank_t::JACK:
			std::wcout << 'J';
			break;
		case cRank_t::QUEEN:
			std::wcout << 'Q';
			break;
		case cRank_t::KING:
			std::wcout << 'K';
			break;
		case cRank_t::RANK_MAX:
			std::wcout << "\nOops! Max reached; something is broken!\n";
			break;
		default:
			std::wcout << "\nUh oh! Something went wrong!\n";
	}

	switch (thisCard.suit)
	{
		case cSuit_t::CLUBS:
			std::wcout << L"\u2663";
			break;
		case cSuit_t::HEARTS:
			std::wcout << L"\u2665";
			break;
		case cSuit_t::DIAMONDS:
			std::wcout << L"\u2666";
			break;
		case cSuit_t::SPADES:
			std::wcout << L"\u2660";
			break;
		case cSuit_t::SUIT_MAX:
			std::wcout << "\nOops! Max reached; something is broken!\n";
			break;
		default:
			std::wcout << "\nUh oh! Something went wrong!\n";
	}
}

deck_array createDeck()
{
	deck_array aDeck{};
	int nRank{ 0 };
	int nSuit{ 0 };

	for (auto& card : aDeck)
	{
		card.rank = static_cast<cRank_t>(nRank);
		++nRank;

		card.suit = static_cast<cSuit_t>(nSuit);

		if (static_cast<cRank_t>(nRank) == cRank_t::RANK_MAX)
		{
			nRank = 0;
			++nSuit;
		}
	}

	return aDeck;
}

void printDeck(const deck_array& aDeck)
{
	for (auto& card : aDeck)
	{
		printCard(card);
		std::cout << '\n';
	}
}

//printHands modifies variables controlling dealer's inital hidden card.
void printHands(hands_t& hands)
{
	std::wcout << "Player has:\n";
	std::wcout << "-----------\n";

	for (auto& card : hands.pHand)
	{
		if (card.rank != cRank_t::RANK_MAX && card.suit != cSuit_t::SUIT_MAX)
		{
			printCard(card);
			std::wcout << ' ';
		}
	}

	std::wcout << '\n' << "Value: " << hands.pSum << "\n\n";

	std::wcout << "Dealer has:\n";
	std::wcout << "-----------\n";

	if (hands.bDealerHidden)
	{
		printCard(hands.dHand[0]);
		hands.bDealerHidden = false;

		std::wcout << '\n' << "Value: " << (hands.dSum - hands.dHiddenSum) << "\n\n";
	}
	else
	{
		for (auto& card : hands.dHand)
		{
			if (card.rank != cRank_t::RANK_MAX && card.suit != cSuit_t::SUIT_MAX)
			{
				printCard(card);
				std::wcout << ' ';
			}
		}

		std::wcout << '\n' << "Value: " << hands.dSum << "\n\n";
	}
}

void shuffleDeck(deck_array& aDeck)
{
	static std::mt19937 rGen{ std::mt19937::result_type(std::time(nullptr)) };

	std::shuffle(aDeck.begin(), aDeck.end(), rGen);
}

/******************************************************************************
* getNonAceValue returns numeric value of cars 2 to 10, and 10 for face cards.
* The value of an ace is evaluated with getAceValue(). This fucntion does not
* modify any values.
*******************************************************************************/
card_value_t getNonAceValue(const cCards_t& card)
{
	if (card.rank < cRank_t::TEN && card.rank != cRank_t::ACE)
		return static_cast<int>(card.rank) + 1;

	switch (card.rank)
	{
		case cRank_t::TEN:
		case cRank_t::JACK:
		case cRank_t::QUEEN:
		case cRank_t::KING:
			return 10;
		default:
			return 0;
	}
}

/*****************************************************************************
* getAceValue checks the sum of cards in hand to determine if an Ace is worth
* 1 or 11. Sums <= 21 with an 11 valued Ace will modify ace to equal true.
* Returns 1 or 11 to caller. Hands that already have an ace in them will
* default to a value of 1, as two 11-valued aces cannot exist in one hand.
******************************************************************************/
card_value_t getAceValue(const card_value_t& sum, bool& ace)
{
	if ((sum + 11) <= 21 && !ace)
	{
		ace = true;
		return 11;
	}
	else
		return 1;
}

/****************************************************************************
* getCardValue calls getNonAceValue or getAceValue depending on card passed.
* Modifies the values to hands members.
*****************************************************************************/
void getCardValue(hands_t& hands, std::size_t index, const who_t who)
{
	switch (who)
	{
		case who_t::WHO_DEALER:
			if (index == static_cast<std::size_t>(1))
			{
				if (hands.dHand[index].rank == cRank_t::ACE)
				{
					card_value_t temp{ getAceValue(hands.dSum, hands.dAce) };
					hands.dSum += temp;
					hands.dHiddenSum = temp;
				}
				else
				{
					card_value_t temp{ getNonAceValue(hands.dHand[index]) };
					hands.dSum += temp;
					hands.dHiddenSum = temp;
				}
			}
			else
			{
				if (hands.dHand[index].rank == cRank_t::ACE)
					hands.dSum += getAceValue(hands.dSum, hands.dAce);
				else
					hands.dSum += getNonAceValue(hands.dHand[index]);
			}

			break;

		case who_t::WHO_PLAYER:
			if (hands.pHand[index].rank == cRank_t::ACE)
				hands.pSum += getAceValue(hands.pSum, hands.pAce);
			else
				hands.pSum += getNonAceValue(hands.pHand[index]);

			break;
	}
}

/**********************************************************************************
* initDeal deals 2 cards each to player and dealer. The number of cards dealt
* are tracked with the dealt parameter, which is incremented with each card dealt.
* The dealer's face down card is handleds in get*AceValue() functions and
* printHands() function.
***********************************************************************************/
void initDeal(deck_array& deck, card_count_t& dealt, hands_t& hands)
{
	//Four total cards need to be dealt and removed from the deck.
	for (std::size_t iii{ 0 }; iii < 2; ++iii)
	{
		hands.pHand[iii] = deck[(deck.size() - dealt)];

		getCardValue(hands, iii, who_t::WHO_PLAYER);

		++dealt;

		hands.dHand[iii] = deck[(deck.size() - dealt)];

		getCardValue(hands, iii, who_t::WHO_DEALER);

		++dealt;
	}
}

void playerLogic(hands_t& hands, deck_array& deck, card_count_t& dealt)
{
	bool bGetInput{ true };

	while (bGetInput)
	{
		std::wcout << "(H)it or (S)tand?\n";

		wchar_t pResponse{};
		std::wcin >> pResponse;

		if (pResponse != L'h' && pResponse != L'H' &&
			pResponse != L's' && pResponse != L'S' ||
			std::wcin.fail())
		{
			std::wcout << "\nThat was not valid input! Please, try again...\n";
			std::wcin.clear();
			std::wcin.ignore(stream_size::max(), '\n');
		}

		if (pResponse == L'h' || pResponse == L'H')
		{
			getCard(hands, deck, dealt, who_t::WHO_PLAYER);
			printHands(hands);
			bGetInput = !(checkBust(hands, who_t::WHO_PLAYER));
		}
		else if (pResponse == L's' || pResponse == L'S')
		{
			checkBust(hands, who_t::WHO_PLAYER);
			printHands(hands);
			bGetInput = false;
		}

		if (!bGetInput)
			hands.pTurnOver = true;
	}
}

void dealerLogic(hands_t& hands, deck_array& deck, card_count_t& dealt)
{
	bool bGetInput = true;

	while (bGetInput)
	{
		if (hands.dSum >= Cards::DEALER_HIT)
		{
			bGetInput = false;
			printHands(hands);
			checkBust(hands, who_t::WHO_DEALER);
		}
		else if (hands.dSum < Cards::DEALER_HIT)
		{
			getCard(hands, deck, dealt, who_t::WHO_DEALER);
			printHands(hands);
			bGetInput = !(checkBust(hands, who_t::WHO_DEALER));
		}

		if (!bGetInput)
			hands.dTurnOver = true;
	}
}

bool isPMax(cCards_t& card)
{
	return (card.rank == cRank_t::RANK_MAX);
}

bool isDMax(cCards_t& card)
{
	return (card.rank == cRank_t::RANK_MAX);
}

void getCard(hands_t& hands, deck_array& deck, card_count_t& dealt, const who_t who)
{
	if (who == who_t::WHO_PLAYER)
	{
		//pHand index = pHand.size() - (number of elements set to RANK_MAX).
		std::size_t index{ (hands.pHand.size() - std::count_if(hands.pHand.begin(),
												hands.pHand.end(), isPMax))};

		hands.pHand[index] = deck[(deck.size() - dealt)];
		getCardValue(hands, index, who_t::WHO_PLAYER);

		++dealt;
	}
	else if (who == who_t::WHO_DEALER)
	{
		std::size_t index{ (hands.dHand.size() - std::count_if(hands.dHand.begin(),
												hands.dHand.end(), isDMax)) };

		hands.dHand[index] = deck[(deck.size() - dealt)];
		getCardValue(hands, index, who_t::WHO_DEALER);

		++dealt;
	}
}

bool checkBust(hands_t& hands, const who_t who)
{
	if (who == who_t::WHO_PLAYER)
	{
		if (hands.pSum > 21)
		{
			hands.pBust = true;
			return true;
		}
		else
			return false;
	}
	else if (who == who_t::WHO_DEALER)
	{
		if (hands.dSum > 21)
		{
			hands.dBust = true;
			return true;
		}
		else
			return false;
	}
	else
		return false;
}

bool checkGameOver(hands_t& hands)
{
	if (hands.pBust == true)
	{
		std::wcout << "\nBust! You lose!\n";
		return true;
	}
	else if (hands.dBust == true)
	{
		std::wcout << "\nDealer bust! You win!\n";
		return true;
	}
	else if (hands.pSum > hands.dSum && hands.pTurnOver &&
		hands.dTurnOver)
	{
		std::wcout << "\nYou win!\n";
		return true;
	}
	else if (hands.pSum < hands.dSum && hands.pTurnOver &&
		hands.dTurnOver)
	{
		std::wcout << "\nDealer wins!\n";
		return true;
	}
	else
		return false;
}

bool checkPlayAgain()
{
	bool bGetInput{ true };

	while (bGetInput)
	{
		std::wcout << "Play again (Y/N)?\n";

		wchar_t pResponse{};
		std::wcin >> pResponse;

		if (pResponse != L'y' && pResponse != L'Y' ||
			pResponse != L'n' && pResponse != L'N' ||
			std::wcin.fail())
		{
			std::wcout << "\nThat was not valid input! Please, try again...\n";
			std::wcin.clear();
			std::wcin.ignore(stream_size::max(), '\n');
		}

		if (pResponse != L'y' || pResponse == L'Y')
			return true;
		else if (pResponse == L'n' || pResponse == L'N')
			return false;
	}

	return false;
}