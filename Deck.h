#ifndef DECK_07292020_H
#define DECK_07292020_H

#include "Card.h"
#include <array>

class Deck
{
public:
	using deck_t = std::array<Card, 52>;
	using index_t = deck_t::size_type;

private:
	deck_t m_deck{};

public:
	Deck();
};

#endif
