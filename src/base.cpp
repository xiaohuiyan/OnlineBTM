#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cassert>

#include "sampler.h"
#include "str_util.h"

#include "base.h"
#include "debug.h"

Base::Base(int K, int W, double a, double b) :
  K(K), W(W), alpha(a), beta(b) {
    srand(time(NULL));
	
	nwz.resize(W, K);
	nb_z.resize(K);
}

// using batch results to initialize nb_z and nwz
void Base::load_init(string pt) {
  cout << "load bz: " << pt << endl;

  ifstream rf(pt.c_str());
  if (!rf) {
	cout << "[Error] file not find： " << pt << endl;
	exit(1);
  }
  
  string line;
  while (getline(rf, line)) {
	istringstream iss(line);
	
	Biterm bi(line);
	bs.push_back(bi);
	// update recorders
	int k = bi.get_z();
	++nwz[bi.get_wi()][k];
	++nwz[bi.get_wj()][k];
	++nb_z[k];
  }
  cout << "init n(b):" << bs.size() << endl;
}

// sample procedure for ith biterm 
void Base::update_biterm(Biterm& bi) {
  if (bi.get_z() != -1) 
	reset_biterm_topic(bi);
  
  // compute p(z|b)
  Pvec<double> pz;
  compute_pz_b(bi, pz);

  // sample topic for biterm b
  int k = Sampler::mult_sample(pz.to_vector());
  assign_biterm_topic(bi, k);
}

// reset topic assignment of biterm i
void Base::reset_biterm_topic(Biterm& bi) {
  int w1 = bi.get_wi();
  int w2 = bi.get_wj();
  int k = bi.get_z();
  
  if (k < 0) return;
  
  --nb_z[k];				// update proportion of biterms in topic K
  --nwz[w1][k];			// update proportion w1's occurrence times in topic K
  --nwz[w2][k];
  assert(nb_z[k]>=0 && nwz[w1][k]>=0 && nwz[w2][k]>=0);
  
  bi.reset_z();
}

// compute p(z|w_i, w_j)
void Base::compute_pz_b(Biterm& bi, Pvec<double>& pz) {
  pz.resize(K);
  
  int w1 = bi.get_wi();
  int w2 = bi.get_wj();
  
  double pw1k, pw2k;
  for (int k = 0; k < K; ++k) {
	double deno = 2 * nb_z[k] + W * beta;
	
	pw1k = (nwz[w1][k] + beta) / deno;
	pw2k = (nwz[w2][k] + beta) / deno;
	pz[k] = (nb_z[k] + alpha) * pw1k * pw2k;
  }
  pz.normalize();
}

// assign topic k to biterm i
void Base::assign_biterm_topic(Biterm& bi, int k) {
  int w1 = bi.get_wi();
  int w2 = bi.get_wj();
  bi.set_z(k);
	
  ++nb_z[k];
  ++nwz[w1][k];
  ++nwz[w2][k];
}

void Base::save_res(string dir) {
  string ks = str_util::itos(K);
  string pt = dir + "pz.k" + ks;
  cout << "write p(z): " << pt << endl;
  save_pz(pt);
  
  string pt2 = dir + "pw_z.k" + ks;
  cout << "write p(w|z): " << pt2 << endl;
  save_pw_z(pt2);
}

// p(z) is determinated by the overall proportions
// of biterms in it
void Base::save_pz(string pt) {  
  Pvec<double> pz(K);	          // p(z) = theta
  for (int k = 0; k < K; k++) 
	pz[k] = (nb_z[k] + alpha);
  pz.normalize();

  pz.write(pt);
}

void Base::save_pw_z(string pt) {  
  Pmat<double> pw_z(K, W);   // p(w|z) = phi, size K * M
  for (int k = 0; k < K; k++) {	
	double deno = 2 * nb_z[k] + W * beta;
	
	for (int m = 0; m < W; m++) 
	  pw_z[k][m] = (nwz[m][k] + beta) / deno;
  }
  
  pw_z.write(pt);
}

// format:wi   wj    z 
void Base::save_bz(string dir) {
  string pt = dir + "bz.k" + str_util::itos(K);
  cout << "save bz: " << pt << endl;
  
  ofstream wf(pt.c_str());
  for (int b = 0; b < bs.size(); ++b)
	wf << bs[b].str() << endl;
}
