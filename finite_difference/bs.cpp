#include "bs.hpp"

BSActualization::BSActualization(double rate) : rate(rate) {};

double BSActualization::operator()(double x, double t) {};

BSActualization::~BSActualization() {};

BSVariance::BSVariance(double sigma) : sigma(sigma) {};

double BSVariance::operator()(double x, double t) {};

BSVariance::~BSVariance() {};

BSTrend::BSTrend(double rate) : rate(rate) {};

double BSTrend::operator()(double x, double t) {};

BSTrend::~BSTrend() {};
