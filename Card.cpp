#include "Card.h"

//Constructor sets up console output to use Unicode for card symbols.
Card::Card(Suit c_suit, Rank c_rank) : m_suit{ c_suit }, m_rank{ c_rank }
{
	_setmode(_fileno(stdout), _O_U16TEXT);
}

Card::card_value_t Card::getCardValue() const
{
	switch (m_rank)
	{
		case Rank::TEN:
		case Rank::JACK:
		case Rank::QUEEN:
		case Rank::KING:
			return 10;
		default:
			return (static_cast<int>(m_rank) + 1);
	}
}

void Card::print() const
{
	switch (m_rank)
	{
		case Rank::ACE:
			std::wcout << 'A';
			break;
		case Rank::TWO:
			std::wcout << '2';
			break;
		case Rank::THREE:
			std::wcout << '3';
			break;
		case Rank::FOUR:
			std::wcout << '4';
			break;
		case Rank::FIVE:
			std::wcout << '5';
			break;
		case Rank::SIX:
			std::wcout << '6';
			break;
		case Rank::SEVEN:
			std::wcout << '7';
			break;
		case Rank::EIGHT:
			std::wcout << '8';
			break;
		case Rank::NINE:
			std::wcout << '9';
			break;
		case Rank::TEN:
			std::wcout << "10";
			break;
		case Rank::JACK:
			std::wcout << 'J';
			break;
		case Rank::QUEEN:
			std::wcout << 'Q';
			break;
		case Rank::KING:
			std::wcout << 'K';
			break;
		case Rank::RANK_MAX:
			std::wcout << "\nOops! Max reached; something is broken!\n";
			break;
		default:
			std::wcout << "\nUh oh! Something went wrong!\n";
	}

	switch (m_suit)
	{
		case Suit::CLUBS:
			std::wcout << L"\u2663";
			break;
		case Suit::HEARTS:
			std::wcout << L"\u2665";
			break;
		case Suit::DIAMONDS:
			std::wcout << L"\u2666";
			break;
		case Suit::SPADES:
			std::wcout << L"\u2660";
			break;
		case Suit::SUIT_MAX:
			std::wcout << "\nOops! Max reached; something is broken!\n";
			break;
		default:
			std::wcout << "\nUh oh! Something went wrong!\n";
	}
}