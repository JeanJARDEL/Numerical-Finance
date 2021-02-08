#ifndef RANDOM_GENERATOR_H
#define RANDOM_GENERATOR_H

typedef unsigned long long myLong;

class RandomGenerator {
    protected:
        const double target_mean;
        const double target_variance;

    public:
        RandomGenerator(double target_mean, double target_variance);
        RandomGenerator();
        ~RandomGenerator();

        virtual double generate() = 0;

        double mean(myLong nb_sim);
        bool test_mean(myLong nb_sim, double tol);
        double variance(myLong nb_sim);
        bool test_variance(myLong nb_sim, double tol);
};

#endif
