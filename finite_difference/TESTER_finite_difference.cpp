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
    double s_max = 200.;
     /*
    // 1D Brownian motion
    Brownian1D* brownian1d = new Brownian1D(normal);
    brownian1d->simulate(0., 1., 100);
    SinglePath* path1 = brownian1d->get_path(0);
    display_values(path1, "Brownian 1D :", true);

    // 3D Brownian motion
    Matrix<double>* cor_matrix = new Matrix<double>(3, 3);
    cor_matrix->set_elem_at(0, 0, 1.);
    cor_matrix->set_elem_at(1, 1, 1.);
    cor_matrix->set_elem_at(2, 2, 1.);
    cor_matrix->set_elem_at(0, 1, 0.8);
    cor_matrix->set_elem_at(0, 2, 0.8);
    cor_matrix->set_elem_at(1, 0, 0.8);
    cor_matrix->set_elem_at(1, 2, 0.8);
    cor_matrix->set_elem_at(2, 0, 0.8);
    cor_matrix->set_elem_at(2, 1, 0.8);

    BrownianND* browniannd = new BrownianND(normal, 3, cor_matrix);
    browniannd->simulate(0., 1., 100);
    SinglePath* path20 = browniannd->get_path(0);
    SinglePath* path21 = browniannd->get_path(1);
    SinglePath* path22 = browniannd->get_path(2);
    display_values(path20, "Brownian 3D, 1 :", true);
    display_values(path21, "Brownian 3D, 2 :", true);
    display_values(path22, "Brownian 3D, 3 :", true);
    */

    Matrix<double> initial_spots(3,1,new double[3]{100.,200.,142.});
    Matrix<double> rates(3,1,new double[3]{0.05,0.03,0.01});
    Matrix<double> vols(3,1,new double[3]{0.1,0.2,0.3});
    Matrix<double> corrs(3,3,new double[9]{1.,0.3,0.1,0.3,1.,0.8,0.1,0.8,1.});

    BlackScholesND BSND(normal,&initial_spots,&rates,&vols,&corrs);
    BSND.simulate(0., 1., 100);
    SinglePath* path30 = BSND.get_path(0);
    SinglePath* path31 = BSND.get_path(1);
    SinglePath* path32 = BSND.get_path(2);
    display_values(path30, "Black Scholes 3D, 1 :", true);
    display_values(path31, "Black Scholes 3D, 2 :", true);
    display_values(path32, "Black Scholes 3D, 3 :", true);

    Matrix<double> weights(3,1,new double[3]{0.2,0.5,0.3});

    StaticControlVariate SCV(normal, &initial_spots, &rates, &vols, &corrs, &weights);
    double js = SCV.joint_simulation(0., 1., 100, 150.);
    printf("Joint simulation result: %6.6f\n", js);

    /*
    // Euler process
    BlackScholes1D* euler = new BSEuler1D(new Normal(0., 1.), spot, rate, volatility);
    euler->simulate(0., 1., 300);
    SinglePath* path2 = euler->get_path(0);
    display_values(path2, "Euler :", true);

    // Milstein process
    BlackScholes1D* milstein = new BSMilstein1D(new Normal(0., 1.), spot, rate, volatility);
    milstein->simulate(0., 1., 300);
    SinglePath* path3 = milstein->get_path(0);
    display_values(path3, "Milstein :", true);

    // Heston process
    Heston* heston = new Heston(new Normal(0., 1.), spot, 1., 0., 1., 0.9, volatility, 0.4);
    heston->simulate(0., 1., 300);
    SinglePath* path4 = heston->get_path(0);
    display_values(path4, "Heston :", true);

    // PDE Solver (excplicit)
    R2R1Function* variance_function = new BSVariance(volatility);
    R2R1Function* trend_function = new BSTrend(rate);
    R2R1Function* actualization_function = new BSActualization(rate);
    R2R1Function* source_term_function = new NullFunction2D();

    R1R1Function* top_boundary_condition = new CallTopBoundary(s_max, strike);
    R1R1Function* bottom_boundary_condition = new CallBottomBoundary(s_min, strike);
    R1R1Function* right_boundary_condition = new CallTerminalCondition(strike);

    PDEGridExplicit black_scholes_grid(maturity, s_min, s_max, 20000, 0.2,
                                       variance_function, trend_function,
                                       actualization_function, source_term_function,
                                       top_boundary_condition, bottom_boundary_condition,
                                       right_boundary_condition);

    black_scholes_grid.fill_nodes();
    //black_scholes_grid.display_nodes();
    double price_at_zero = black_scholes_grid.get_time_zero_value(spot);
    double price_6_months = black_scholes_grid.get_value(spot, 0.5);

    printf("The computed price is %6.6f\n", price_at_zero);
    printf("The at-the-money price 6 months before maturity is %6.6f\n", price_6_months);
    */
};
