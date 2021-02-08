#ifndef PDE_GRID_2D_H
#define PDE_GRID_2D_H

#include "r2r1_function.hpp"
#include "r1r1_function.hpp"
#include <vector>

class PDEGrid2D {
    protected:
        double T;
        double t_min;
        double t_max;
        double h0;
        double h1;
        R2R1Function* a;
        R2R1Function* b;
        R2R1Function* r;
        R2R1Function* f;
        R1R1Function* top_boundary_function;
        R1R1Function* bottom_boundary_function;
        R1R1Function* right_boundary_function;
        vector< vector<double> > nodes;
        size_t nodes_height;
        size_t nodes_width;
    
    public:
        PDEGrid2D(double T, double t_min, double t_max, double h0, double h1,
                  R2R1Function* a, R2R1Function* b, R2R1Function* r, R2R1Function* f,
                  R1R1Function* top_boundary_function, R1R1Function* bottom_boundary_function,
                  R1R1Function* right_boundary_function, vector< vector<double> > nodes,
                  size_t nodes_height, size_t nodes_width);
        virtual void fill_nodes() = 0;
        double get_value(double spot, double time);
        ~PDEGrid2D();

    private:
        void FillTopAndBottomBoundary();
        void FillRightBoundary();
};

class PDEGridExplicit : public PDEGrid2D {
    public:
        PDEGridExplicit(double T, double t_min, double t_max, double h0, double h1,
                        R2R1Function* a, R2R1Function* b, R2R1Function* r, R2R1Function* f,
                        R1R1Function* top_boundary_function, R1R1Function* bottom_boundary_function,
                        R1R1Function* right_boundary_function, vector< vector<double> > nodes,
                        size_t nodes_height, size_t nodes_width);
        void fill_nodes();
        ~PDEGridExplicit();
};

class PDEGridImplicit : public PDEGrid2D {
    public:
        PDEGridImplicit(double T, double t_min, double t_max, double h0, double h1,
                        R2R1Function* a, R2R1Function* b, R2R1Function* r, R2R1Function* f,
                        R1R1Function* top_boundary_function, R1R1Function* bottom_boundary_function,
                        R1R1Function* right_boundary_function, vector< vector<double> > nodes,
                        size_t nodes_height, size_t nodes_width);
        void fill_nodes();
        ~PDEGridImplicit();
};

class PDEGridTheta : public PDEGrid2D {
    public:
        PDEGridTheta(double T, double t_min, double t_max, double h0, double h1,
                        R2R1Function* a, R2R1Function* b, R2R1Function* r, R2R1Function* f,
                        R1R1Function* top_boundary_function, R1R1Function* bottom_boundary_function,
                        R1R1Function* right_boundary_function, vector< vector<double> > nodes,
                        size_t nodes_height, size_t nodes_width);
        void fill_nodes();
        ~PDEGridTheta();
};

#endif
