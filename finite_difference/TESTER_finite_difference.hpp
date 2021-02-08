#ifndef TESTER_FINITE_DIFFERENCE_C
#define TESTER_FINITE_DIFFERENCE_C

#include "single_path.hpp"
#include "random_process.hpp"
#include "brownian_1d.hpp"
#include "brownian_nd.hpp"
#include "black_scholes_1d.hpp"
#include "black_scholes_2d.hpp"
#include "heston.hpp"
#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>

using namespace std;

void display_values(SinglePath* path, string name, bool five_first_five_last);

void test_finite_difference();

#endif
