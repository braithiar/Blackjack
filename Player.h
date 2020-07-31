#ifndef PLAYER_07302020_H
#define PLAYER_07302020_H

#include "Card.h"
#include "Deck.h"
#include <array>
#include <iostream>
#include <vector>

class Player
{
public:
	using score_t =		int;
	using hand_t =		std::vector<Card>;
	using index_t =		hand_t::size_type;
	using wld_track_t = std::array<int, 3>;

	enum WLD
	{
		WINS,
		LOSSES,
		DRAWS,
		WLD_MAX
	};

private:
	static constexpr score_t s_MAX_SCORE{ 21 };
	static constexpr score_t s_MIN_DEALER_SCORE{ 17 };

	score_t m_score{ 0 };
	wld_track_t m_wld{};
	hand_t m_hand;
	bool m_isDealer{ false };
	bool m_hasAce{ false };
	index_t m_cardIndex{ 0 };

public:
	/********************************************************************
	* Default non-dealer player; dealer should use Player(bool isDealer)
	* constructor.
	*********************************************************************/
	Player() : m_hand(10) {}

	/***********************************************************
	* Player acting as dealer should have isDealer = true to
	* keep second card "face down." Face down card is "flipped"
	* on dealers turn using dealerReveal().
	************************************************************/
	Player(bool isDealer) : m_hand(10), m_isDealer{ isDealer }{}

	score_t getScore() const { return m_score; };
	void printHand() const;
	bool isBust() const;
	void drawCard(Deck& deck);
	bool isNatural21() const;
	bool willDealerHit() const;

	/*********************************************************
	* Allows dealer's "face down" card to be revealed during
	* dealer's turn.
	**********************************************************/
	void dealerReveal() { m_isDealer = false; }
	void plusWin() { ++m_wld[WINS]; }
	void plusLoss() { ++m_wld[LOSSES]; }
	void plusDraw() { ++m_wld[DRAWS]; }
	score_t getWins() { return m_wld[WINS]; }
	score_t getLosses() { return m_wld[LOSSES]; }
	score_t getDraws() { return m_wld[DRAWS]; }
	bool getIsDealer() { return m_isDealer; }
	void reset() { m_cardIndex = 0; m_score = 0; m_hasAce = false; }
	void resetDealer() { m_cardIndex = 0; m_score = 0; m_hasAce = false; m_isDealer = true; }
};

#endif
