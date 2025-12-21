#include <unordered_map>

enum class Choice
{
    Same,
    Change,
    Shrug
};
enum class Outcome
{
    Win,
    Lose,
    Unset
};

using state_t = std::tuple<Outcome, Choice, Outcome>;
using last_choices_t = std::pair<Choice, Choice>;

template<>
struct std::hash<state_t>
{
    std::size_t operator()(state_t const& state) const noexcept 
    {
        std::size_t h1 = std::hash<Outcome>{}(std::get<0>(state));
        std::size_t h2 = std::hash<Choice>{}(std::get<1>(state));
        std::size_t h3 = std::hash<Outcome>{}(std::get<2>(state));
        return h1 + (h2 << 1) + (h3 << 2);
    }
};

std::unordered_map<state_t, last_choices_t> initial_state();
Choice prediction_method(const last_choices_t& choices);

class State
{
    std::unordered_map<state_t, last_choices_t> state_lookup = initial_state();
    
public:
    last_choices_t choices(const state_t& key) const;
    void update(const state_t& key, const Choice& turn_changed);
};

template<std::invocable<> T, typename U>
class MindReader {
    State state_table;
    T generator;
    U distribution;
    int prediction = flip();
    state_t state {
        Outcome::Unset,
        Choice::Shrug,
        Outcome::Unset
    };
    int previous_go = -1;
    int flip()
    {
        return distribution(generator);
    }
    bool update_prediction(int player_choice)
    {
        bool guessing = false;
        Choice option = prediction_method(state_table.choices(state));
        switch (option)
        {
        case Choice::Shrug:
            prediction = flip();
            guessing = true;
            break;
        case Choice::Change:
            prediction = player_choice ^ 1;
            break;
        case Choice::Same:
            prediction = player_choice;
            break;
        }
        return guessing;
    }
    
public:
    MindReader(T gen, U dis) : generator(gen), distribution(dis)
    {
    }
    int get_prediction() const 
    {
        return prediction;
    }
    bool update(int player_choice)
    {
        const Choice turn_changed = player_choice == previous_go ? Choice::Same : Choice::Change;
        state_table.update(state, turn_changed);
        
        previous_go = player_choice;
        state = { std::get<2>(state), turn_changed, ( player_choice != prediction) ? Outcome::Win : Outcome::Lose };
        
        return update_prediction(player_choice);
    }
};