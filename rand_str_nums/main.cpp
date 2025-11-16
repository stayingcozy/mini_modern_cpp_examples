#include <ios>
#include <iostream>
#include <limits>
#include <optional>

unsigned return_const_number()
{
    return 42;
}

unsigned input()
{
    unsigned number;
    while (!(std::cin >> number)) // streams in char and make sure nothing failed
    {
        std::cin.clear();        // clears the failed flag
        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(), '\n');  // mops up invalid input
        std::cout << "Please enter a number. \n";
    }
    return number;
}

std::optional<int> read_number(std::istream& in)
{
    int result {};
    if (in >> result)
    {
        return result;
    }
    in.clear();
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return {};
}

void guess_number(unsigned number)
{
    std::cout << "Guess the number. \n";
    unsigned guess = input();
    while(guess != number)
    {
        std::cout << guess << " is wrong. Try again\n";
        guess = input();
    }
    std::cout << "Well Done. \n";
}

int main() {
    guess_number(return_const_number());
}
