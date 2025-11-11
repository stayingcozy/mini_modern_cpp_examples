#include <iostream>
#include <functional>

auto main() -> int { 
  std::cout << "Hello Again." << '\n';
  std::cout << std::plus<int>{}(1, 1.23) << '\n';
  std::cout << std::plus<>{}(1, 1.23) << '\n';
}

template<typename T, typename U>
auto simple_plus(T lhs, U rhs) -> decltype(lhs + rhs)
{
  return lhs + rhs;
}
