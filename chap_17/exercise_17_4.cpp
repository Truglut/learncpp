#include <array>
#include <iostream>
#include <string_view>

// Define Item struct
struct Item
{
    std::string_view name{};
    int gold{};
};


void printItem(const Item& item)
{
    std::cout << "A " << item.name << " costs " << item.gold << " gold.\n";
}


int main()
{
    // define array using CTAD (question 1)
    constexpr std::array items {
        Item{"sword", 5},
        Item{"dagger", 3},
        Item{"club", 2},
        Item{"spear", 7}
    };

    // define array without explicitly specifying element type for each initializer
    constexpr std::array<Item, 4> items2 {{
        {"sword", 5},
        {"dagger", 3},
        {"club", 2},
        {"spear", 7}
    }};

    // Print items in array 1
    std::cout << "--- Array 1: ---\n";
    for (const auto& item: items)
    {
        printItem(item);
    }

    // Print items in array 2
    std::cout << "\n--- Array 2: ---\n";
    for (const auto& item: items2)
    {
        printItem(item);
    }

    // Note: defining a function to print all items in an array (what the tutorial suggests)
    // might be preferable over iterating over both arrays (DRY) 
    // but I prefer this solution for a single array, which is what the exercise intended
}