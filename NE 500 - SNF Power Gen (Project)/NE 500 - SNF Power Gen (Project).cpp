//  NE 500 - SNF Power Gen (Project).cpp : This file contains the 'main' function. Program execution begins and ends there.
//  Author: A. Wells
//  Date:   2024-04-13

//  Description:
//  Executes parametric studies using the header functions

#include <iostream>
#include <vector>

#include "fe_heat.h"
#include "td_cycles.h"
#include "heat_source.h"

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
double fhr_cycle = 44180640;
double fhr_q_elem = 0.555;
double fhr_res = 157788000;
double fhr_rate = 0.009624;
double fhr_tro = 0;
lot test_lot(fhr_cycle, fhr_q_elem, fhr_res, fhr_tro, fhr_rate);

//	lumped heat vs resicence study: 0.5 to 10 years
vector <double> lh_study_res = {15778800, 31557600, 47336400, 63115200, 78894000, 94672800, 110451600, 126230400, 142009200, 157788000, 189345600, 220903200, 252460800, 284018400, 315576000};
string lh_study_fileName = "study_lheat_vs_res.csv";
int lh_study_width = 1;
int lh_study_length = lh_study_res.size();

//	Specific Heat Values
double cp_flinak = 1512;	//FLiNaK
double cp_na = 1.374;		//Sodium
double cp_pb = 148.4;		//Lead
double cp_bi = 141.2;		//Bismuth
double cp_pbbi = 149.8;		//Lead-Bismuth Eutectic

//	Heat Sources and study inputs
lotArray n9216_array(9216, fhr_rate, fhr_res, fhr_cycle, fhr_q_elem);
lotArray n10000_array(10000, fhr_rate, fhr_res, fhr_cycle, fhr_q_elem);
lotArray n15000_array(15000, fhr_rate, fhr_res, fhr_cycle, fhr_q_elem);
lotArray n20000_array(20000, fhr_rate, fhr_res, fhr_cycle, fhr_q_elem);
lotArray n25000_array(25000, fhr_rate, fhr_res, fhr_cycle, fhr_q_elem);

string flowReq_vTemp_Name = "study_flowReq_vTemp.csv";
string flowReq_vNLot_name = "study_flowReq_vNLot";
vector <double> array_flowReq_in = {10, 20, 30, 40, 50};
vector <double> array_Cp_matl = { cp_flinak, cp_na, cp_pb, cp_bi, cp_pbbi };
vector <double> flowReq_vNLot;
int study_flowReq_width = array_Cp_matl.size();
int study_flowReq_length = array_flowReq_in.size();
int study_flowReq_height = 5;


//	efficiency_r_water test based on "Nuclear Systems vol. 1" ex) 6.6
double test_eta;
double qi_test = 250000;
double m_doti_test = 0.114;
double p1i_test = 7750000;
double p2i_test = 345000;
double t4i_test = 311;

//	study test case
string study_test_n = "study_test2.csv";
char study_type = 'w';
double et1_test = 1;
double et2_test = 1;
double ep1_test = 1;
double ep2_test = 1;
vector <double> mfr_test	= {0.06, 0.065, 0.07, 0.075, 0.08, 0.085, 0.09, 0.095, 0.10, 0.105, 0.110, 0.115, 0.120};
vector <double> mp_test		= {500000, 450000, 400000, 350000, 300000, 250000, 200000, 150000};
study_r study_test(study_type, qi_test, p1i_test, t4i_test, mfr_test, mp_test, et1_test, et2_test, ep1_test, ep2_test, study_test_n);

//	rankine water study
string study_s1_n = "study_r_w.csv";
char study_s1_type = 'w';
double et1_s1 = 1;
double et2_s1 = 1;
double ep1_s1 = 1;
double ep2_s1 = 1;
double qi_s1 = 180000;
vector <double> mfr_s1 = { 0.055, 0.060, 0.065, 0.070, 0.075, 0.080, 0.085 };
vector <double> mp_s1 = { 500000, 450000, 400000, 350000, 300000, 250000, 200000, 150000 };
study_r study_s1(study_s1_type, qi_s1, p1i_test, t4i_test, mfr_s1, mp_s1, et1_s1, et2_s1, ep1_s1, ep2_s1, study_s1_n);

int main() 
{
	httr_ans_prof.gen_corr();
	httr_ans_prof.exp_prof(httr_out);
	test_lot.gen_corr();
	test_lot.tot_heat();
	test_eta = efficiency_r_water(qi_test, m_doti_test, p1i_test, p2i_test, t4i_test, 0.85, 0.85, 0.85, 0.85);
	std::cout << "test rankine efficiency: " << test_eta << std::endl;
	study_s1.execute();
	study_s1.write();
	vector <double> lh_study_out = res_study(test_lot, lh_study_res);
	write2csv(lh_study_out, lh_study_fileName, lh_study_width, lh_study_length);
	vector <double> hs_study_temp;
}


