//  NE 500 - SNF Power Gen (Project).cpp : This file contains the 'main' function. Program execution begins and ends there.
//  Author: A. Wells
//  Date:   2024-04-13

//  Description:
//  Executes parametric studies using the header functions

#include <iostream>
#include <vector>

#include "fe_heat.h"
#include "td_cycles.h"

//	dh_profile and ans_inf/fin tests
vector <double> test_times = { 7, 200, 17000, 800000, 5000000, 65000000, 900000000};
dh_profile test_prof(test_times);
string test_out = "test-fe_heat.csv";

//	httr decay heat data generation
vector <double> httr_ans = { 86000, 172800, 259200, 345600, 432000, 518400, 604800, 691200, 777600, 864000, 950400, 1037000, 1123000, 1210000, 1296000, 1382000, 1469000, 1555000, 1642000, 1728000, 1814000, 1987000, 2074000, 2160000, 2246000, 2333000, 2419000, 2506000, 2592000, 5098000, 11500000, 15980000, 20820000, 26870000, 31710000, 38970000, 42600000, 47430000, 48610000, 51060000, 54690000, 57110000, 59530000, 63160000, 69210000, 72840000, 78888000, 82510000, 84930000, 88560000, 90980000, 94610000, 98240000, 101900000, 104300000, 106700000, 110300000, 114000000, 116400000, 120000000, 123600000, 126100000 };
double httr_to = 57000000;
double httr_q = 30000;
dh_profile httr_ans_prof(httr_ans, httr_to, httr_q);
string httr_out = "dh_httr_ans.csv";

//	pb-fhr discharge decay heat, 5-year residence
double fhr_cycle = 441806400;
double fhr_q_elem = 0.555;
double fhr_res = 1577880000;
double fhr_rate = 0.009624;
lot test_lot(fhr_cycle, fhr_q_elem, fhr_res, fhr_rate);

double test_eta;
double qi_test = 250000;
double m_doti_test = 0.114;
double p1i_test = 7750000;
double p2i_test = 345000;
double t4i_test = 311;

int main() 
{
//	httr_ans_prof.gen_corr();
//	httr_ans_prof.exp_prof(httr_out);
	test_lot.gen_corr();
	test_lot.tot_heat();
	test_eta = efficiency_r_water(qi_test, m_doti_test, p1i_test, p2i_test, t4i_test, 0.85, 0.85, 0.85, 0.85);
	std::cout << "test rankine efficiency: " << test_eta << std::endl;
}

