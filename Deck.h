#ifndef DECK_07292020_H
#define DECK_07292020_H

#include "Card.h"
#include <algorithm>
#include <array>
#include <ctime>
#include <iostream>
#include <random>

/**********************************************
* Class: Deck
* Author: J. Thomas Paxton
* Date: 07/29/2020
*
* Creates a deck of 52 Card class objects: one
* card object for each of the 52 cards in a 
* standard deck of cards. 
***********************************************/
class Deck
{
public:
	using deck_t =	std::array<Card, 52>;
	using index_t = deck_t::size_type;

private:
	deck_t	m_deck{};
	index_t m_cardIndex{ 0 };

public:
	/***************************************************************
	* Deck::Deck()
	*
	* constructor
	*
	* Fills deck array with 52 Card class objects, one for each card
	* in a standard deck of playing cards.
	****************************************************************/
	Deck();

	/*************************************************
	* Deck::print()
	*
	* param none
	* return void
	*
	* Prints all 52 Cards in Deck array.
	**************************************************/
	void print() const;

	/*************************************************
	* Deck::shuffle()
	*
	* param none
	* return void
	*
	* Randomizes array of cards and also resets inter-
	* nal tracking of current index used in dealing
	* cards.
	**************************************************/
	void shuffle();

	/*************************************************
	* Deck::dealCard()
	*
	* param none
	* return const Card&
	*
	* Reminder: returns a constant reference of type 
	* Card, which cannot be used as an l-value.
	**************************************************/
	const Card& dealCard();
};

#endif
