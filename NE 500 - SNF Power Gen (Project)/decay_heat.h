//	deay_heat.h
//	Author:	A. Wells
//	Date:	2024-04-13

//	Description:
//	Implements one-group decay heat approximation for SNF presented in "Nucelar Systems Vol. 1" [Todreas and Kazimi], as well as applying piecewise correction factor

#ifndef _DECAY_HEAT_
#define _DECAY_HEAT_

//	--== utilities ==--
#include <iostream>
#include <cstring>
#include <cmath>

//	--== constants ==--
const double ans_coef[6][2] = { {-0.00614575,	0.060157	},
								{0.14058,		-0.286		},
								{0.8703,		-0.4255		},
								{12.842,		-0.6014		},
								{40683,			-1.0675		},
								{0.000039113,	-0.00000000073541} };

//const double httr_cf[3][4];

//	--== structs ==--

//	--== functions ==--

//	ans_inf:	computes decay heat fraction of full power after infinitely long operation at ts seconds after s/d
double ans_inf(double &ts) {
	double q_frac;
	if (1.5 <= ts && ts < 400) {							//decay curve between 1.5 and 4E+02 s
		q_frac = ans_coef[0][0] * log(ts) + ans_coef[0][1];
	} else if (400 <= ts && ts < 400000) {					//decay curve between 4E+02 and 4E+05 s
		q_frac = ans_coef[1][0] * pow(ts, ans_coef[1][1]);
	} else if (400000 <= ts && ts < 4000000) {				//decay curve between 4E+05 and 4E+06 s
		q_frac = ans_coef[2][0] * pow(ts, ans_coef[2][1]);
	} else if (4000000 <= ts && ts < 40000000) {			//decay curve between 4E+06 and 4E+07 s
		q_frac = ans_coef[3][0] * pow(ts, ans_coef[3][1]);
	} else if (40000000 <= ts && ts < 400000000) {			//decay curve between 4E+07 and 4E+08 s
		q_frac = ans_coef[4][0] * pow(ts, ans_coef[4][1]);
	} else if (400000000 <= ts && ts < 10000000000) {		//decay curve between 4E+08 and 1E+10 s
		q_frac = ans_coef[5][0] * exp(ts * ans_coef[5][1]);
	} else {												//catches out-of-bound time inputs and pulls q_frac to 0
		std::cout << "error decay_heat	:	decay heat time out-of-bounds, ts = " << ts << std::endl;
		q_frac = 0;
	}

	return q_frac;
}


//	ans_fin:	computes decay heat fraction of full power after finite operating period
double	ans_fin(double& ts, double& to) {
	double tse = ts + to;
	return ans_inf(ts) - ans_inf(tse);
}

//	corr_fin:	computes corrected decay heat fraction of full power after finite operation at ts seconds after s/d
double corr_fin(double& ts, double &to) {
	double q_frac;
	if (1.5 <= ts && ts < 10000000) {							//correction factor region I
		q_frac = ans_fin(ts, to) * 0.7724;
	} else if (10000000 <= ts && ts < 27000000) {				//correction factor region II
		q_frac = ans_fin(ts, to) * 0.9 * exp(-0.000000022 * (ts - 10000000));
	} else if (27000000 <= ts && ts < 125000000) {				//correction factor region III
		q_frac = ans_fin(ts, to) * (0.3 * log(((ts - 30000000) * 0.0000000415 + 1)) + 0.6202);
	} else {													//correction factor region III+
		q_frac = ans_fin(ts, to) * 1.05;
	}

	return q_frac;
}

#endif
