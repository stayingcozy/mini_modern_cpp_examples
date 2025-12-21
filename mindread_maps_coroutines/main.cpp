#include <iostream>
#include <optional>
#include <string>
#include <random>
#include <cassert>

#include "MindReader.hpp"

void check_properties()
{
    // Verify all init state buckets DONT have multiple values
    std::unordered_map<state_t, last_choices_t> states = initial_state();
    for (size_t bucket=0; bucket<states.bucket_count(); bucket++)
    {
        assert(states.bucket_size(bucket) <= 1);
    }
}

std::optional<int> read_number(std::istream& in)
{
    std::string line;
    std::getline(in, line);
    if (line == "0")
    {
        return 0;
    }
    else if (line == "1")
    {
        return 1;
    }
    return {};
}

void pennies_game()
{
    int player_wins = 0;
    int turns = 0;
    std::mt19937 gen{ std::random_device{}() };
    std::uniform_int_distribution dist(0, 1);
    
    std::cout << "Select 0 or 1 at random and press enter.\n";
    std::cout << "If the computer predicts your guess it wins.\n";
    while (true)
    {
        const int prediction = dist(gen);
        
        auto input = read_number(std::cin);
        if (!input)
        {
            break;
        }
        const int player_choice = input.value();
        
        ++turns;
        std::cout << "You pressed " << player_choice << ", I guessed " << prediction << '\n';
        
        if (player_choice != prediction)
        {
            ++player_wins;
        }    
    }
    std::cout << "you win " << player_wins << '\n' << "I win " << turns - player_wins << '\n';
}

void mind_reader()
{
    int turns = 0;
    int player_wins = 0;
    int guessing = 0;
    
    std::mt19937 gen{ std::random_device{}() };
    std::uniform_int_distribution dist{ 0, 1 };
    MindReader mr(gen, dist);

    std::cout << "Select 0 or 1 at random and press enter.\n";
    std::cout << "If the computer predicts your guess it wins.\n";
    std::cout << "and it can now read your MIND.\n";
    while(true)
    {
        const int prediction = mr.get_prediction();
        
        auto input = read_number(std::cin);
        if (!input)
        {
            break;
        }
        const int player_choice = input.value();
        
        ++turns;
        std::cout << "You pressed " << player_choice << ", I guessed " << prediction << '\n';
        
        if (player_choice != prediction)
        {
            ++player_wins;
        }
        if (mr.update(player_choice))
        {
            ++guessing;
        }
    }
    std::cout << "you win " << player_wins << '\n' << "machine guessed " << guessing << " times" << '\n'
        << "machine won " << (turns - player_wins) << '\n';
}

int main()
{
    // pennies_game();
    mind_reader();
    
    return 0;
}