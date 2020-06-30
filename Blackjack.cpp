#include "Cards.h"
#include <cstddef>
#include <iostream>
#include <array>
#include <algorithm>
#include <random>
#include <ctime>
#include <io.h>
#include <fcntl.h>

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
void getCardValue(hands_t& hands, std::size_t index, who_t who)
{
	switch (who)
	{
		case who_t::WHO_DEALER:
			if (index == 1)
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
void initDeal(deck_array& deck, std::size_t& dealt, Cards::Hands& hands)
{
	//Four total cards need to be dealt and removed from the deck.
	for(std::size_t iii{0}; iii < 2; ++iii)
	{
		hands.pHand[iii] = deck[(deck.size() - dealt)];

		getCardValue(hands, iii, who_t::WHO_PLAYER);

		++dealt;

		hands.dHand[iii] = deck[(deck.size() - dealt)];

		getCardValue(hands, iii, who_t::WHO_DEALER);

		++dealt;
	}
}

void playBJ()
{
	auto gameDeck{ createDeck() };
	hands_t hands{};
	std::size_t cDealt{ 1 };

	shuffleDeck(gameDeck);
	initDeal(gameDeck, cDealt, hands);

	printHands(hands);
	printHands(hands);

}

int main()
{
	_setmode(_fileno(stdout), _O_U16TEXT);

	playBJ();

	return 0;
}
