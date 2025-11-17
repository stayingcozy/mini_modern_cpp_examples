#include <cassert>
// #include <concepts>
#include <ios>
#include <iostream>
#include <limits>
#include <optional>
#include <functional>
#include <format>
#include <random>

constexpr bool is_prime(int n)
{
    if (n == 2 | n == 3)
        return true;

    if (n <= 1 || n % 2 == 0 || n % 3 == 0)
        return false;

    for (int i = 5; i * i <= n; ++i)
    {
        if (n % i == 0)
            return false;
    }

    return true;
}



unsigned return_const_number()
{
    return 42;
}

int some_prime_number()
{
    std::random_device rd;
    std::mt19937 engine { rd() };
    std::uniform_int_distribution<int> dist(1, 9999);
    int n = {};
    while (!is_prime(n))
    {
        n = dist( engine );
    }
    return n;
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

std::string check_which_digits_correct(int number, int guess)
{
    auto ns = std::format("{:0>5}",(number));
    auto gs = std::format("{:0>5}", (guess));
    std::string matches(5, '.');
    for (size_t i=0, stop=gs.length(); i < stop; ++i)
    {
        char guess_char = gs[i];
        if (i < ns.length() && guess_char == ns[i])
        {
            matches[i] = '*';
            ns[i] = '*';
        }
    }
    for (size_t i=0, stop=gs.length(); i<stop; ++i)
    {
        char guess_char = gs[i];
        if (i < ns.length() && matches[i] != '*')
        {
            if (size_t idx = ns.find(guess_char, 0); idx != std::string::npos)
            {
                matches[i] = '^';
                ns[idx] = '^';
            }
        }
    }
    return matches;
}

void guess_number_with_clues(int number, auto messages) //(used) less strict but still specific for compiler OR strict typing -> std::function<std::string(int, int)> message)
{ // also std::invocable<std::string(int, int) message
    std::cout << "Guess the number. \n";
    std::optional<int> guess;
    while ((guess = read_number(std::cin)))
    {
        if (guess.value() == number)
        {
            std::cout << "Well Done.";
            return;
        }
        std::cout << std::format("{:0<5} is wrong. Try again\n", guess.value());

        for (auto message : messages)
        {
            auto clue = message(guess.value());
            if (clue.length())
            {
                std::cout << clue;
                break;
            }
        }
        std::cout << '>';
    }
    std::cout << std::format("The number was {:0>5}\n", number);
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

void check_properties()
{
    static_assert(is_prime(2));
    assert(check_which_digits_correct(12347, 23471) == "^^^^^");
}

int main() {
    // guess_number(return_const_number());
    // guess_number_or_give_up(return_const_number());

    check_properties();

    auto check_prime = [] (int guess) {
        return std::string((is_prime(guess) ? "" : "Not Prime\n"));
    };

    auto check_length = [] (int guess) {
        return std::string((guess < 100000) ? "" : "Too long\n");
    };

    int number = some_prime_number();
    auto check_digits = [number] (int guess) {
        return std::format("{}\n",
            check_which_digits_correct(number, guess));
    };

    std::vector<std::function<std::string(int)>> messages {
        check_length,
        check_prime,
        check_digits
    };

    // auto make_message = [] (int number, int guess) {
    //     return std::format("Your guess was too {}\n", (guess < number ? "small" : "big"));
    // };
    // auto make_message = [] (int number, int guess) {
    //     return std::format("{}\n{}\n",
    //         is_prime(guess) ? "Prime" : "Not Prime",
    //         check_which_digits_correct(number, guess));
    // };
    guess_number_with_clues(number, messages);
}
