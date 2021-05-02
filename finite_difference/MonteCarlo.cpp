#include "MonteCarlo.hpp"

MonteCarlo::MonteCarlo(RNR1Function* payoff, BlackScholesND* target_process):
    m_payoff_function(payoff),
    m_target_process(target_process){

}

double MonteCarlo::compute_payoff_fixed_number(double start_time, double end_time, size_t nb_steps, int nb_simulation){
    vector<double> res;
    double mean=0.;
    for(int i=0;i<nb_simulation;i++){
        m_target_process->simulate(start_time,end_time,nb_steps);
        res.push_back((*m_payoff_function)(m_target_process->spot_at_maturity()));
        mean+=res.back();
    }
    mean /= nb_simulation;
    double var=0.;
    for(int i=0;i<nb_simulation;i++)
        var+=(res.at(i)-mean)*(res.at(i)-mean);

    var /= (nb_simulation-1);
    printf("Finished Monte Carlo with %i simulations: average=%4.2f variance=%4.2f\n", nb_simulation, mean, var);

    std::sort(res.begin(),res.end());
    Matrix<double> confidence_interval(1,2,new double[2]{res.at(std::lround(0.025*nb_simulation)),res.at(std::lround(0.975*nb_simulation))});
    printf("... 95%% confidence interval: %s\n", confidence_interval.to_string().c_str());
    return mean;
}

double MonteCarlo::inv_cdf(const double& quantile){
  //Beasley-Springer-Moro algorithm
  static double a[4] = {2.50662823884,-18.61500062529,41.39119773534,-25.44106049637};

  static double b[4] = {-8.47351093090,23.08336743743,-21.06224101826,3.13082909833};

  static double c[9] = {0.3374754822726147,0.9761690190917186,0.1607979714918209,0.0276438810333863,0.0038405729373609,
                        0.0003951896511919,0.0000321767881768,0.0000002888167364,0.0000003960315187};

  if (quantile >= 0.5 && quantile <= 0.92) {
    double num = 0.0;
    double denom = 1.0;

    for (int i=0; i<4; i++) {
      num += a[i] * std::pow((quantile - 0.5), 2*i + 1);
      denom += b[i] * std::pow((quantile - 0.5), 2*i);
    }
    return num/denom;

  } else if (quantile > 0.92 && quantile < 1) {
    double num = 0.0;

    for (int i=0; i<9; i++) {
      num += c[i] * std::pow((std::log(-std::log(1-quantile))), i);
    }
    return num;

  } else {
    return -1.0*inv_cdf(1-quantile);
  }
}

double MonteCarlo::compute_payoff_conf(double start_time, double end_time, size_t nb_steps, double eps, double conf){
    vector<double> res;
    double running_tot=0.;
    double running_mean=0.;
    double running_dist=0.;
    double running_var=0.;
    double normal_quantile = inv_cdf((1+conf)/2);
    double boundary = normal_quantile*normal_quantile/(eps*eps);
    int iteration=1;
    do{
        m_target_process->simulate(start_time,end_time,nb_steps);
        res.push_back((*m_payoff_function)(m_target_process->spot_at_maturity()));
        running_tot+=res.back();
        running_mean = running_tot/iteration;
        running_dist=0.;
        for(int i=0;i<res.size();i++)
            running_dist+=(res.at(i)-running_mean)*(res.at(i)-running_mean);
        running_var = running_dist/(iteration-1);
        if(iteration%1000==0)
            printf("Higher bound: %i\n",std::lround(boundary*running_var));
    }while((iteration<MIN_ITER || iteration<boundary*running_var) && iteration++<MAX_ITER);

    printf("Finished Monte Carlo with error=%4.2f confidence=%4.2f with %i simulations: average=%4.2f variance=%4.2f\n",eps,conf,iteration, running_mean, running_var);
    return running_mean;
}

MonteCarlo::~MonteCarlo(){
    //dtor
}
