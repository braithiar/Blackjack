#include "Card.h"

using rank = Card::Rank;
using suit = Card::Suit;

//Constructor sets up console output to use Unicode for card symbols.
Card::Card(Suit c_suit, Rank c_rank) : Card::m_suit{ c_suit }, Card::m_rank{ c_rank }
{
	_setmode(_fileno(stdout), _O_U16TEXT);
}

/**************************************************
* Card::getCardValue()
* Author: J. Thomas Paxton
* Date: 07/29/2020
*
* param none
* return card_value_t (int)
* 
* Returns the value of the card to caller. Aces
* are always returned with a value of 1.
***************************************************/
Card::card_value_t Card::getCardValue() const
{
	switch (Card::m_rank)
	{
		case rank::TEN:
		case rank::JACK:
		case rank::QUEEN:
		case rank::KING:
			return 10;
		default:
			return (static_cast<int>(Card::m_rank) + 1);
	}
}

/**************************************************
* Card::print()
* Author: J. Thomas Paxton
* Date: 07/29/2020
*
* param none
* return void
*
* Prints card Suit & Rank to console in unicode.
* Suits are represented with unicode symbols.
***************************************************/
void Card::print() const
{
	switch (Card::m_rank)
	{
		case rank::ACE:
			std::wcout << 'A';
			break;
		case rank::TWO:
			std::wcout << '2';
			break;
		case rank::THREE:
			std::wcout << '3';
			break;
		case rank::FOUR:
			std::wcout << '4';
			break;
		case rank::FIVE:
			std::wcout << '5';
			break;
		case rank::SIX:
			std::wcout << '6';
			break;
		case rank::SEVEN:
			std::wcout << '7';
			break;
		case rank::EIGHT:
			std::wcout << '8';
			break;
		case rank::NINE:
			std::wcout << '9';
			break;
		case rank::TEN:
			std::wcout << "10";
			break;
		case rank::JACK:
			std::wcout << 'J';
			break;
		case rank::QUEEN:
			std::wcout << 'Q';
			break;
		case rank::KING:
			std::wcout << 'K';
			break;
		case rank::RANK_MAX:
			std::wcout << "\nOops! Max reached; something is broken!\n";
			break;
		default:
			std::wcout << "\nUh oh! Something went wrong!\n";
	}

	switch (Card::m_suit)
	{
		case suit::CLUBS:
			std::wcout << L"\u2663";
			break;
		case suit::HEARTS:
			std::wcout << L"\u2665";
			break;
		case suit::DIAMONDS:
			std::wcout << L"\u2666";
			break;
		case suit::SPADES:
			std::wcout << L"\u2660";
			break;
		case suit::SUIT_MAX:
			std::wcout << "\nOops! Max reached; something is broken!\n";
			break;
		default:
			std::wcout << "\nUh oh! Something went wrong!\n";
	}
}