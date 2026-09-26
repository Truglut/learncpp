#include <iostream>
#include <array>
#include <assert.h>
#include <algorithm> // for std::shuffle
#include "Random.h"  // for Random::mt

struct Card {
    enum Rank {
        ace,
        two,
        three,
        four,
        five,
        six,
        seven,
        eight,
        nine,
        jack,
        queen,
        king,
        max_ranks,
    };

    static constexpr std::array<char, max_ranks> rank_names {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'J', 'Q', 'K'};
    static constexpr std::array<int, max_ranks> rank_values {11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10};
    static constexpr std::array<Rank, max_ranks> allRanks {ace, two, three, four, five, six, seven, eight, nine, jack, queen, king};
    
    static_assert(rank_names.size() == max_ranks);
    static_assert(rank_values.size() == max_ranks);
    static_assert(allRanks.size() == max_ranks);

    enum Suit {
        clubs,
        diamonds,
        hearts,
        spades,
        max_suits,
    };

    static constexpr std::array<char, max_suits> suit_names {'C', 'D', 'H', 'S'};
    static constexpr std::array<Suit, max_suits> allSuits {clubs, diamonds, hearts, spades};
    static_assert(suit_names.size() == max_suits);
    static_assert(allSuits.size() == max_suits);

    Rank rank{};
    Suit suit{};

    friend std::ostream& operator<<(std::ostream& out, const Card& card) {
        out << rank_names[card.rank] << suit_names[card.suit]; 
        return out;
    }

    int getCardValue() const {
        return rank_values[rank];
    }
};


class Deck
{
private:
    std::array<Card, 52> m_cards{};
    int m_next_card_idx{0};

public:
    Deck() {
        int i {0};
        for (auto suit : Card::allSuits) {
            for (auto rank : Card::allRanks) {
                m_cards[i] = Card { rank, suit };
                ++i;
            }
        }
    }

    Card dealCard() {
        assert(m_next_card_idx < m_cards.size());
        ++m_next_card_idx;
        return m_cards[m_next_card_idx - 1];
    }

    void shuffle() {
        std::shuffle(m_cards.begin(), m_cards.end(), Random::mt);
        m_next_card_idx = 0;
    }
};

struct Player {
    int score{};
};

namespace Settings {
    constexpr int max_score{21};
    constexpr int dealer_stops{17};
}

// Input handling functions from lesson 9.5
#include <limits> // for std::numeric_limits

void ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// returns true if extraction failed, false otherwise
bool clearFailedExtraction()
{
    if (!std::cin)
    {
        if (std::cin.eof())
        {
            std::exit(0); // Shut down the program now
        }

        std::cin.clear(); // Put us back in 'normal' operation mode
        ignoreLine();     // And remove the bad input

        return true;
    }

    return false;
}

bool playerWantsCard() {
    char input {};
    std::cout << "(h) to hit, or (s) to stand: ";
    while (true) {
        std::cin >> input;

        if (clearFailedExtraction()) {
            std::cout << "Invalid input. Try again: ";
            ignoreLine();
            continue;
        }

        if (!std::cin.eof() && std::cin.peek() != '\n') {
            std::cout << "Invalid input. Try again: ";
            ignoreLine();
            continue;
        }

        if (input == 'h') {
            return true;
        }
        else if (input == 's') {
            return false;
        }

        std::cout << "Invalid input. Try again: ";
    }
}

// returns true if the player has a greater score than the dealer (ties are considered dealer wins here)
bool playBlackJack() {
    Deck deck{};
    
    deck.shuffle();
    
    // Draw one card for the dealer and two cards for the player
    Player dealer{deck.dealCard().getCardValue()};

    std::cout << "The dealer is showing: " << dealer.score << '\n';
    
    Player player {deck.dealCard().getCardValue() + deck.dealCard().getCardValue()};

    std::cout << "You have score: " << player.score << '\n';

    // Player's turn
    while (playerWantsCard()) {
        Card nextCard {deck.dealCard()};
        player.score = player.score + nextCard.getCardValue();
        std::cout << "You were dealt " << nextCard << ". ";
        std::cout << "You now have: " << player.score << '\n';

        if (player.score > Settings::max_score) {
            std::cout << "You went bust!\n";
            return false;
        }
    }

    // Dealer's turn: draw until hitting given score
    while (dealer.score < Settings::dealer_stops) {
        Card nextCard {deck.dealCard()};
        dealer.score = dealer.score + nextCard.getCardValue();
        std::cout << "The dealer flips a " << nextCard << ". "; 
        std::cout << "They now have: " << dealer.score << '\n';
    }

    if (dealer.score > Settings::max_score) {
        std::cout << "The dealer went bust!\n";
        return true;
    }

    return player.score > dealer.score;
}


int main()
{
    if (playBlackJack()) {
        std::cout << "You win!\n";
    }
    else {
        std::cout << "You lose!\n";
    }

    return 0;
}