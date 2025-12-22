#include <numeric>
#include <vector>
#include <cassert>
#include <algorithm>
#include <iostream>
#include <iterator>

constexpr std::vector<int> make_triangle_numbers(int count)
{
    std::vector<int> numbers(count);
    std::iota(numbers.begin(), numbers.end(), 1);
    std::partial_sum(numbers.begin(), numbers.end(), numbers.begin());
    return numbers;
}

void demo_further_properties()
{
    const int count = 20;
    const auto triangle_numbers = make_triangle_numbers(count);
    std::vector<char> odd_or_even;
    std::ranges::transform(triangle_numbers, std::back_inserter(odd_or_even),
        [](int i){ return i % 2 ? '.' : '*'; });
    std::ranges::copy(odd_or_even, std::ostream_iterator<char>(std::cout, " "));
    std::cout << '\n';
}

void check_properties()
{
    const int count = 20;
    const auto triangle_numbers = make_triangle_numbers(count);
    std::vector<int> diffs(count);
    std::adjacent_difference(triangle_numbers.begin(), triangle_numbers.end(), diffs.begin());
    std::vector<int> numbers(count);
    std::iota(numbers.begin(), numbers.end(), 1);
    assert(numbers == diffs);
    
    std::adjacent_difference(diffs.begin(), diffs.end(), diffs.begin());
    assert(std::all_of(diffs.begin(), diffs.end(), [](int x){ return x == 1; }));
    
    assert(std::count(diffs.begin(), diffs.end(), 1) == count);
    
    assert(std::all_of(triangle_numbers.begin(), triangle_numbers.end(), 
        [n = 0](int x) mutable
        {
            ++n;
            return x == n * (n+1) / 2;
        }
    ));
}

int main()
{
    check_properties();
    demo_further_properties();
    return 0;
}