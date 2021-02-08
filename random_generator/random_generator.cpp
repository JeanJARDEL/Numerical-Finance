#include "random_generator.hpp"
#include <iostream>
#include <vector>

using namespace std;

RandomGenerator::RandomGenerator(double target_mean, double target_variance) : target_mean(target_mean), target_variance(target_variance) {};

RandomGenerator::RandomGenerator() : target_mean(0.), target_variance(1.) {};

RandomGenerator::~RandomGenerator() {};

double RandomGenerator::mean(myLong nb_sim)
{
    double sum = 0.;
    for (myLong i = 0; i < nb_sim; ++i)
    {
        sum += generate();
    }
    return sum / nb_sim;
};

bool RandomGenerator::test_mean(myLong nb_sim, double tol)
{
    return (abs(mean(nb_sim) - target_mean) <= tol);
};

double RandomGenerator::variance(myLong nb_sim)
{
    double sum = 0.;
    double mean = 0.;
    double generated;
    vector<double> generated_numbers;
    for (myLong i = 0; i < nb_sim; ++i)
    {
        generated = generate();
        generated_numbers.push_back(generated);
        mean += generated;
    }
    mean = mean / nb_sim;
    for (myLong i = 0; i < nb_sim; ++i)
    {
        sum += pow(generated_numbers[i] - mean, 2);
    }
    return sum / nb_sim;
};

bool RandomGenerator::test_variance(myLong nb_sim, double tol)
{
    return (abs(variance(nb_sim) - target_variance) <= tol);
};
