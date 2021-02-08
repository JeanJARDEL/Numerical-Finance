#ifndef BROWNIAN_ND_H
#define BROWNIAN_ND_H

#include "random_process.hpp"
#include <vector>

class BrownianND : public RandomProcess {
    protected:
        vector< vector<double> >* correlation_matrix;
        int dimension;

    public:
        BrownianND(Normal* gen, int dim, vector< vector<double> >* cor);
        void simulate(double start_time, double end_time, size_t nb_steps);
        ~BrownianND();
};

#endif
