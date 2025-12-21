#include "MindReader.hpp"


std::unordered_map<state_t, last_choices_t> initial_state()
{
    const auto unset = std::pair<Choice, Choice>{ Choice::Shrug, Choice::Shrug };
    
    return {
        { {Outcome::Lose, Choice::Same, Outcome::Lose}, unset },
        { {Outcome::Lose, Choice::Same, Outcome::Win}, unset },
        { {Outcome::Lose, Choice::Change, Outcome::Lose}, unset },
        { {Outcome::Lose, Choice::Change, Outcome::Win}, unset },
        { {Outcome::Win, Choice::Same, Outcome::Lose}, unset },
        { {Outcome::Win, Choice::Same, Outcome::Win}, unset },
        { {Outcome::Win, Choice::Change, Outcome::Lose}, unset },
        { {Outcome::Win, Choice::Change, Outcome::Win}, unset }
    };
}

Choice prediction_method(const last_choices_t& choices)
{
    if (choices.first == choices.second)
    {
        return choices.first;
    }
    else 
    {
        return Choice::Shrug;
    }
}

last_choices_t State::choices(const state_t& key) const
{
    if (auto it = state_lookup.find(key); it!=state_lookup.end())
    {
        return it->second;
    }
    else
    {
        return { Choice::Shrug, Choice::Shrug };
    }
}

void State::update(const state_t& key, const Choice& turn_changed)
{
    if (auto it = state_lookup.find(key); it!=state_lookup.end())
    {
        const auto [prev2, prev1] = it->second;
        last_choices_t value{ prev1, turn_changed };
        it->second = value;
    }
}
