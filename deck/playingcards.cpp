#include "playingcards.hpp"

namespace cards
{
    std::string to_string(const Suit& suit)
    {
        using namespace std::literals;
        switch (suit)
        {
            case Suit::Hearts:
                return "Hearts"s;
            case Suit::Diamonds:
                return "Diamonds"s;
            case Suit::Clubs:
                return "Clubs"s;
            case Suit::Spades:
                return "Spades"s;
            default:
                return "?"s;
        }
    }
    std::string to_string(const FaceValue& value)
    {
        using namespace std::literals;
        switch (value.value())
        {
            case 1:
                return "Ace"s;
            case 11:
                return "Jack"s;
            case 12:
                return "Queen"s;
            case 13:
                return "King"s;
            default:
                return std::to_string(value.value()); // 2-10
        }
    }
    std::ostream& operator<<(std::ostream& os, const Card& card)
    {
        os << to_string(card.value()) << " of " << to_string(card.suit());
        return os;
    }
    Suit& operator++(Suit& suit)
    {
        using IntType = typename std::underlying_type<Suit>::type; // underlying enum type
        if (suit == Suit::Spades)
            suit = Suit::Hearts;
        else
            suit = static_cast<Suit>(static_cast<IntType>(suit) + 1);
        return suit;
    }
}
