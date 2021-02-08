#include "discrete_generator.hpp"
#include <stdexcept>

DiscreteGenerator::DiscreteGenerator(double target_mean, double target_variance) : RandomGenerator(target_mean, target_variance) {};

DiscreteGenerator::DiscreteGenerator() {};

DiscreteGenerator::~DiscreteGenerator() {};

Bernoulli::Bernoulli(double p) : DiscreteGenerator(p, p * (1 - p)), p(p) {};

Bernoulli::Bernoulli(double p, UniformGenerator* uniform) : DiscreteGenerator(p, p * (1 - p)), p(p), uniform(uniform) {};

Bernoulli::Bernoulli() {};

Bernoulli::~Bernoulli() {};

double Bernoulli::generate() {
    double u = uniform->generate();
    if (u <= p)
        return 1.;
    return 0.;
};

HeadTail::HeadTail(UniformGenerator* uniform) : DiscreteGenerator(0.5, 0.25), uniform(uniform) {};

HeadTail::HeadTail() : DiscreteGenerator(0.5, 0.25) {};

HeadTail::~HeadTail() {};

double HeadTail::generate() {
    return bernoulli.generate();
};

Binomial::Binomial(myLong n, double p) : DiscreteGenerator(n * p, n * p * (1 - p)), n(n), p(p) {};

Binomial::Binomial(myLong n, double p, UniformGenerator* uniform) : DiscreteGenerator(n * p, n * p * (1 - p)), n(n), p(p), uniform(uniform) {};

Binomial::Binomial() {};

Binomial::~Binomial() {};

double Binomial::generate() {
    double sum = 0.;
    for (myLong i = 0; i < n; ++i) {
        sum += bernoulli.generate();
    }
    return sum;
};

bool check_probabilities(const vector<double>& probabilities) {
    double s = 0.;
    double pi;
    for (size_t i = 0; i < probabilities.size(); ++i) {
        pi = probabilities[i];
        if (pi < 0 || pi > 1) throw std::invalid_argument("a probability given is not between 0 and 1");
        s += pi;
    };
    if (s != 1.) throw std::invalid_argument("the sum of probabilities is not 1");
};

FiniteSet::FiniteSet(const vector<double>& input_probabilities) : probabilities(input_probabilities) {
    check_probabilities(probabilities);
};

FiniteSet::FiniteSet(const vector<double>& input_probabilities, UniformGenerator* uniform) : probabilities(input_probabilities), uniform(uniform) {
    check_probabilities(probabilities);
};

FiniteSet::FiniteSet() {};

FiniteSet::~FiniteSet() {};

double FiniteSet::generate() {
    double u = uniform->generate();
    double Pk = 0.;
    double Pk_1 = 0.;
    double k = 1.;
    for (myLong i = 0; i < probabilities.size(); ++i) {
        Pk += probabilities[i];
        if (Pk_1 <= u && u < Pk) {
            break;
        } else {
            Pk_1 = Pk;
        };
        k += 1.;
    };
    return k;
};

Poisson::Poisson(double lambda) : DiscreteGenerator(lambda, lambda), lambda(lambda) {};

Poisson::Poisson(double lambda, bool poisson_algo) : DiscreteGenerator(lambda, lambda), lambda(lambda), poisson_algo(poisson_algo) {};

Poisson::Poisson(double lambda, bool poisson_algo, UniformGenerator* uniform) : DiscreteGenerator(lambda, lambda), lambda(lambda), poisson_algo(poisson_algo), uniform(uniform) {};

Poisson::Poisson() {};

Poisson::~Poisson() {};

double Poisson::generate() {
    if (poisson_algo) {
        double u = uniform->generate();
        double Pk = exp(-lambda);
        double Pk_1 = 0.;
        double pk = Pk;
        double k = 0.;
        while (u > Pk and u != Pk_1) {
            Pk_1 = Pk;
            pk = (lambda / (k + 1)) * pk;
            Pk += pk;
            k += 1.;
        };
        return k;
    } else {
        double s = exponential.generate();
        double i = 0.;
        while (s < 1) {
            s += exponential.generate();
            i += 1.;
        };
        return i;
    };
};
