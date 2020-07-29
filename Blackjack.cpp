/*
* Need to continue to hide dealer card until its turn.
* Need auto win for player/dealer natural 21.
*/

#include "Card.h"
#include <iostream>
#include <vector>

//void playBJ()
//{
//	std::wcout << 
//		"==========================================================================\n" <<
//		"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n" <<
//		"||                                                                      ||\n" << 
//		"|| Welcome to Blackjack, the shittiest of games! Whoever is closest to  ||\n" <<
//		"|| 21, without going over, wins. You will automatically win if you're   ||\n" <<
//		"|| dealt a natural 21 (blackjack). However, this applies to the dealer, ||\n" <<
//		"|| as well!                                                             ||\n" <<
//		"||                                                                      ||\n" <<
//		"||                              GOOD LUCK!                              ||\n" << 
//		"||                                                                      ||\n" <<
//		"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n" <<
//		"==========================================================================\n\n";
//	score_array aPScore{};
//	bool bQuit{ false };
//
//	while (!bQuit)
//	{
//		auto gameDeck{ createDeck() };
//		hands_t hands{};
//		card_count_t cDealt{ 1 };
//
//		shuffleDeck(gameDeck);
//		initDeal(gameDeck, cDealt, hands);
//		
//		printHands(hands);														//Print initial hands; Second dealer card hidden.
//
//		bool bGameOver{ false };
//		bGameOver = checkGameOver(hands, aPScore);								//Check for blackjack (natural 21).
//
//		if (!bGameOver)
//		{
//			playerLogic(hands, gameDeck, cDealt);								//Player goes first. Continues until bust or player stands.
//			bGameOver = checkGameOver(hands, aPScore);							//Check if player is bust before continuing to dealer.
//		}
//
//		if (!bGameOver)
//		{
//			dealerLogic(hands, gameDeck, cDealt);								//Dealer goes until 17 or great, or bust.
//			checkGameOver(hands, aPScore);										//Dump returned bool value and display game results.
//		}
//
//		std::wcout << "\n\tGames Won: [" << aPScore[score_t::WLD_WIN] << "]\t" <<
//			"Games Lost: [" << aPScore[score_t::WLD_LOSE] << "]\t" <<
//			"Draws: [" << aPScore[score_t::WLD_DRAW] << "]\n\n";
//
//		bQuit = !(checkPlayAgain());
//	}
//}

int main()
{
	using s = Card::Suit;
	using r = Card::Rank;

	std::vector<Card> card{
		{s::CLUBS, r::ACE},
		{s::CLUBS, r::TWO},
		{s::CLUBS, r::THREE},
		{s::CLUBS, r::FOUR},
		{s::CLUBS, r::FIVE},
		{s::CLUBS, r::SIX},
		{s::CLUBS, r::SEVEN},
		{s::CLUBS, r::EIGHT},
		{s::CLUBS, r::NINE},
		{s::CLUBS, r::TEN },
		{s::CLUBS, r::JACK},
		{s::CLUBS, r::QUEEN},
		{s::CLUBS, r::KING}
	};

	for (const auto& c : card)
	{
		std::wcout << c.getCardValue() << ' ';
		c.print();

		std::wcout << '\n';
	}

	return 0;
}

//deck_array createDeck()
//{
//	deck_array aDeck{};
//	int nRank{ 0 };
//	int nSuit{ 0 };
//
//	for (auto& card : aDeck)
//	{
//		card.rank = static_cast<cRank_t>(nRank);
//		++nRank;
//
//		card.suit = static_cast<cSuit_t>(nSuit);
//
//		if (static_cast<cRank_t>(nRank) == cRank_t::RANK_MAX)
//		{
//			nRank = 0;
//			++nSuit;
//		}
//	}
//
//	return aDeck;
//}
//
//void printDeck(const deck_array& aDeck)
//{
//	for (auto& card : aDeck)
//	{
//		printCard(card);
//		std::cout << '\n';
//	}
//}
//
////printHands modifies variables controlling dealer's inital hidden card.
//void printHands(hands_t& hands)
//{
//	if (hands.pTurnOver)
//	{
//		std::wcout << "\n\tDealer reveals his hidden card...\n";
//		hands.bDealerHidden = false;
//	}
//
//	std::wcout << "\n================================\n";
//	std::wcout << "\n\n\tPlayer has:\n";
//	std::wcout << "\t-----------\n\t";
//
//	for (auto& card : hands.pHand)
//	{
//		if (card.rank != cRank_t::RANK_MAX && card.suit != cSuit_t::SUIT_MAX)
//		{
//			printCard(card);
//			std::wcout << ' ';
//		}
//	}
//
//	std::wcout << "\n\tValue: " << hands.pSum << "\n\n";
//
//	std::wcout << "\tDealer has:\n";
//	std::wcout << "\t-----------\n\t";
//
//	if (hands.bDealerHidden && hands.dSum != 21)
//	{
//		printCard(hands.dHand[0]);
//
//		std::wcout << "\n\tValue: " << (hands.dSum - hands.dHiddenSum) << "\n\n";
//	}
//	else
//	{
//		for (auto& card : hands.dHand)
//		{
//			if (card.rank != cRank_t::RANK_MAX && card.suit != cSuit_t::SUIT_MAX)
//			{
//				printCard(card);
//				std::wcout << ' ';
//			}
//		}
//
//		std::wcout << "\n\tValue: " << hands.dSum << "\n\n";
//	}
//
//	std::wcout << "\n================================\n";
//}
//
//void shuffleDeck(deck_array& aDeck)
//{
//	static std::mt19937 rGen{ std::mt19937::result_type(std::time(nullptr)) };
//
//	std::shuffle(aDeck.begin(), aDeck.end(), rGen);
//}
//
///******************************************************************************
//* getNonAceValue returns numeric value of cars 2 to 10, and 10 for face cards.
//* The value of an ace is evaluated with getAceValue(). This fucntion does not
//* modify any values.
//*******************************************************************************/
//card_value_t getNonAceValue(const cCards_t& card)
//{
//	if (card.rank < cRank_t::TEN && card.rank != cRank_t::ACE)
//		return static_cast<int>(card.rank) + 1;
//
//	switch (card.rank)
//	{
//		case cRank_t::TEN:
//		case cRank_t::JACK:
//		case cRank_t::QUEEN:
//		case cRank_t::KING:
//			return 10;
//		default:
//			return 0;
//	}
//}
//
///*****************************************************************************
//* getAceValue checks the sum of cards in hand to determine if an Ace is worth
//* 1 or 11. Sums <= 21 with an 11 valued Ace will modify ace to equal true.
//* Returns 1 or 11 to caller. Hands that already have an ace in them will
//* default to a value of 1, as two 11-valued aces cannot exist in one hand.
//******************************************************************************/
//card_value_t getAceValue(const card_value_t& sum, bool& ace)
//{
//	if ((sum + 11) <= 21 && !ace)
//	{
//		ace = true;
//		return 11;
//	}
//	else
//		return 1;
//}
//
///****************************************************************************
//* getCardValue calls getNonAceValue or getAceValue depending on card passed.
//* Modifies the values to hands members.
//*****************************************************************************/
//void getCardValue(hands_t& hands, std::size_t index, const who_t who)
//{
//	switch (who)
//	{
//		case who_t::WHO_DEALER:
//			if (index == static_cast<std::size_t>(1))
//			{
//				if (hands.dHand[index].rank == cRank_t::ACE)
//				{
//					card_value_t temp{ getAceValue(hands.dSum, hands.dAce) };
//					hands.dSum += temp;
//					hands.dHiddenSum = temp;
//				}
//				else
//				{
//					card_value_t temp{ getNonAceValue(hands.dHand[index]) };
//					hands.dSum += temp;
//					hands.dHiddenSum = temp;
//				}
//			}
//			else
//			{
//				if (hands.dHand[index].rank == cRank_t::ACE)
//					hands.dSum += getAceValue(hands.dSum, hands.dAce);
//				else
//					hands.dSum += getNonAceValue(hands.dHand[index]);
//			}
//
//			break;
//
//		case who_t::WHO_PLAYER:
//			if (hands.pHand[index].rank == cRank_t::ACE)
//				hands.pSum += getAceValue(hands.pSum, hands.pAce);
//			else
//				hands.pSum += getNonAceValue(hands.pHand[index]);
//
//			break;
//	}
//}
//
///**********************************************************************************
//* initDeal deals 2 cards each to player and dealer. The number of cards dealt
//* are tracked with the dealt parameter, which is incremented with each card dealt.
//* The dealer's face down card is handleds in get*AceValue() functions and
//* printHands() function.
//***********************************************************************************/
//void initDeal(deck_array& deck, card_count_t& dealt, hands_t& hands)
//{
//	//Four total cards need to be dealt and removed from the deck.
//	for (std::size_t iii{ 0 }; iii < 2; ++iii)
//	{
//		hands.pHand[iii] = deck[(deck.size() - dealt)];
//
//		getCardValue(hands, iii, who_t::WHO_PLAYER);
//
//		++dealt;
//
//		hands.dHand[iii] = deck[(deck.size() - dealt)];
//
//		getCardValue(hands, iii, who_t::WHO_DEALER);
//
//		++dealt;
//	}
//}
//
//void playerLogic(hands_t& hands, deck_array& deck, card_count_t& dealt)
//{
//	bool bGetInput{ true };
//
//	while (bGetInput)
//	{
//		std::wcout << "\t(H)it or (S)tand? ";
//
//		wchar_t pResponse{};
//		std::wcin >> pResponse;
//
//		if (pResponse != L'h' && pResponse != L'H' &&
//			pResponse != L's' && pResponse != L'S' ||
//			std::wcin.fail())
//		{
//			std::wcout << "\n\tThat was not valid input! Please, try again...\n";
//			std::wcin.clear();
//			std::wcin.ignore(stream_size::max(), '\n');
//		}
//
//		if (pResponse == L'h' || pResponse == L'H')
//		{
//			getCard(hands, deck, dealt, who_t::WHO_PLAYER);
//			printHands(hands);
//			bGetInput = !(checkBust(hands, who_t::WHO_PLAYER));
//		}
//		else if (pResponse == L's' || pResponse == L'S')
//		{
//			checkBust(hands, who_t::WHO_PLAYER);
//			hands.pTurnOver = true;
//			printHands(hands);
//			bGetInput = false;
//
//			//Skip last if statement, as pTurnOver is already true.
//			continue;					
//		}
//
//		if (!bGetInput)
//			hands.pTurnOver = true;
//	}
//}
//
//void dealerLogic(hands_t& hands, deck_array& deck, card_count_t& dealt)
//{
//	bool bGetInput = true;
//
//	while (bGetInput)
//	{
//		std::wcout << "\tDealer's turn. Press enter to continue...";
//
//		wchar_t sGarbage[1];
//		std::wcin.getline(sGarbage, 1);
//
//		if (hands.dSum >= Cards::DEALER_HIT)
//		{
//			std::wcout << "\n\tDealer stands.\n";
//
//			bGetInput = false;
//			printHands(hands);
//			checkBust(hands, who_t::WHO_DEALER);
//		}
//		else if (hands.dSum < Cards::DEALER_HIT)
//		{
//			std::wcout << "\n\tDealer hits.\n";
//
//			getCard(hands, deck, dealt, who_t::WHO_DEALER);
//			printHands(hands);
//			bGetInput = !(checkBust(hands, who_t::WHO_DEALER));
//		}
//
//		if (!bGetInput)
//			hands.dTurnOver = true;
//	}
//}
//
///*******************************************************************
//* isPMax & isDMax used with std::count_if inside getCard function.
//********************************************************************/
//bool isPMax(cCards_t& card)
//{
//	return (card.rank == cRank_t::RANK_MAX);
//}
//
//bool isDMax(cCards_t& card)
//{
//	return (card.rank == cRank_t::RANK_MAX);
//}
///*******************************************************************/
//
//void getCard(hands_t& hands, deck_array& deck, card_count_t& dealt, const who_t who)
//{
//	if (who == who_t::WHO_PLAYER)
//	{
//		//pHand index = pHand.size() - (number of elements set to RANK_MAX).
//		std::size_t index{ (hands.pHand.size() - std::count_if(hands.pHand.begin(),
//												hands.pHand.end(), isPMax))};
//
//		hands.pHand[index] = deck[(deck.size() - dealt)];
//		getCardValue(hands, index, who_t::WHO_PLAYER);
//
//		++dealt;
//	}
//	else if (who == who_t::WHO_DEALER)
//	{
//		std::size_t index{ (hands.dHand.size() - std::count_if(hands.dHand.begin(),
//												hands.dHand.end(), isDMax)) };
//
//		hands.dHand[index] = deck[(deck.size() - dealt)];
//		getCardValue(hands, index, who_t::WHO_DEALER);
//
//		++dealt;
//	}
//}
//
//bool checkBust(hands_t& hands, const who_t who)
//{
//	if (who == who_t::WHO_PLAYER)
//	{
//		if (hands.pSum > 21)
//		{
//			hands.pBust = true;
//			return true;
//		}
//		else
//			return false;
//	}
//	else if (who == who_t::WHO_DEALER)
//	{
//		if (hands.dSum > 21)
//		{
//			hands.dBust = true;
//			return true;
//		}
//		else
//			return false;
//	}
//	else
//		return false;
//}
//
//bool checkGameOver(hands_t& hands, score_array& score)
//{
//	/***************Check for natural 21 **************/
//	static bool bCheckedOnce{ false };
//
//	if (!bCheckedOnce)
//	{
//		if (hands.pSum == 21 && hands.dSum != 21)
//		{
//			std::wcout << "\n\tBlackjack! You win!\n";
//
//			++score[score_t::WLD_WIN];
//
//			return true;
//		}
//		else if (hands.pSum != 21 && hands.dSum == 21)
//		{
//			std::wcout << "\n\tDealer blackjack... You lose!\n";
//
//			++score[score_t::WLD_LOSE];
//
//			return true;
//		}
//		else if (hands.pSum == 21 && hands.dSum == 21)
//		{
//			std::wcout << "\n\tOh my! You both have natural 21s! It's a draw...\n";
//
//			++score[score_t::WLD_DRAW];
//
//			return true;
//		}
//		else
//		{
//			bCheckedOnce = true;
//			return false;
//		}
//	}
//	/**************************************************/
//
//	if (hands.pBust == true)
//	{
//		std::wcout << "\n\tBust! You lose!\n\n";
//
//		++score[score_t::WLD_LOSE];
//
//		return true;
//	}
//	else if (hands.dBust == true)
//	{
//		std::wcout << "\n\tDealer bust! You win!\n\n";
//
//		++score[score_t::WLD_WIN];
//
//		return true;
//	}
//	else if (hands.pSum > hands.dSum && hands.pTurnOver &&
//		hands.dTurnOver)
//	{
//		std::wcout << "\n\tYou win!\n\n";
//
//		++score[score_t::WLD_WIN];
//
//		return true;
//	}
//	else if (hands.pSum < hands.dSum && hands.pTurnOver &&
//		hands.dTurnOver)
//	{
//		std::wcout << "\n\tDealer wins!\n\n";
//
//		++score[score_t::WLD_LOSE];
//
//		return true;
//	}
//	else if (hands.pSum == hands.dSum && hands.pTurnOver &&
//		hands.dTurnOver)
//	{
//		std::wcout << "\n\tIt's a draw!\n\n";
//
//		++score[score_t::WLD_DRAW];
//
//		return true;
//	}
//	else
//		return false;
//}
//
//bool checkPlayAgain()
//{
//	bool bGetInput{ true };
//
//	while (bGetInput)
//	{
//		std::wcout << "\tPlay again (Y/N)? ";
//
//		wchar_t pResponse{};
//		std::wcin >> pResponse;
//
//		if (pResponse != L'y' && pResponse != L'Y' &&
//			pResponse != L'n' && pResponse != L'N' ||
//			std::wcin.fail())
//		{
//			std::wcout << "\n\tThat was not valid input! Please, try again...\n";
//			std::wcin.clear();
//			std::wcin.ignore(stream_size::max(), '\n');
//		}
//
//		if (pResponse == L'y' || pResponse == L'Y')
//			return true;
//		else if (pResponse == L'n' || pResponse == L'N')
//			return false;
//	}
//
//	return false;
//}