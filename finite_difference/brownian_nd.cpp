#include "brownian_nd.hpp"
#include "random_process.hpp"

BrownianND::BrownianND(Normal* gen, int dim, Matrix<double>* cor) : RandomProcess(gen, dim), correlation_matrix(cor) {};

void BrownianND::simulate(double start_time, double end_time, size_t nb_steps) {
    for (int i = 0; i < dimension; i++) {
        SinglePath* path = new SinglePath(start_time, end_time, nb_steps);
        paths.push_back(path);
    }
    Matrix<double> cholesky = correlation_matrix->cholesky();
    Matrix<double> draws(dimension, nb_steps);
    for(int i = 0; i < dimension; i++)
        for(int j = 0; j < nb_steps; j++)
            draws.set_elem_at(i, j, generator->generate());
    Matrix<double> prod(dimension, nb_steps);
    prod = cholesky.dot(draws);
    prod = prod * sqrt(end_time);
    for(int i = 0; i < dimension; i++) {
        for(int j = 0; j < nb_steps; j++) {
            paths[i]->add_value(prod.elem_at(i, j));
        }
    }
}

BrownianND::~BrownianND() {};
