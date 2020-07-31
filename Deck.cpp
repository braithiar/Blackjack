#include "Deck.h"

Deck::Deck()
{
	auto suit_max{ static_cast<index_t>(Card::Suit::SUIT_MAX) };
	auto rank_max{ static_cast<index_t>(Card::Rank::RANK_MAX) };
	index_t card{ 0 };

	for (index_t suit{ 0 }; suit < suit_max; ++suit)
	{
		for (index_t rank{ 0 }; rank < rank_max; ++rank)
		{
			m_deck[card] = { static_cast<Card::Suit>(suit), static_cast<Card::Rank>(rank) };

			++card;
		}
	}
}

void Deck::print() const
{
	for (auto& card : m_deck)
	{
		card.print();
		
		std::wcout << '\n';
	}
}

void Deck::shuffle()
{
	static std::mt19937 rgen{ std::mt19937::result_type(std::time(nullptr)) };

	std::shuffle(m_deck.begin(), m_deck.end(), rgen);

	m_cardIndex = 0;
}

const Card& Deck::dealCard()
{
	if (m_cardIndex >= m_deck.size())
		shuffle();

	return m_deck[m_cardIndex++];
}