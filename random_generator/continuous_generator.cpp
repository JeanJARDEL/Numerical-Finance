#include "continuous_generator.hpp"
#include <math.h>
#include <stdexcept>

ContinuousGenerator::ContinuousGenerator(double target_mean, double target_variance) : RandomGenerator(target_mean, target_variance) {};

ContinuousGenerator::ContinuousGenerator() {};

ContinuousGenerator::~ContinuousGenerator() {};

Exponential::Exponential(double lambda) : ContinuousGenerator(1 / lambda, 1 / (lambda * lambda)), lambda(lambda) {};

Exponential::Exponential(double lambda, bool expo_algo) : ContinuousGenerator(1 / lambda, 1 / (lambda * lambda)), lambda(lambda), expo_algo(expo_algo) {};

Exponential::Exponential(double lambda, bool expo_algo, UniformGenerator* uniform1) : ContinuousGenerator(1 / lambda, 1 / (lambda * lambda)), lambda(lambda), expo_algo(expo_algo), uniform(uniform) {};

Exponential::Exponential() {};

Exponential::~Exponential() {};

double Exponential::generate() {
    if (expo_algo) {
        double u = uniform->generate();
        return -log(u) / lambda;
    } else {
        double u1 = uniform->generate();
        double u2 = uniform->generate();
        double x = u1;
        double fx = lambda * exp(lambda * x);
        double y = lambda * u2;
        myLong i = 0;
        myLong max_iter = 1000;
        while (y > fx && i < max_iter) {
            u1 = uniform->generate();
            u2 = uniform->generate();
            x = u1;
            fx = lambda * exp(lambda * x);
            y = lambda * u2;
            i += 1;
        };
        if (i == max_iter)
        {
            throw std::overflow_error("no y have been lower than the density function of x");
        };
        return x;
    };
};

Normal::Normal(double mu, double sigma) : ContinuousGenerator(mu, sigma), mu(mu), sigma(sigma) {};

Normal::Normal(double mu, double sigma, int normal_algo) : ContinuousGenerator(mu, sigma), mu(mu), sigma(sigma), normal_algo(normal_algo) {};

Normal::Normal(double mu, double sigma, int normal_algo, UniformGenerator* uniform) : ContinuousGenerator(mu, sigma), mu(mu), sigma(sigma), normal_algo(normal_algo), uniform(uniform) {};

Normal::Normal() {};

double Normal::get_mu() {
    return mu;
}

double Normal::get_sigma() {
    return sigma;
}

Normal::~Normal() {};

double Normal::generate() {
    if (normal_algo == 2) { // Central Limit Theorem
        double s = 0;
        for (int i = 0; i < 12; ++i) {
            s += uniform->generate();
        };
        return mu + sigma * (s - 6.);
    } else if (normal_algo == 3) { // Rejection sampling method
        double u1 = uniform->generate();
        double u2 = uniform->generate();
        double a = sqrt(2 * exp(1) / M_PI);
        double x = -log(2 * u1);
        double gx = 0.5 * exp(- abs(x));
        double fx = exp(-pow(x, 2)/2) / sqrt(2 * M_PI);
        double y = a * gx * u2;
        // We force a stop condition
        myLong i = 0;
        myLong max_iter = 1000;
        while (y > fx && i < max_iter) {
            u1 = uniform->generate();
            u2 = uniform->generate();
            x = -log(2 * u1);
            gx = 0.5 * exp(- abs(x));
            fx = exp(-pow(x, 2) / 2) / sqrt(2 * M_PI);
            y = a * gx * u2;
            i += 1;
        };
        if (i == max_iter) {
            throw std::overflow_error("no y have been lower than the density function of x");
        };
        return mu + sigma * x;
    } else { // If normal_algo is anything else, we use Box-Müller algorithm
        double u1 = uniform->generate();
        double u2 = uniform->generate();
        double r = sqrt(-2 * log(u1));
        double theta = 2 * M_PI * u2;
        return mu + sigma * r * cos(theta);
    };
};
