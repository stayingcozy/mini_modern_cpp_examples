#include <concepts>
#include <ios>
#include <iostream>
#include <limits>
#include <optional>
#include <functional>
#include <format>
#include <random>

unsigned return_const_number()
{
    return 42;
}

int some_random_number()
{
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_int_distribution<int> dist(1,100);
    return dist(engine);
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

void guess_number_with_clues(int number, std::invocable<int, int> auto message) //(used) less strict but still specific for compiler OR strict typing -> std::function<std::string(int, int)> message)
{
    std::cout << "Guess the number. \n";
    std::optional<int> guess;
    while ((guess = read_number(std::cin)))
    {
        if (guess.value() == number)
        {
            std::cout << "Well Done.";
            return;
        }
        std::cout << message(number, guess.value());
        std::cout << '>';
    }
    std::cout << std::format("The number was {}\n", number);
}

void guess_number_or_give_up(int number)
{
    std::cout << "Guess the number. \n";
    std::optional<int> guess;
    while((guess = read_number(std::cin)))
    {
        if (guess.value() == number)
        {
            std::cout << "Well Done.";
            return;
        }
        std::cout << guess.value() << " is wrong. Try again. \n";
    }
    std::cout << "The number was " << number << "\n";
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
    // guess_number(return_const_number());
    // guess_number_or_give_up(return_const_number());

    auto make_message = [] (int number, int guess) {
        return std::format("Your guess was too {}\n", (guess < number ? "small" : "big"));
    };
    guess_number_with_clues(some_random_number(), make_message);
}
