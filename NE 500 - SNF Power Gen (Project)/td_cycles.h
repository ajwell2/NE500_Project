//	td_cycles.h
//	Author:	A. Wells
//	Date:	2024-04-14

//	Description:
//	Evaluates thermodynamic cycle efficiency for various cycle configurations

//	Note:
//	All input arguments should be provided in absolute base SI units (ie. K, J, Pa, s, kg)

#include <cmath>
#include <vector>

#include "IF97.h"

//	--== utilities ==--

//	--== structs ==--

//	--== functions ==--

//	efficiency_r_water:		computes efficiency of model rankine cycle with water working fluid, inputs arguments are as follows:
// 
//							qi:		heat rate in				W
//							m_doti:	mass flow rate through SG	kg/s
//							p1i:	SG exit pressure			Pa
//							p2i:	HP turbine exit pressure	Pa
//							t1i:	SG exit temperature			K
//							t4i:	condenser temperature		K
//							et1:	HP turbine efficiency		(ul)
//							et2:	LP turbine efficiency		(ul)
//							ep1:	condensate pump efficiency	(ul)
//							ep2:	feedwater pump efficiency	(ul)
//
double efficiency_r_water(double qi, double& m_doti, double &p1i, double &p2i, double &t4i, double et1, double et2, double ep1, double ep2) {
	double eta = 0;

	double t1 = IF97::Tsat97(p1i);
	double p1 = p1i;
	double t2 = IF97::Tsat97(p2i);
	double p2 = p2i;
	double t3 = t2;
	double p3 = p2i;
	double t4 = t4i;
	double p4 = IF97::psat97(t4i);
	double t5 = t4i;
	double p5 = p4;
	double p6 = p2i;
	double t7 = 0;
	double p7 = p2i;
	double p8 = p1i;
	double t9 = t2;
	double p9 = p2i;
	//std::cout << "temps & pressures initialized" << std::endl;

	double h1 = IF97::hvap_p(p1);
	double h2s = 1;
	double h2a = 1;
	double h3 = IF97::hvap_p(p3);
	double h4a = 1;
	double h4s = 1;
	double h5 = IF97::hliq_p(p5);
	double h6s = h5 + ((p6 - p5) / IF97::rholiq_p(p5));
	double h6a = h5 + ((h6s - h5) / ep1);
	double h7 = 1;
	double h8s = 1;
	double h8a = IF97::hliq_p(p7);
	double h9 = IF97::hliq_p(p9);
	//std::cout << "enthalpy initialized" << std::endl;

	double s1 = 0;
	double s3 = IF97::svap_p(p3);
	//std::cout << "entropy initialized" << std::endl;

	double x2s = 0;
	double x2a = 0;
	double x4s = 0;
	double x4a = 0;
	//std::cout << "quality initialized" << std::endl;

	while (eta == 0) {
		if (h1 < ((qi / m_doti) + h8a)) {	//checks if heat rise across the SG is currently less that the heat input; increments t1 and recomputes until SG heat rise matches heat input
			std::cout << "t1 = " << t1 << " K, incrementing..." << std::endl;
			t1++;
			h1 = IF97::hmass_Tp(t1, p1);
			s1 = IF97::smass_Tp(t1, p1);
			//std::cout << "point 1 complete" << std::endl;
			std::cout << "h1 = " << h1 << std::endl;
			x2s = (s1 - IF97::sliq_p(p2)) / (IF97::svap_p(p2) - IF97::sliq_p(p2));
			h2s = IF97::hliq_p(p2) + (x2s * (IF97::hvap_p(p2) - IF97::hliq_p(p2)));
			h2a = h1 - (et1 * (h1 - h2s));
			x2a = (h2s - IF97::hliq_p(p2)) / (IF97::hvap_p(p2) - IF97::hliq_p(p2));
			std::cout << "h2a = " << h2a << std::endl;
			//std::cout << "point 2 complete" << std::endl;
			x4s = (s3 - IF97::sliq_p(p4)) / (IF97::svap_p(p4) - IF97::sliq_p(p4));
			h4s = IF97::hliq_p(p4) + (x4s * (IF97::hvap_p(p4) - IF97::hliq_p(p4)));
			h4a = h3 - (et2 * (h3 - h4s));
			x4a = (h4a - IF97::hliq_p(p4)) / (IF97::hvap_p(p4) - IF97::hliq_p(p4));
			std::cout << "h4a = " << h4a << std::endl;
			//std::cout << "point 4 complete" << std::endl;
			h7 = (x2a * h6a) + ((1 - x2a) * h9);
			//std::cout << "x2a = " << x2a << std::endl;
			//std::cout << "h7 = " << h7 << std::endl;
			t7 = IF97::T_phmass(p7, h7);
			//std::cout << "point 7 complete" << std::endl;
			h8s = h7 + ((p8 - p7) / IF97::rhomass_Tp(t7, p7));
			h8a = h7 + ((h8s - h7) / ep2);
			std::cout << "h8a = " << h8a << std::endl;
			//std::cout << "point 8 complete" << std::endl;
			//std::cout << "heat rise: " << m_doti * (h1 - h8a) << " out of " << qi << std::endl;
		} else if(h1 < h8a){
			eta = -1;
		} else {						//if SG heat rise is greater than heat input, compute efficiency
			//std::cout << "h1 = " << h1 << std::endl;
			//std::cout << "h2a = " << h2a << std::endl;
			//std::cout << "h3 = " << h3 << std::endl;
			//std::cout << "h4a = " << h4a << std::endl;
			//std::cout << "h5 = " << h5 << std::endl;
			//std::cout << "h6a = " << h6a << std::endl;
			//std::cout << "h7 = " << h7 << std::endl;
			//std::cout << "h8a = " << h8a << std::endl;
			//std::cout << "h9 = " << h9 << std::endl;

			//std::cout << "p5 = " << p5 << std::endl;

			std::cout << "x2a = " << x2a << std::endl;
			//std::cout << "x4a = " << x4a << std::endl;

			std::cout << "t1 final = " << t1 - 273 << " C" << std::endl;

			//std::cout << "w_hp = " << h1 - h2a << std::endl;
			//std::cout << "w_lp = " << x2a * (h3 - h4a) << std::endl;
			//std::cout << "w_cp = " << x2a * (h6a - h5) << std::endl;
			//std::cout << "w_fp = " << h8a - h7 << std::endl;

			eta = ((h1 - h2a) + (x2a * ((h3 - h4a) - (h6a - h5))) - (h8a - h7)) / (h1 - h8a);
		}
	}

	if (eta < 0) {
		std::cout << "error td_cycles.h	:	cycle has negative efficiency" << std::endl;
	}

	if (x2a > 1 || x4a > 1) {					//flag any results which rely on impossibly high steam quality
		std::cout << "error td_cycles.h	:	x2a or x4a greater than 1.00" << std::endl;
		eta = -1;
	}

	return eta;
}

//	efficiency_r_[organic]:	computes efficiency of model rankine cycle with [organic] working fluid

//	efficiency_b_co2:		computes efficiency of model brayton cycle with carbon dioxide working fluid

//	efficiency_b_he:		computes efficiency of model brayton cycle with helium working fluid

//	efficiency_s_n:			computes efficiency of model stirling cycle with nitrogen working fluid

//	efficiency_s_he:		computes efficiency of model stirling cycle with helium working fluid
