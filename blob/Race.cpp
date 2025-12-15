#include <iostream>
#include <string>
#include <thread>

#include "Race.hpp"

void Race::draw_blobs(const std::vector<Race::StepperBlob>& blobs)
{
    const int bag_height = 3;
    const int race_height = 8;
    for (int  y=race_height; y>=0; --y)
    {
        std::string output = y >= bag_height ? "  " : "| ";
        for (const auto& blob : blobs)
        {
            if (blob.total_steps() >= y)
                output += "* ";
            else
                output += "  ";
        }
        output += y>= bag_height ? "  " : "| ";
        std::cout << output << '\n';
    }
    const int edges = 3;
    std::cout << std::string(blobs.size() * 2 + edges, '-') << '\n';
}

void Race::draw_blobs(const std::vector<std::unique_ptr<Race::Blob>>& blobs)
{
    const int bag_height = 3;
    const int race_height = 8;
    for (int  y=race_height; y>=0; --y)
    {
        std::string output = y >= bag_height ? "  " : "| ";
        for (const auto& blob : blobs)
        {
            if (blob->total_steps() >= y)
                output += "* ";
            else
                output += "  ";
        }
        output += y>= bag_height ? "  " : "| ";
        std::cout << output << '\n';
    }
    const int edges = 3;
    std::cout << std::string(blobs.size() * 2 + edges, '-') << '\n';
}

void Race::move_blobs(std::vector<Race::StepperBlob>& blobs)
{
    for (auto& blob : blobs)
    {
        blob.step();
    }
}

void Race::move_blobs(std::vector<std::unique_ptr<Race::Blob>>& blobs)
{
    for (auto& blob : blobs)
    {
        blob->step();
    }
}
void Race::race(std::vector<Race::StepperBlob>& blobs)
{
    using namespace std::chrono;
    const int max = 3;
    std::cout << "\x1B[2J\x1B[H";
    for (int i = 0; i < max; ++i)
    {
        draw_blobs(blobs);
        move_blobs(blobs);
        std::this_thread::sleep_for(1000ms);
        std::cout << "\x1B[2J\x1B[H";
    }
    draw_blobs(blobs);
};

void Race::race(std::vector<std::unique_ptr<Race::Blob>>& blobs)
{
    using namespace std::chrono;
    const int max = 3;
    std::cout << "\x1B[2J\x1B[H";
    for (int i=0; i<max; ++i)
    {
        draw_blobs(blobs);
        move_blobs(blobs);
        std::this_thread::sleep_for(1000ms);
        std::cout << "\x1B[2J\x1B[H";
    }
    draw_blobs(blobs);
}
