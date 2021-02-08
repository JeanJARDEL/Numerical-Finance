#include "pde_grid_2d.hpp"
#include <vector>

PDEGrid2D::PDEGrid2D(double T, double t_min, double t_max, double h0, double h1,
                  R2R1Function* a, R2R1Function* b, R2R1Function* r, R2R1Function* f,
                  R1R1Function* top_boundary_function, R1R1Function* bottom_boundary_function,
                  R1R1Function* right_boundary_function, vector< vector<double> > nodes,
                  size_t nodes_height, size_t nodes_width) :
                  T(T), t_min(t_min), t_max(t_max), h0(h0), h1(h1),
                  a(a), b(b), r(r), f(f),
                  top_boundary_function(top_boundary_function), bottom_boundary_function(bottom_boundary_function),
                  right_boundary_function(right_boundary_function), nodes(nodes),
                  nodes_height(nodes_height), nodes_width(nodes_width) {};

double PDEGrid2D::get_value(double spot, double time) {};

PDEGrid2D::~PDEGrid2D() {};

PDEGridExplicit::PDEGridExplicit(double T, double t_min, double t_max, double h0, double h1,
                                 R2R1Function* a, R2R1Function* b, R2R1Function* r, R2R1Function* f,
                                 R1R1Function* top_boundary_function, R1R1Function* bottom_boundary_function,
                                 R1R1Function* right_boundary_function, vector< vector<double> > nodes,
                                 size_t nodes_height, size_t nodes_width) :
                                 PDEGrid2D(T, t_min, t_max, h0, h1, a, b, r, f,
                                 top_boundary_function, bottom_boundary_function,
                                 right_boundary_function, nodes,
                                 nodes_height, nodes_width) {};

void PDEGridExplicit::fill_nodes() {};

PDEGridExplicit::~PDEGridExplicit() {};

PDEGridImplicit::PDEGridImplicit(double T, double t_min, double t_max, double h0, double h1,
                                 R2R1Function* a, R2R1Function* b, R2R1Function* r, R2R1Function* f,
                                 R1R1Function* top_boundary_function, R1R1Function* bottom_boundary_function,
                                 R1R1Function* right_boundary_function, vector< vector<double> > nodes,
                                 size_t nodes_height, size_t nodes_width) :
                                 PDEGrid2D(T, t_min, t_max, h0, h1, a, b, r, f,
                                 top_boundary_function, bottom_boundary_function,
                                 right_boundary_function, nodes,
                                 nodes_height, nodes_width) {};

void PDEGridImplicit::fill_nodes() {};

PDEGridImplicit::~PDEGridImplicit() {};

PDEGridTheta::PDEGridTheta(double T, double t_min, double t_max, double h0, double h1,
                           R2R1Function* a, R2R1Function* b, R2R1Function* r, R2R1Function* f,
                           R1R1Function* top_boundary_function, R1R1Function* bottom_boundary_function,
                           R1R1Function* right_boundary_function, vector< vector<double> > nodes,
                           size_t nodes_height, size_t nodes_width) :
                           PDEGrid2D(T, t_min, t_max, h0, h1, a, b, r, f,
                           top_boundary_function, bottom_boundary_function,
                           right_boundary_function, nodes,
                           nodes_height, nodes_width) {};

void PDEGridTheta::fill_nodes() {};

PDEGridTheta::~PDEGridTheta() {};

