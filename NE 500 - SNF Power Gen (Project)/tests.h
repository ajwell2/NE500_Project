//	test.cpp
//	Author:	A. Wells
//	Date: 2024-04-13

//	Description:
//	Contains test cases for validating header file content

// #include "fe_heat.h"

//	--== test select ==--
bool test_ans_inf = true;
bool test_ans_fin = true;

//	--== decay_heat.h ==--

double ts_test0 = 1;
double ts_test1 = 7;
double ts_test2 = 200;
double ts_test3 = 17000;
double ts_test4 = 800000;
double ts_test5 = 5000000;
double ts_test6 = 65000000;
double ts_test7 = 900000000;
double ts_test8 = 9000000000;

//	--== fe_heat.h ==--

//	--== heat_source.h ==--

void test() {
	if (test_ans_inf) {
		//std::cout << "decay heat @ 1 s      = " << ans_inf(ts_test0) << std::endl;	//expected: error
		//std::cout << "decay heat @ 7 s      = " << ans_inf(ts_test1) << std::endl;	//expected: 4.820E-2
		//std::cout << "decay heat @ 2E2 s    = " << ans_inf(ts_test2) << std::endl;	//expected: 2.759E-2
		//std::cout << "decay heat @ 1.7E4 s  = " << ans_inf(ts_test3) << std::endl;	//expected: 8.676E-3
		//std::cout << "decay heat @ 8E5 s    = " << ans_inf(ts_test4) << std::endl;	//expected: 2.679E-3
		//std::cout << "decay heat @ 5E6 s    = " << ans_inf(ts_test5) << std::endl;	//expected: 1.202E-3
		//std::cout << "decay heat @ 6.5E7 s  = " << ans_inf(ts_test6) << std::endl;	//expected: 1.845E-4
		//std::cout << "decay heat @ 9E8 s    = " << ans_inf(ts_test7) << std::endl;	//expected: 2.018E-5
		//std::cout << "decay heat @ 9E9 s    = " << ans_inf(ts_test8) << std::endl;	//expected: 5.200E-8
	}
	if (test_ans_fin) {
		//std::cout << "decay heat @ ts = 1.7E4 s, to = 5E6	= " << ans_fin(ts_test3, ts_test5) << std::endl;	//expected: 7.474E-3
	}
}