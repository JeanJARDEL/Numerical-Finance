#ifndef CONTINUOUS_GENERATOR_H
#define CONTINUOUS_GENERATOR_H

#include "random_generator.hpp"
#include "uniform_generator.hpp"
#include <vector>

using namespace std;

class ContinuousGenerator : public RandomGenerator {
    public:
        ContinuousGenerator(double target_mean, double target_variance);
        ContinuousGenerator();
        ~ContinuousGenerator();
};

class Exponential : public ContinuousGenerator {
    protected:
        double lambda;
        bool expo_algo = true;
        UniformGenerator* uniform = new EcuyerCombined();

    public:
        Exponential(double lambda);
        Exponential(double lambda, bool expo_algo);
        Exponential(double lambda, bool expo_algo, UniformGenerator* uniform1);
        Exponential();
        ~Exponential();

        virtual double generate();
};

class Normal : public ContinuousGenerator {
    protected:
        double mu = 0.;
        double sigma = 1.;
        int normal_algo = 1;
        UniformGenerator* uniform = new EcuyerCombined();

    public:
        Normal(double mu, double sigma);
        Normal(double mu, double sigma, int normal_algo);
        Normal(double mu, double sigma, int normal_algo, UniformGenerator* uniform);
        Normal();
        double get_mu();
        double get_sigma();
        ~Normal();

        virtual double generate();
};

#endif
