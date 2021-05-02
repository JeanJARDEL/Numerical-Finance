#include "black_scholes_nd.hpp"
#include <iostream>

BlackScholesND::BlackScholesND(Normal* gen, Matrix<double>* initial_spots, Matrix<double>* rates, Matrix<double>* vols,Matrix<double>* corrs) :
    RandomProcess(gen, initial_spots->get_num_rows()),
    m_dimension(initial_spots->get_num_rows()),
    m_initial_spots_matrix(initial_spots),
    m_rates_matrix(rates),
    m_vols_matrix(vols),
    m_corrs_matrix(corrs){

}

void BlackScholesND::simulate(double start_time, double end_time, size_t nb_steps) {
    for (int i = 0; i < m_dimension; i++)
        paths.push_back(new SinglePath(start_time, end_time, nb_steps));

    double dt = paths.back()->get_time_step();
    Matrix<double> cholesky = m_corrs_matrix->cholesky();
    Matrix<double> ones(m_dimension,1,new double[3]{1.,1.,1.});
    Matrix<double> random_law(dimension, nb_steps);
    for(int i = 0; i < dimension; i++)
        for(size_t j = 0; j < nb_steps; j++)
            random_law.set_elem_at(i, j, generator->generate());

    Matrix<double> current_spot = *m_initial_spots_matrix;

    for(size_t j = 0; j < nb_steps; j++) {
        for(int i = 0; i < m_dimension; i++)
           paths.at(i)->add_value(current_spot.elem_at(i,0));

        current_spot  = current_spot*(ones + (*m_rates_matrix)*dt + (*m_vols_matrix)*random_law.extract_column(j)*cholesky*std::sqrt(dt));
    }
}

BlackScholesND::~BlackScholesND(){}
