#ifndef MONTECARLO_H
#define MONTECARLO_H
#include <stdio.h>
#include <vector>
#include <algorithm>
#include "rnr1_function.h"
#include "BlackScholesND.h"

class MonteCarlo{
    public:
        MonteCarlo(RNR1Function* payoff, BlackScholesND* target_process);
        double compute_payoff_fixed_number(double start_time, double end_time, size_t nb_steps, int nb_simulation);
        double compute_payoff_conf(double start_time, double end_time, size_t nb_steps, double eps, double conf);
        double static inv_cdf(const double& quantile);
        virtual ~MonteCarlo();

    protected:
        RNR1Function* m_payoff_function;
        BlackScholesND* m_target_process;
        const int MAX_ITER = 50000;
        const int MIN_ITER = 100;
    private:
};

#endif // MONTECARLO_H
