#include <cassert>
#include <random>
#include <memory>

#include "Race.hpp"

void check_properties()
{
    Race::StepperBlob blob;
    blob.step();
    assert(blob.total_steps() == 2);
    
    Race::RandomBlob random_blob([] () { return 0; }, [] (auto gen) { return gen(); });
    random_blob.step();
    assert(random_blob.total_steps() == 0);
}

std::vector<std::unique_ptr<Race::Blob>> create_blobs(int number)
{
    using namespace Race;
    std::vector<std::unique_ptr<Blob>> blobs;
    std::random_device rd;
    for (int i=0; i < number/2; ++i)
    {
        blobs.emplace_back(std::make_unique<StepperBlob>());
        blobs.emplace_back(std::make_unique<
            RandomBlob<std::default_random_engine, std::uniform_int_distribution<int>>
        >
        (
            std::default_random_engine{ rd() },
            std::uniform_int_distribution{ 0, 4 }
        )
        );
    }
    return blobs;
}


int main() 
{
    check_properties();
    // std::vector<Race::StepperBlob> blobs(4);
    // Race::race(blobs);
    auto blobs = create_blobs(8);
    Race::race(blobs);

    return 0;
}