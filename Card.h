#ifndef CARD_07292020_H
#define CARD_07292020_H

#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <stdio.h>

/********************************************************
* Class: Card
* Author: J. Thomas Paxton
* Date: 07/29/2020
*
* Creates an object representing a card from a standard
* deck of 52 playing cards. 
* Public enumerations represent the Suits (Clubs, Spades,
* Hearts, Diamonds) & Ranks (Ace to King).
*
*********************************************************/
class Card
{
public:
	using card_value_t = int;

	enum class Suit
	{
		CLUBS,
		HEARTS,
		DIAMONDS,
		SPADES,
		SUIT_MAX
	};

	enum class Rank
	{
		ACE,
		TWO,
		THREE,
		FOUR,
		FIVE,
		SIX,
		SEVEN,
		EIGHT,
		NINE,
		TEN,
		JACK,
		QUEEN,
		KING,
		RANK_MAX
	};

private:
	Suit m_suit{ Suit::CLUBS };
	Rank m_rank{ Rank::ACE };

public:
	/**************************************************
	* Card::Card()
	*
	* constructor
	* param none
	*
	* Defaults card suit to clubs and rank to ace. Con-
	* structor sets up windows console to use unicode 
	* card symbols. Card class uses std::wcout.
	***************************************************/
	Card() = default;

	/**************************************************
	* Card::Card(Suit c_suit, Rank c_rank)
	*
	* constructor
	* param Suit, Rank
	*
	* Paramameter types defined in class as public 
	* enums. Con-
	* structor sets up windows console to use unicode 
	* card symbols. Card class uses std::wcout.
	***************************************************/
	Card(Suit c_suit, Rank c_rank);

	/**************************************************
	* Card::getCardValue()
	*
	* param none
	* return card_value_t (int)
	*
	* Returns the value of the card to caller. Aces
	* are always returned with a value of 1.
	***************************************************/
	card_value_t getCardValue() const;

	/**************************************************
	* Card::print()
	*
	* param none
	* return void
	*
	* Prints card Suit & Rank to console in unicode.
	* Suits are represented with unicode symbols.
	***************************************************/
	void print() const;

	Suit getSuit() const { return m_suit; }
	Rank getRank() const { return m_rank; }
};

#endif