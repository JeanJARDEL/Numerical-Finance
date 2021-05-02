#include "quasi_random_generator.hpp"

QuasiRandomGenerator::QuasiRandomGenerator(double target_mean, double target_variance) : RandomGenerator(target_mean, target_variance) {};

QuasiRandomGenerator::QuasiRandomGenerator() {};

QuasiRandomGenerator::~QuasiRandomGenerator() {};

VDCHSequence::VDCHSequence(int p, myLong n) : QuasiRandomGenerator(0.5, 1 / 12.), p(p), n(n) {};

VDCHSequence::VDCHSequence(int p) : QuasiRandomGenerator(0.5, 1 / 12.), p(p) {};

VDCHSequence::VDCHSequence() : QuasiRandomGenerator(0.5, 1 / 12.) {};

double VDCHSequence::generate() {
    double q = 0.;
    double pk_1 = (double) 1 / p;
    myLong n_gen = n;

    while (n_gen > 0) {
      q += (n_gen % p) * pk_1;
      n_gen /= p;
      pk_1 /= p;
    }
    n += 1;
    return q;
};

VDCHSequence::~VDCHSequence() {};
