#include <iostream>
#include <map>
#include <string>
#include <cassert>

#include "Smash.hpp"

void check_properties()
{
    auto select_first = [] (auto lb, auto ub, auto dest) {
        *dest = *lb;
    };
    auto [no_word, no_defintion, no_offset] = select_overlapping_word_from_dictionary("class", {}, select_first);
    
    assert(no_word == "");
    assert(no_offset == -1);
}

void warm_up()
{
    std::map<std::string, std::string> dictionary;
    dictionary["assume"] = "take for granted, take to be the case";
    std::string new_value = dictionary["fictional"];
    for (const auto& item : dictionary)
    {
        std::cout << item.first << " : " << item.second << '\n';
    }
}

void structured_bindings()
{
    std::map<std::string, std::string> dictionary; 
    dictionary["assume"] = "presume, take for granted";
    std:: string new_word = dictionary["fictional"];
    for (const auto& [key, value] : dictionary)
    {
        std::cout << key << " : " << value << '\n';
    }
}

int main() 
{
    // const std::map<std::string, std::string> dictionary {
    //     {"assume", "take for granted"},
    //     {"harsh", "coarse, large-grained or rough"},
    //     {"table", "piece of furniture"},
    //     {"tease", "mock, make fun of"},
    //     {"torch", "lit stick carried in one's hand"},
    // };
    
    // const std::map<std::string, std::string> keywords {
    //     {"char", "type for character representation which can be most efficiently processed on a target system"},
    //     {"class", "user defined type with private members by default"},
    //     {"struct", "user defined type with public members by default"},
    //     {"vector", "sequential container suppporting dynamic resizing"},
    //     {"template", "used for generic code"}
    // };
    
    const auto dictionary = load_dict(R"(dictionary.csv)");
    const auto keywords = load_dict(R"(keywords.csv)");
    
    // warm_up(); 
    // structured_bindings();
    // simple_answer_smash(keywords, dictionary);
    answer_smash(keywords, dictionary);
}
