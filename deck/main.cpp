#include <array>
#include <algorithm>
#include "playingcards.hpp"
using namespace cards;

// clang++ -std=c++23 main.cpp playingcards.cpp -o main.exe && main.exe

std::array<Card, 52> create_deck()
{
    std::array<Card, 52> deck;
    int value = 1;
    Suit suit = Suit::Hearts;
    std::ranges::generate(deck, [&value, &suit]() {
        if (value > 13)
        {
            value = 1;
            ++suit;
        }
        return Card{ FaceValue(value++), suit };
    });
    return deck;
}


int main()
{
    std::array<Card, 52> deck = create_deck();
    // Card card{FaceValue{ 11 }, Suit::Clubs};
    std::cout << deck[0] << '\n';
    return 0;
}