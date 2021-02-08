#ifndef DISCRETE_GENERATOR_H
#define DISCRETE_GENERATOR_H

#include "random_generator.hpp"
#include "uniform_generator.hpp"
#include "continuous_generator.hpp"
#include <vector>

using namespace std;

class DiscreteGenerator : public RandomGenerator {
    public:
        DiscreteGenerator(double target_mean, double target_variance);
        DiscreteGenerator();
        ~DiscreteGenerator();
};

class Bernoulli : public DiscreteGenerator {
    private:
        double p;
        UniformGenerator* uniform = new EcuyerCombined();

    public:
        Bernoulli(double p);
        Bernoulli(double p, UniformGenerator* uniform);
        Bernoulli();
        ~Bernoulli();

        virtual double generate();
};

class HeadTail : public DiscreteGenerator {
    private:
        UniformGenerator* uniform = new EcuyerCombined();
        Bernoulli bernoulli = Bernoulli(0.5, uniform);

    public:
        HeadTail(UniformGenerator* uniform);
        HeadTail();
        ~HeadTail();

        virtual double generate();
};

class Binomial : public DiscreteGenerator {
    private:
        myLong n;
        double p;
        UniformGenerator* uniform = new EcuyerCombined();
        Bernoulli bernoulli = Bernoulli(p, uniform);

    public:
        Binomial(myLong n, double p);
        Binomial(myLong n, double p, UniformGenerator* uniform);
        Binomial();
        ~Binomial();

        virtual double generate();
};

class FiniteSet : public DiscreteGenerator {
    protected:
        vector<double> probabilities;
        UniformGenerator* uniform = new EcuyerCombined();

    public:
        FiniteSet(const vector<double>& probabilities);
        FiniteSet(const vector<double>& probabilities, UniformGenerator* uniform);
        FiniteSet();
        ~FiniteSet();

        virtual double generate();
};

class Poisson : public DiscreteGenerator {
    protected:
        double lambda;
        bool poisson_algo = true;
        UniformGenerator* uniform = new EcuyerCombined();
        Exponential exponential = Exponential(lambda, uniform);

    public:
        Poisson(double lambda);
        Poisson(double lambda, bool poisson_algo);
        Poisson(double lambda, bool poisson_algo, UniformGenerator* uniform);
        Poisson();
        ~Poisson();

        virtual double generate();
};

#endif
