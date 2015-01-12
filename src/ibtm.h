/**
 * IBTM algorithm of online BTM
 * Author: Xiaohui Yan(xhcloud@gmail.com)
 * 2013-6-6
 */
#ifndef _IBTM_H
#define _IBTM_H

#include <string>
#include <vector>

#include "biterm.h"
#include "pvec.h"
#include "pmat.h"

using namespace std;

class IBTM {
private:
  int K;				// topic number
  int W;				// vocabulary size

  double alpha;			// hyperparameters of p(z)
  double beta;			// hyperparameters of p(w|z)

  int n_rej;	// number of biterms to rejuvenate
  int win;		// size of the biterm sliding window
  long n_b;		// number of biterms processed

  // sample recorders
  Pvec<int> nb_z;	// n(b|z), size K*1
  Pmat<int> nwz;	  // n(w,z), size K*W

  vector<Biterm> bs;  // training biterms
  
public:
  IBTM(int K, int W, double a, double b, int win, int n_rej);
  
  void run(string input_dir, int n_day, string res_dir);
  
  void proc_day(string pt);
  
private:
  void proc_biterm(Biterm& bi);
  void gen_rej_idx(vector<int>& idxs);

  // update estimate of a biterm
  void update_biterm(Biterm& bi);
  
  // reset topic proportions for biterm b
  void reset_biterm_topic(Biterm& bi);
  
  // assign topic proportions for biterm b
  void assign_biterm_topic(Biterm& bi, int k);
  
  // compute condition distribution p(z|b)
  void compute_pz_b(Biterm& bi, Pvec<double>& p);

  void save_res(string dir);
  void save_pz(string pt);
  void save_pw_z(string pt);
};


#endif
