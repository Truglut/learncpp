#include <iostream>
#include <cstddef>
#include <string>
#include <algorithm>

std::size_t getNameCount()
{
    std::size_t count{};
    std::cout << "How many names would you like to enter? ";
    std::cin >> count;

    return count;
}

int main()
{
    std::size_t nameCount{getNameCount()};

    // Dynamically allocate memory for the array of names
    std::string *names{
        new std::string[nameCount]{}};

    // Get names from user
    for (std::size_t i{0}; i < nameCount; ++i)
    {
        std::cout << "Enter name #" << i + 1 << ": ";
        std::getline(std::cin >> std::ws, names[i]);
    }

    // In-place sort
    std::sort(names, names + nameCount);

    // Print out sorted names
    std::cout << "\nHere is your sorted list: \n";
    for (std::size_t i{0}; i < nameCount; ++i)
    {
        std::cout << "Name #" << i + 1 << ": " << names[i] << "\n";
    }

    delete[] names;
    // names = nullptr (unnecessary because names is going out of scope anyway)

    return 0;
}