#include "TESTER_finite_difference.hpp"

void display_values(SinglePath* path, string name, bool five_first_five_last) {
    printf("\n%s\n", name.c_str());
    vector<double> values = path->get_values();
    vector<double> times = path->get_times();
    if (times.size() >= 10) {
        if (five_first_five_last) {
            for (size_t i = 0; i < 5; ++i) {
                printf("Time %4.2f : %4.2f\n", times[i], values[i]);
            }
            printf("...\n");
            for (size_t i = times.size() - 5; i < times.size(); ++i) {
                printf("Time %4.2f : %4.2f\n", times[i], values[i]);
            }
            printf("\n");
            return ;
        }
    }
    for (size_t i = 0; i < times.size(); ++i) {
        printf("Time %4.2f : %4.2f\n", times[i], values[i]);
    }
    printf("\n");
};

void test_finite_difference() {
    Normal* normal = new Normal(0., 1.);

    // 1D Brownian motion
    Brownian1D* brownian1d = new Brownian1D(normal);
    brownian1d->simulate(0., 1., 100);
    SinglePath* path1 = brownian1d->get_path(0);
    display_values(path1, "Brownian 1D :", true);

    // 3D Brownian motion
    /*
    vector< vector<double> >* correlation_matrix = {{1., 0.5, 0.2}, {0.5, 1., 0.9}, {0.2, 0.9, 1.}};
    Brownian1D* browniannd = new BrownianND(normal, correlation_matrix);
    brownian1d->simulate(0., 1., 100);
    SinglePath* path20 = browniannd->get_path(0);
    SinglePath* path21 = browniannd->get_path(1);
    SinglePath* path22 = browniannd->get_path(2);
    display_values(path20, "Brownian 3D, 1 :", true);
    display_values(path21, "Brownian 3D, 2 :", true);
    display_values(path22, "Brownian 3D, 3 :", true);
    */

    // Euler process
    BlackScholes1D* euler = new BSEuler1D(normal, 100., 0.01, 0.15);
    euler->simulate(0., 1., 100);
    SinglePath* path2 = euler->get_path(0);
    display_values(path2, "Euler :", true);

    // Milstein process
    BlackScholes1D* milstein = new BSMilstein1D(normal, 100., 0.01, 0.15);
    milstein->simulate(0., 1., 300);
    SinglePath* path3 = milstein->get_path(0);
    display_values(path3, "Milstein :", true);

    // Heston process
    Heston* heston = new Heston(normal, 100., 1., 0., 1., 0.9, 0.1, 0.4);
    heston->simulate(0., 1., 300);
    SinglePath* path4 = heston->get_path(0);
    display_values(path4, "Heston :", true);
};
