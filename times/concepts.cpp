// Script to show writing concepts

// write the concept
template<typename T>
concept Quacks = requires (T t)
{
    t.Quack();
};

// example of use
template<typename T>
requires Quacks<T>
void must_be_a_duck(T x)
{
    x.Quack();
}

// 2nd use (preferred)
void also_must_be_a_duck(Quacks auto x)
{
    x.Quack();
}
// concepts are not themselves nouns but adjectives (for now) so must use auto with it

int main()
{
    return 0; // compile check 
}