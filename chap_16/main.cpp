#include <iostream>
#include <string_view>
#include <vector>
#include "Random.h"

namespace WordList
{
    // Define your list of words here
    std::vector<std::string_view> words { "mystery", "broccoli" , "account", "almost", "spaghetti", "opinion", "beautiful", "distance", "luggage" };

    std::string_view getRandomWord()
    {
        return words[Random::get<std::size_t>(0, words.size()-1)];
    }
}

class Session
{
private:
    // Game session data
    std::string_view m_word { WordList::getRandomWord() };
    std::vector<bool> m_letterGuessed { std::vector<bool>(26) };
    int m_totalWrongGuesses{6};
    std::vector<char> m_wrongGuesses {};

    std::size_t toIndex(char c) const { return static_cast<std::size_t>((c % 32)-1); }

public:
    Session() = default;

    Session(int wrongGuesses)
        : m_totalWrongGuesses {wrongGuesses}
    {}

    std::string_view getWord() const { return m_word; }

    bool isLetterGuessed(char c) const { return m_letterGuessed[toIndex(c)]; }
    void setLetterGuessed(char c) { m_letterGuessed[toIndex(c)] = true; }
    
    int guessesLeft() const
    { 
        return m_totalWrongGuesses - static_cast<int>(std::size(m_wrongGuesses));
    }

    const std::vector<char>& getWrongGuesses() const
    {
        return m_wrongGuesses;
    }

    bool isLetterInWord(char c) const
    {
        // check if guessed letter is in word
        bool correct {false};
        for (const auto& e: m_word)
        {
            if (e == c)
                return true;
        }
        return false;
    }

    void addWrongGuess(char c)
    {
        m_wrongGuesses.push_back(c);
    }

    bool checkLost() const
    {
        return static_cast<int>(m_wrongGuesses.size()) == m_totalWrongGuesses;
    }

    bool checkWon() const
    {
        for (const auto& e: m_word)
        {
            if ( !isLetterGuessed(e) )
                return false;
        }
        return true;
    }
};

void draw(const Session& s)
{
    std::cout << '\n';

    std::cout << "The word: ";
    for (auto c: s.getWord()) // step through each letter of word
    {
        if (s.isLetterGuessed(c))
            std::cout << c;
        else
            std::cout << '_';
    }

    std::cout << "\tWrong guesses: ";
    int guessesLeft { s.guessesLeft() };
    while (--guessesLeft)
    {
        std::cout << '+';
    }
    const auto& wrongGuesses { s.getWrongGuesses() };
    for (const auto& e: wrongGuesses)
    {
        std::cout << e;
    }

    std::cout << '\n';
}

char getGuess(const Session& s)
{
    while (true)
    {
        std::cout << "Enter your next letter: ";

        char c{};
        std::cin >> c;

        // If user did something bad, try again
        if (!std::cin)
        {
            // Fix it
            std::cin.clear();
            std::cout << "That wasn't a valid input.  Try again.\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        // Clear out any extraneous input
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // If the user entered an invalid char, try again
        if (c < 'a' || c > 'z')
        {
            std::cout << "That wasn't a valid input.  Try again.\n";
            continue;
        }

        // If the letter was already guessed, try again
        if (s.isLetterGuessed(c))
        {
            std::cout << "You already guessed that.  Try again.\n";
            continue;
        }

        // If we got here, this must be a valid guess
        return c;
    }
}

int main()
{
    std::cout << "Welcome to C++man (a variant of Hangman)\n";
    std::cout << "To win: guess the word.  To lose: run out of pluses.\n";

    Session s {};

    while (true)
    {
        draw(s);
        char c { getGuess(s) };
        s.setLetterGuessed(c);
        if ( !(s.isLetterInWord(c)) )
        {
            std::cout << "No, '" << c << "' is not in the word!\n";
            s.addWrongGuess(c);

            // Check if game lost
            if (s.checkLost())
            {
                std::cout << "You lost!\n";
                break;
            }
        }
        else
        {
            std::cout << "Yes, '" << c << "' is in the word!\n";

            // Check if game won
            if (s.checkWon())
            {
                std::cout << "You won!\n";
                break;
            }
        }
    }

    // Draw the final state of the game
    draw(s);

    return 0;
}