#include <optional>
#include <thread>
#include <chrono>
#include <iostream>

// clang++ main.cpp -std=c++23 -o main.exe && main.exe

void duration_to_end_of_year()
{
    std::chrono::time_point now = std::chrono::system_clock::now();
    
    constexpr auto year = 2025;
    auto new_years_eve = std::chrono::year_month_day(
        std::chrono::year(year),
        std::chrono::month(12),
        std::chrono::day(31)
    );
    
    auto event = std::chrono::sys_days(new_years_eve);
    std::chrono::duration dur = event - now;
    std::cout << dur << " until event\n";
}

void durations()
{
    using namespace std::chrono;
    auto nearly_a_day = hours{ 23 }; // alt - 23h due to hours operator""h(long long val){return hours(_Val);}
    days a_day = duration_cast<days>(nearly_a_day);
    hours round_trip = a_day;
    std::cout << nearly_a_day << " cast to " << a_day << " and cast back to " << round_trip << '\n';
}

void defining_a_duration()
{
    using namespace std::chrono;
    using centuries = duration<long long,
        std::ratio_multiply<years::period, std::hecto>>;
    centuries two_hundred_years = centuries(2);
    seconds sec = two_hundred_years;
    hours hrs = two_hundred_years;
    days day_count = duration_cast<days>(two_hundred_years); // cast since days are decimal per year (days in year -> 365.2425) 
    // where seconds and hours are whole nums, integers
    std::cout << "Two centuries is approximately " << day_count << '\n';
}

void countdown()
{
    using namespace std::chrono;
    time_point now = system_clock::now();
    
    const auto ymd = year_month_day{
        floor<days>(now)
    };
    
    auto this_year = ymd.year();
    auto new_years_eve = this_year / December / last; // std::chrono::December, std::chrono::last
    // also do last day -> Friday[last], picks appropriate overload - no calc's
    // also Friday[1] first friday (it is indexed based)
    
    auto event = sys_days(new_years_eve);
    duration dur = event - now;
    std::cout << duration_cast<days>(dur) << " until event \n ";
}

void pay_day()
{
    using namespace std::chrono;
    
    time_point now = system_clock::now();
    const auto ymd = year_month_day {
        floor<days>(now)
    }; // current year month day
    
    auto pay_day = ymd.year() / ymd.month() / Friday[last];
    auto event = sys_days(pay_day);
    duration dur = event - now;
    
    std::cout << duration_cast<days>(dur) << " until pay day \n";
    
}

constexpr std::chrono::system_clock::duration countdown(std::chrono::system_clock::time_point start)
{
    using namespace std::chrono;
    
    auto days_only = floor<days>(start);
    
    const auto ymd = year_month_day{days_only};
    
    auto this_year = ymd.year();
    auto new_years_eve = this_year / December / last;
    
    auto event = sys_days(new_years_eve);
    return event - start;
}

std::optional<std::chrono::year_month_day> read_date(std::istream& in)
{
    using namespace std::string_literals;
    auto format_str = "%Y-%m-%d"s;
    std::chrono::year_month_day date;
    if (in >> std::chrono::parse(format_str, date))
    {
        return date;
    }
    in.clear();
    std::cout << "Invalid format. Expected " << format_str << '\n';
    return {};
}

constexpr std::chrono::system_clock::duration countdown_to(std::chrono::system_clock::time_point now, std::chrono::year_month_day date)
{
    using namespace std::chrono;
    auto event = sys_days(date);
    return event - now;
}

std::chrono::system_clock::duration countdown_in_local_time(std::chrono::system_clock::time_point now, std::chrono::year_month_day date)
{
    using namespace std::chrono;
    auto sys_event = zoned_time(current_zone(), local_days{ date }).get_sys_time();
    return sys_event - now;
}

void check_properties() 
{
    using namespace std::chrono;
    
    constexpr auto new_years_eve = 2022y / December / last;
    constexpr auto one_day_away = sys_days{ new_years_eve } - 24h;
    constexpr auto result = countdown(one_day_away);
    static_assert (duration_cast<days>(result) == days{ 1 });
}

int main()
{
    using namespace std::chrono;
    std::cout << "Enter a date\n";
    std::string str;
    std::cin >> str;
    std::istringstream in(str);
    std::optional<year_month_day> event_date = read_date(in);
    if (event_date)
    {
        auto dur = countdown_to(system_clock::now(), event_date.value());
        std::cout << duration_cast<days>(dur) << " until " << event_date.value();
    }
    
    // std::cout << countdown(std::chrono::system_clock::now()) << " until event \n";
    // countdown();
    // pay_day();
    // defining_a_duration();
    // durations();
    // duration_to_end_of_year();
    check_properties();
}
