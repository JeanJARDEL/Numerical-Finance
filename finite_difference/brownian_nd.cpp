#include "brownian_nd.hpp"
#include "random_process.hpp"

BrownianND::BrownianND(Normal* gen, int dim, vector<vector<double> >* cor) : RandomProcess(gen, dim), correlation_matrix(cor) {};

void BrownianND::simulate(double start_time, double end_time, size_t nb_steps) {
    // To be implemented
}

BrownianND::~BrownianND() {};
