#ifndef DECK_07292020_H
#define DECK_07292020_H

#include "Card.h"
#include <algorithm>
#include <array>
#include <ctime>
#include <io.h>
#include <iostream>
#include <random>
#include <stdio.h>

class Deck
{
public:
	using deck_t =	std::array<Card, 52>;
	using index_t = deck_t::size_type;

private:
	deck_t	m_deck{};
	index_t m_cardIndex{ 0 };

public:
	Deck();

	void print() const;
	void shuffle();
	const Card& dealCard();
};

#endif
