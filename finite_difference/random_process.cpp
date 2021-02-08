#include "random_process.hpp"

RandomProcess::RandomProcess(RandomGenerator* gen, int dim) : generator(gen), dimension(dim) {};

SinglePath* RandomProcess::get_path(size_t index) {
    return paths[index];
};

RandomProcess::~RandomProcess() {};
