#include "rnr1_function.hpp"
#include <iostream>

RNR1Function::RNR1Function() {}

RNR1Function::~RNR1Function() {}

BasketPayoff::BasketPayoff(Matrix<double> coeffs){
    m_coeffs = coeffs;
}

double BasketPayoff::operator()(Matrix<double> X){
    return (m_coeffs.dot(X)).elem_at(0,0);
}

BasketPayoff::~BasketPayoff() {}
