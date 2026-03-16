#include <array>
#include <iostream>


namespace Animal
{
    enum Type
    {
        chicken,
        dog,
        cat,
        elephant,
        duck,
        snake,
        max_types,
    };

    struct Data
    {
        std::string_view name{};
        int legs{};
        std::string_view sound{};
    };

    using namespace std::string_view_literals;

    constexpr std::array types {chicken, dog, cat, elephant, duck, snake};
    static_assert(std::size(types) == max_types);

    constexpr std::array animalData {
        Data{"chicken", 2, "cluck"},
        Data{"dog", 4, "woof"},
        Data{"cat", 4, "meow"},
        Data{"elephant", 4, "pawoo"},
        Data{"duck", 2, "quack"},
        Data{"snake", 0, "hissss"},
    };
    static_assert(std::size(animalData) == max_types);
} // namespace Animal


// Adapted from a similar function in the tutorial (learncpp.com, lesson 17.6)
// We pass name by non-const reference so we can have the function modify its value
std::istream& operator>> (std::istream& in, Animal::Type& name)
{
    std::string input {};
    std::getline(in >> std::ws, input);

    // Iterate through the list of names to see if we can find a matching name
    for (std::size_t index=0; index < Animal::animalData.size(); ++index)
    {
        if (input == Animal::animalData[index].name)
        {
            // If we found a matching name, we can get the enumerator value based on its index
            name = static_cast<Animal::Type>(index);
            return in;
        }
    }

    // We didn't find a match, so input must have been invalid
    // so we will set input stream to fail state
    in.setstate(std::ios_base::failbit);

    // On an extraction failure, operator>> zero-initializes fundamental types
    // Uncomment the following line to make this operator do the same thing
    // name = {};
    return in;
}


void printAnimalData(Animal::Type type)
{
    const Animal::Data& data {Animal::animalData[type]};
    std::cout << "A " << data.name << " has " << data.legs << " legs and says " 
              << data.sound << ".\n";
    return;
}

int main()
{
    Animal::Type user_type{Animal::max_types}; // Initialize to max_types to handle invalid input

    // Ask user to input an animal type
    std::cout << "Enter an animal: ";
    std::cin >> user_type;

    // Handle input
    if (!std::cin)
    {
        std::cin.clear();
        std::cout << "That animal couldn't be found.\n";
    }
    else
        printAnimalData(user_type);
    
    // Print other animals
    std::cout << "\nHere is the data for the rest of the animals:\n";
    for (const auto& type : Animal::types)
    {
        if (type != user_type)
            printAnimalData(type);
    }

    return 0;
}