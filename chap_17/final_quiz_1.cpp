#include <array>
#include <vector>
#include <string>
#include <iostream>
#include "Random.h"

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
};

void shop()
{
    std::cout << "Here is our selection for today:\n";
    for (auto p : Potion::types)
    {
        std::cout << p << ") " << Potion::names[p] << " costs " << Potion::costs[p] << "\n";
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
    
    shop();

    std::cout << "\nThanks for shopping at Roscoe's potion emporium!\n";

    return 0;
}