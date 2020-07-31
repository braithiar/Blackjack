#include "Player.h"

/*****************************************************************
* if(m_isDealer) hides player's second card if they are dealer.
* Second card is "flipped" on dealer's turn using dealerReveal()
* to set m_isDealer to false.
******************************************************************/
void Player::printHand() const
{
	if (m_isDealer)
	{
		m_hand[0].print();
		std::wcout << " ## ";
	}
	else
	{
		for (index_t ind{ 0 }; ind < m_cardIndex; ++ind)
		{
			m_hand[ind].print();
			std::wcout << ' ';
		}
	}
}

bool Player::isBust() const
{
	return (m_score > s_MAX_SCORE);
}

bool Player::isNatural21() const
{
	return (m_score == s_MAX_SCORE);
}

void Player::drawCard(Deck& deck)
{
	m_hand[m_cardIndex] = deck.dealCard();
	
	if (m_hand[m_cardIndex].getRank() == Card::Rank::ACE)
	{
		if (!m_hasAce)
		{
			m_hasAce = true;

			//Increase value of first Ace to 11, instead of 1.
			m_score += (m_hand[m_cardIndex].getCardValue() + 10);
		}
		else
			m_score += m_hand[m_cardIndex].getCardValue();
	}
	else
		m_score += m_hand[m_cardIndex].getCardValue();

	++m_cardIndex;
}

bool Player::willDealerHit() const
{
	return (m_score < s_MIN_DEALER_SCORE);
}