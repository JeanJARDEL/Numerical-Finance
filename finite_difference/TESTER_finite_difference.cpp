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

    // Main parameters
    Normal* normal = new Normal(0., 1.);

    // Price should be : 6.80495771
    double spot = 100.;
    double strike = 100.;
    double volatility = 0.1;
    double rate = 0.05;
    double maturity = 1.;

    double s_min = 0.;
    double s_max = 199.;

    // 1D Brownian motion
    /*
    Brownian1D* brownian1d = new Brownian1D(normal);
    brownian1d->simulate(0., 1., 100);
    SinglePath* path1 = brownian1d->get_path(0);
    display_values(path1, "Brownian 1D :", true);
    */

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
    /*
    BlackScholes1D* euler = new BSEuler1D(normal, spot, rate, volatility);
    euler->simulate(0., 1., 100);
    SinglePath* path2 = euler->get_path(0);
    display_values(path2, "Euler :", true);
    */

    // Milstein process
    /*
    BlackScholes1D* milstein = new BSMilstein1D(normal, spot, rate, volatility);
    milstein->simulate(0., 1., 300);
    SinglePath* path3 = milstein->get_path(0);
    display_values(path3, "Milstein :", true);
    */

    // Heston process
    /*
    Heston* heston = new Heston(normal, spot, 1., 0., 1., 0.9, volatility, 0.4);
    heston->simulate(0., 1., 300);
    SinglePath* path4 = heston->get_path(0);
    display_values(path4, "Heston :", true);
    */

    // PDE Solver (excplicit)
    R2R1Function* variance_function = new BSVariance(volatility);
    R2R1Function* trend_function = new BSTrend(rate);
    R2R1Function* actualization_function = new BSActualization(rate);
    R2R1Function* source_term_function = new NullFunction2D();

    R1R1Function* top_boundary_condition = new CallTopBoundary(s_max, strike);
    R1R1Function* bottom_boundary_condition = new CallBottomBoundary(s_min, strike);
    R1R1Function* right_boundary_condition = new CallTerminalCondition(strike);

    PDEGridExplicit black_scholes_grid(maturity, s_min, s_max, 20, 20,
                                       variance_function, trend_function,
                                       actualization_function, source_term_function,
                                       top_boundary_condition, bottom_boundary_condition,
                                       right_boundary_condition);

    black_scholes_grid.fill_nodes();
    black_scholes_grid.display_nodes();
    double price_at_zero = black_scholes_grid.get_time_zero_value(spot);
    double price_6_months = black_scholes_grid.get_value(spot, 0.5);

    printf("The computed price is %6.6f\n", price_at_zero);
    printf("The at-the-money price 6 months before maturity is %6.6f\n", price_6_months);
};
