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
	Card() = default;
	Card(Suit c_suit, Rank c_rank);
	card_value_t getCardValue() const;
	void print() const;
};

#endif