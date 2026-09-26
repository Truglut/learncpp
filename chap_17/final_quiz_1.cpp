#include <array>
#include <vector>
#include <string>
#include <iostream>
#include "Random.h"

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

namespace Potion
{
    enum Type
    {
        healing,
        mana,
        speed,
        invisibility,
        max_potion_types,
    };

    constexpr std::array types{healing, mana, speed, invisibility};

    constexpr std::array costs{20, 30, 12, 50};

    using namespace std::literals::string_view_literals;
    constexpr std::array names{"healing"sv, "mana"sv, "speed"sv, "invisibility"sv};

    static_assert(types.size() == max_potion_types);
    static_assert(costs.size() == max_potion_types);
    static_assert(names.size() == max_potion_types);
} // namespace Potion

class Player
{
private:
    static constexpr int s_minStartingGold{80};
    static constexpr int s_maxStartingGold{120};

    std::string m_name{};
    int m_gold{};
    std::array<int, Potion::max_potion_types> m_inventory{};

public:
    explicit Player(std::string_view name) : m_name{name},
                                             m_gold{Random::get(s_minStartingGold, s_maxStartingGold)}
    {
    }

    int gold() const { return m_gold; }
    std::string_view name() { return m_name; }
    int inventory(Potion::Type p) const { return m_inventory[p]; }
    void buy(Potion::Type p) { 
        ++m_inventory[p];
        m_gold = m_gold - Potion::costs[p]; 
    }
};

int charToNum(char c) {
    return c - '0';
}

Potion::Type getPotionType()
{
    std::cout << "Enter the number of the potion you'd like to buy, or 'q' to quit: ";
    char chosen_char{};
    while (true)
    {
        std::cin >> chosen_char;
        
        if (clearFailedExtraction()) {
            ignoreLine();
            continue;
        }

        if (!std::cin.eof() && std::cin.peek() != '\n') {
            std::cout << "I didn't understand what you said. Try again: ";
            ignoreLine();
            continue;
        }

        if (chosen_char == 'q') {
            return Potion::max_potion_types;
        }

        int chosen_number {charToNum(chosen_char)};

        if (0 <= chosen_number && chosen_number < Potion::max_potion_types) {
            return static_cast<Potion::Type>(chosen_number);
        }

        std::cout << "I didn't understand what you said. Try again: ";
        ignoreLine();
    }
}

void printInventory(Player& player) {
    std::cout << "Your inventory contains:\n";
    for (auto p : Potion::types) {
        if (player.inventory(p) > 0) {
            std::cout << player.inventory(p) << "x potion of " << Potion::names[p] << '\n';
        }
    }

    std::cout << "You escaped with " << player.gold() << " gold remaining.\n";
}

void shop(Player& player)
{
    while(true) {
        std::cout << "Here is our selection for today:\n";
        for (auto p : Potion::types)
        {
            std::cout << p << ") " << Potion::names[p] << " costs " << Potion::costs[p] << "\n";
        }

        Potion::Type chosen_potion {getPotionType()};

        if (chosen_potion == Potion::max_potion_types) {
            return;
        }

        if (Potion::costs[chosen_potion] > player.gold()) {
            std::cout << "You can not afford that.\n\n";
            continue;
        }

        player.buy(chosen_potion);
        std::cout << "You purchased a potion of " << Potion::names[chosen_potion] << ". You have " << player.gold() << " gold left.\n\n";
    }
}

int main()
{
    std::cout << "Welcome to Roscoe's potion emporium!\n";
    std::cout << "Enter your name: ";

    std::string player_name{};
    std::getline(std::cin >> std::ws, player_name); // read a full line of text into name
    // std::cin >> player_name would only read the first word

    Player player{player_name};

    std::cout << "Hello, " << player.name() << ", you have " << player.gold() << " gold.\n";

    shop(player);

    std::cout << '\n';

    printInventory(player);

    std::cout << "\nThanks for shopping at Roscoe's potion emporium!\n";

    return 0;
}