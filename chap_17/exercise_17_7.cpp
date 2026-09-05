#include <array>
#include <iostream>

// Use a global constexpr C-style array to hold the perfect squares between 0 and 9 (inclusive).
constexpr int squares[]{0, 1, 4, 9};
// Note: tutorial solution includes this array in a namespace `ProgramData`, which
// is probably a good idea


int getNumber()
{
    int x{};

    while (true)
    {
        std::cout << "Enter a single digit integer, or -1 to quit: ";

        std::cin >> x;

        if ((-2 < x) and (x < 10))
        {
            return x;
        }

        std::cout << "Invalid input. Please try again.\n";
    }
}

bool checkIfPerfectSquare(int number)
{
    for (const auto &c : squares)
    {
        if (c == number)
        {
            return true;
        }
    }

    return false;
}

int main()
{
    // Repeatedly ask the user to enter a single digit integer, or -1 to quit.
    // Print whether the digit the user entered is a perfect square.

    int number{};

    while (true)
    {
        number = getNumber();

        if (number == -1)
        {
            break;
        }

        if (checkIfPerfectSquare(number))
        {
            std::cout << number << " is a perfect square.\n";
        }
        else
        {
            std::cout << number << " is not a perfect square.\n";
        }
    }

    std::cout << "Bye\n";

    return 0;
}