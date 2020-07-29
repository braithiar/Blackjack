#include "Deck.h"

Deck::Deck()
{
	auto suit_max{ static_cast<Deck::index_t>(Card::Suit::SUIT_MAX) };
	auto rank_max{ static_cast<Deck::index_t>(Card::Rank::RANK_MAX) };
}