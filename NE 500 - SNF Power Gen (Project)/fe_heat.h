//	fe_source.h
//	Author:	A. Wells
//	Date:	2024-04-13

//	Description:
//	Contains functions utilizing decay_heat.h to predict decay heat for SNF elements based on power history. Also supports lumped heat for SNF lots

#ifndef _FE_HEAT_
#define _FE_HEAT_

#include <vector>

#include "decay_heat.h"
#include "csvwrite.h"

//	--== utilities ==--

//	--== structs ==--

//	dh_profile:	stores decay heat data computed at the inputed timesteps, with support for .csv export
struct dh_profile {
	vector <double> times;		//timestamps composing the profile (s)
	vector <double> powers;		//power or power fraction at corresponding timestamp
	double to;					//length of operation prior to s/d (s)
	double qo;					//operating power prior to s/d; default set to 1, computed power will be output as fraction of power

	dh_profile() = default;
	dh_profile(vector <double> spread) {
		times = spread;
		qo = 1;
	}
	dh_profile(vector <double> spread, double &t) {
		times = spread;
		to = t;
		qo = 1;
	}
	dh_profile(vector <double> spread, double& t, double &q) {
		times = spread;
		to = t;
		qo = q;
	}

	//	gen_ans:	generates <powers> at each timestamp using the uncorrected ans approximation from decay_heat.h
	void gen_ans() {
		if (to == 0) {									//checks is an operation duration was specified; if not, assumes infinite operation and uses ans_inf; if specfied, uses ans_fin
			for (int i = 0; i < times.size(); i++) {
				powers.push_back(ans_inf(times[i])*qo);
			};
		}
		else {
			for (int i = 0; i < times.size(); i++) {
				powers.push_back(ans_fin(times[i], to)*qo);
			};
		}
	};

	//	gen_corr:	generates <powers> at each timestamp using the corrected ans approximation from decay_heat.h
	void gen_corr() {
		if (to == 0) {									//checks is an operation duration was specified; if not, assumes infinite operation and uses ans_inf; if specfied, uses ans_fin
			for (int i = 0; i < times.size(); i++) {
				std::cout << "error fe_heat	:	gen_core argument invalid, to = 0" << std::endl;
			};
		}
		else {
			for (int i = 0; i < times.size(); i++) {
				powers.push_back(corr_fin(times[i], to) * qo);
			};
		}
	};

	//	exp_prof:		exports times and powers to a local .csv
	void exp_prof(string& filename) {
		vector <double> csv_output;
		for (int i = 0; i < times.size(); i++) {
			csv_output.push_back(times[i]);
			csv_output.push_back(powers[i]);
		};
		int csv_width = 2;
		int csv_length = int(times.size());
		write2csv(csv_output, filename, csv_width, csv_length);
	};

};

//	lot:	stores data for a regular series of spent fuel elements
struct lot {
	double	to;		//length of operation prior to discharge
	double	qo;		//avg element power prior to discharge
	double	tr;		//residence time, ie. maximum age of oldest lot member
	double	tro;	//residence time offset, ie. offset to apply to timestamps
	double	rate;	//rate at which new elements are added to lot, ie. inverse of timestep between elements
	int		size;	//alternative to rate, size of lot which is then used to calculate timestamps for lot members based on residence
	vector <double> powers;
	double	q_net;	//lumped decay heat generated by lot

	lot() = default;
	lot(double& toi, double& qoi, double& tri, double& tro, double& ri) {
		to = toi;
		qo = qoi;
		tr = tri;
		rate = ri;
		size = floor(tri * ri);
		q_net = 0;
	}
	lot(double& toi, double& qoi, double& tri, double& tro, int& si) {
		to = toi;
		qo = qoi;
		tr = tri;
		rate = si / tri;
		size = si;
		q_net = 0;
	}

	void gen_corr() {							//fills <powers> with the decay heat produced by each member of the lot; also tallies total heat generated by lot
		double ts = tro;							//initializes and/or resets ts
		q_net = 0;								//resets q_net to prevent accumulation if function is called multiple times
		powers.clear();							//resets powers to prevent appending duplicate data if the function is called twice
		for (int i = 0; i < size + 1; i++) {
			ts += (1 / rate);
			powers.push_back(qo * corr_fin(ts, to));
			q_net += (qo * corr_fin(ts, to));
		};
	}

	void tot_heat() {
		std::cout << "lumped heat generation:	" << q_net << " kW" << std::endl;
	}

};

//	--== functions ==--

//	res_study:	computes lumped heat generation rate for different residence times using a lot input and residence vector
vector <double> res_study(lot refLot, vector <double> &resVec) {
	vector <double> studyHeats;
	for (int i = 0; i < resVec.size(); i++) {
		refLot.tr = resVec[i];							//updates residence time of lot to resVec input value
		refLot.size = floor(refLot.tr * refLot.rate);	//updates lot size based on new residence time
		refLot.gen_corr();								//computes heat generated by the n-th column
		studyHeats.push_back(refLot.q_net);				//stores result
	};
	return studyHeats;
}

//	--== test cases ==--

#endif
