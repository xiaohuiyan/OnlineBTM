/**
 * OBTM model of online BTM
 * Author: Xiaohui Yan(xhcloud@gmail.com)
 * 2013-6-6
 */
#ifndef _OBTM_H
#define _OBTM_H

#include <vector>

#include "biterm.h"
#include "pvec.h"
#include "pmat.h"

using namespace std;

class OBTM {
private:
  int K;				// topic number
  int W;				// vocabulary size
  int n_iter;			// maximum number of iteration of Gibbs Sampling

  double lam;					// decay coefficient
  Pvec<double> alpha;	// hyperparameters of p(z)
  Pmat<double> beta;			// hyperparameters of p(w|z)
  // record the sum over W in beta to save computation, size Kx1
  Pvec<double> beta_sum;		

  // sample recorders
  Pvec<int> nb_z;   	// n(b|z), size K*1  
  Pmat<int> nwz;	    // n(w,z), size M*K

  vector<Biterm> bs;  // training biterms
  
public:
  OBTM(int K, int W, double a, double b, int n_iter, double l);
  
  void run(string input_dir, int n_day, string res_dir);

private:
  void model_init();
  void load_docs(string dfile);
  void proc_day(string pt);

  void prepare_day();
  
  // run a batch Gibbs sampling precedure
  void Gibbs_sampling();

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
