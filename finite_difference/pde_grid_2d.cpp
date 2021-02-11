#include "pde_grid_2d.hpp"
#include <vector>
#include <stdio.h>

PDEGrid2D::PDEGrid2D(double maturity,
                     double minimum_underlying_value,
                     double maximum_underlying_value,
                     int underlying_steps,
                     int nbr_time_steps,
                     R2R1Function* variance_function,
                     R2R1Function* trend_function,
                     R2R1Function* actualization_function,
                     R2R1Function* source_term_function,
                     R1R1Function* top_boundary_function,
                     R1R1Function* bottom_boundary_function,
                     R1R1Function* right_boundary_function) :
                     T(maturity),
                     x_min(minimum_underlying_value),
                     x_max(maximum_underlying_value),
                     nodes_height(underlying_steps + 1),
                     nodes_width(nbr_time_steps + 1),
                     a(variance_function),
                     b(trend_function),
                     r(actualization_function),
                     f(source_term_function),
                     top_boundary_function(top_boundary_function),
                     bottom_boundary_function(bottom_boundary_function),
                     right_boundary_function(right_boundary_function) {
    h0 = maturity / (double) nodes_width;
    h1 = (maximum_underlying_value - minimum_underlying_value) / (double) nodes_height;
    nodes = vector< vector<double> > (nodes_height);
    for (size_t j = 0; j < nodes_height; ++j) {
        nodes[j] = vector<double> (nodes_width);
    }
};

void PDEGrid2D::fill_nodes() {
    fill_right_boundary();
    fill_top_and_bottom_boundaries();
};

double PDEGrid2D::get_time_zero_value(double spot) {
    return nodes[(int) (spot - x_min) / h1][0];
};

double PDEGrid2D::get_value(double spot, double time) {
    int spot_pos = (int) (spot - x_min) / h1;
    int time_pos = (int) ((double) time / h0);
    return nodes[spot_pos][time_pos];
};

void PDEGrid2D::fill_top_and_bottom_boundaries() {
    for (size_t i = 0; i < nodes_width; ++i) {
        nodes[0][i] = (*top_boundary_function)(i * h0);
        nodes[nodes_height - 1][i] = (*bottom_boundary_function)(i * h0);
    }
};

void PDEGrid2D::fill_right_boundary() {
    for (size_t j = 0; j < nodes_height; ++j) {
        nodes[nodes_height - j - 1][nodes_width - 1] = (*right_boundary_function)(x_min + j * h1);
    }
};

void PDEGrid2D::display_nodes() {
    printf("\n The nodes matrix is :\n");
    printf("[");
    for (size_t j = 0; j < nodes_height; ++j) {
        if (j == 0) {
            printf("[");
        } else {
            printf(" [");
        }
        for (size_t i = 0; i < nodes_width; ++i) {
            if (i == nodes_width - 1) {
                printf("% 07.3f", nodes[j][i]);
            } else {
                printf("% 07.3f, ", nodes[j][i]);
            }
        }
        if (j == nodes_height - 1) {
            printf("]");
        } else {
            printf("],\n");
        }
    }
    printf("]\n\n");
}

PDEGrid2D::~PDEGrid2D() {};

PDEGridExplicit::PDEGridExplicit(double maturity,
                                 double minimum_underlying_value,
                                 double maximum_underlying_value,
                                 int underlying_steps,
                                 int nbr_time_steps,
                                 R2R1Function* variance_function,
                                 R2R1Function* trend_function,
                                 R2R1Function* actualization_function,
                                 R2R1Function* source_term_function,
                                 R1R1Function* top_boundary_function,
                                 R1R1Function* bottom_boundary_function,
                                 R1R1Function* right_boundary_function) :
                                 PDEGrid2D(maturity,
                                           minimum_underlying_value,
                                           maximum_underlying_value,
                                           underlying_steps,
                                           nbr_time_steps,
                                           variance_function,
                                           trend_function,
                                           actualization_function,
                                           source_term_function,
                                           top_boundary_function,
                                           bottom_boundary_function,
                                           right_boundary_function) {};

void PDEGridExplicit::fill_nodes() {
    PDEGrid2D::fill_nodes();
    double x;
    double t;
    double ajk_h0_to_h12;
    double bjk_h0_to_h1;
    for (size_t k = nodes_width - 1; k > 0; --k) {
        for (size_t j = 1; j < nodes_height - 1; ++j) {
            x = x_min + j * h1;
            t = k * h0;
            ajk_h0_to_h12 = h0 * (*a)(x, t) / (h1 * h1);
            nodes[j][k - 1] = nodes[j][k] * (1 - ajk_h0_to_h12)
                            + nodes[j + 1][k] * 0.5 * ajk_h0_to_h12
                            + nodes[j - 1][k] * 0.5 * ajk_h0_to_h12
                            + h0 * (*f)(x, t);
        }
    }
};

PDEGridExplicit::~PDEGridExplicit() {};

PDEGridImplicit::PDEGridImplicit(double maturity,
                                 double minimum_underlying_value,
                                 double maximum_underlying_value,
                                 int underlying_steps,
                                 int nbr_time_steps,
                                 R2R1Function* variance_function,
                                 R2R1Function* trend_function,
                                 R2R1Function* actualization_function,
                                 R2R1Function* source_term_function,
                                 R1R1Function* top_boundary_function,
                                 R1R1Function* bottom_boundary_function,
                                 R1R1Function* right_boundary_function) :
                                 PDEGrid2D(maturity,
                                           minimum_underlying_value,
                                           maximum_underlying_value,
                                           underlying_steps,
                                           nbr_time_steps,
                                           variance_function,
                                           trend_function,
                                           actualization_function,
                                           source_term_function,
                                           top_boundary_function,
                                           bottom_boundary_function,
                                           right_boundary_function) {};

void PDEGridImplicit::fill_nodes() {
    PDEGrid2D::fill_nodes();
    // To implement
};

PDEGridImplicit::~PDEGridImplicit() {};

PDEGridTheta::PDEGridTheta(double maturity,
                           double minimum_underlying_value,
                           double maximum_underlying_value,
                           int underlying_steps,
                           int nbr_time_steps,
                           R2R1Function* variance_function,
                           R2R1Function* trend_function,
                           R2R1Function* actualization_function,
                           R2R1Function* source_term_function,
                           R1R1Function* top_boundary_function,
                           R1R1Function* bottom_boundary_function,
                           R1R1Function* right_boundary_function,
                           double theta) :
                           PDEGrid2D(maturity,
                                     minimum_underlying_value,
                                     maximum_underlying_value,
                                     underlying_steps,
                                     nbr_time_steps,
                                     variance_function,
                                     trend_function,
                                     actualization_function,
                                     source_term_function,
                                     top_boundary_function,
                                     bottom_boundary_function,
                                     right_boundary_function) {};

void PDEGridTheta::fill_nodes() {
    PDEGrid2D::fill_nodes();
    // To implement
};

PDEGridTheta::~PDEGridTheta() {};

