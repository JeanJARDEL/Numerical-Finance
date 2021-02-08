#ifndef RANDOM_PROCESS_H
#define RANDOM_PROCESS_H

#include "single_path.hpp"
#include "../random_generator/continuous_generator.hpp"

class RandomProcess {
    protected:
        RandomGenerator* generator;
        vector<SinglePath*> paths;
        int dimension;
    
    public:
        RandomProcess(RandomGenerator* gen, int dim);
        virtual void simulate(double start, double end, size_t nb_steps) = 0;
        SinglePath* get_path(size_t index);
        ~RandomProcess();
};

#endif
