#include "brownian_nd.hpp"
#include "random_process.hpp"

BrownianND::BrownianND(Normal* gen, int dim, Matrix<double> cor) : RandomProcess(gen, dim), correlation_matrix(cor) {};

void BrownianND::simulate(double start_time, double end_time, size_t nb_steps) {
    int nb_time_steps = paths[0]->get_time_step();
    Matrix<double> cholesky = correlation_matrix.cholesky();
    printf("%s", cholesky.to_string().c_str());
    Matrix<double> draws(dimension, nb_steps);
    printf("%s", draws.to_string().c_str());
    for(int i = 0; i < dimension; i++)
        for(int j = 0; j < nb_steps; j++)
            draws.set_elem_at(i, j, generator->generate());
    printf("%s", draws.to_string().c_str());
    
    Matrix<double> prod(dimension, nb_steps);
    prod = cholesky.dot(draws);
    printf("%s", prod.to_string().c_str());
    prod = prod * sqrt(nb_time_steps);
    printf("%s", prod.to_string().c_str());

    for(int i = 0; i < dimension; i++)
        for(int j = 0; j < nb_steps; j++)
            paths[i]->add_value(prod.elem_at(i, j));
}

BrownianND::~BrownianND() {};
