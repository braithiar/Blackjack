#ifndef CARDS_06282020_H
#define CARDS_06282020_H

#include <array>
#include <limits>

namespace Cards
{
	enum class Who
	{
		WHO_PLAYER,
		WHO_DEALER
	};

	enum WLD
	{
		WLD_WIN,
		WLD_LOSE,
		WLD_DRAW,
		WLD_MAX
	};

	enum class Suits
	{
		CLUBS,
		HEARTS,
		DIAMONDS,
		SPADES,
		SUIT_MAX
	};

	enum class Ranks
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

	struct Card
	{
		Suits suit{ Suits::SUIT_MAX };
		Ranks rank{ Ranks::RANK_MAX };
	};

	struct Hands
	{
		std::array<Card, 10> pHand{};
		bool pAce{ false };
		int pSum{ 0 };
		bool pBust{ false };
		bool pTurnOver{ false };
		std::array<Card, 10> dHand{};
		bool dAce{ false };
		bool bDealerHidden{ true };
		int dSum{ 0 };
		int dHiddenSum{ 0 };
		bool dBust{ false };
		bool dTurnOver{ false };
	};

	inline constexpr int DEALER_HIT = 17;
}

using cRank_t = Cards::Ranks;
using cSuit_t = Cards::Suits;
using cCards_t = Cards::Card;
using deck_array = std::array<cCards_t, 52>;
using card_value_t = int;
using hands_t = Cards::Hands;
using who_t = Cards::Who;
using card_count_t = std::size_t;
using stream_size = std::numeric_limits<std::streamsize>;
using score_t = Cards::WLD;
using score_array = std::array<int, Cards::WLD::WLD_MAX>;

#endif
