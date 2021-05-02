#ifndef QUASI_RANDOM_GENERATOR_H
#define QUASI_RANDOM_GENERATOR_H

#include "random_generator.hpp"

class QuasiRandomGenerator : public RandomGenerator {
    public:
        QuasiRandomGenerator(double target_mean, double target_variance);
        QuasiRandomGenerator();
        ~QuasiRandomGenerator();
};

class VDCHSequence : public QuasiRandomGenerator {
    protected:
        int p = 13;
        myLong n = 1313;

    public:
        VDCHSequence(int p, myLong n);
        VDCHSequence(int p);
        VDCHSequence();
        ~VDCHSequence();

        virtual double generate();
};

#endif
