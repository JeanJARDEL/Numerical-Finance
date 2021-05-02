#ifndef BLACKSCHOLESND_H
#define BLACKSCHOLESND_H

#include "random_process.hpp"
#include "../utils/matrix.hpp"

class BlackScholesND : public RandomProcess {
    protected:
        Matrix<double>* m_initial_spots_matrix;
        Matrix<double>* m_rates_matrix;
        Matrix<double>* m_vols_matrix;
        Matrix<double>* m_corrs_matrix;
        int m_dimension;

    public:
        BlackScholesND(Normal* gen, Matrix<double>* initial_spots, Matrix<double>* rates, Matrix<double>* vols,Matrix<double>* corrs);
        void simulate(double start_time, double end_time, size_t nb_steps);
        ~BlackScholesND();

};

#endif
