/**
 * Base model of online BTM
 * Author: Xiaohui Yan(l0he1g@gmail.com)
 * 2013-6-6
 */
#ifndef _BASE_H
#define _BASE_H

#include <vector>

#include "biterm.h"
#include "pvec.h"
#include "pmat.h"

using namespace std;

class Base {
protected:
  int K;				// topic number
  int W;				// vocabulary size

  vector<Biterm> bs;
  double alpha;			// hyperparameters of p(z)
  double beta;			// hyperparameters of p(w|z)

  // sample recorders
  Pvec<int> nb_z;   	// n(b|z), size K*1  
  Pmat<int> nwz;	    // n(w,z), size M*K
  
public:
  Base(int K, int W, double a, double b);

  // load batch initialization  
  virtual void load_init(string pt);

  virtual void proc_dfile(string pt) = 0;
  
  void save_res(string dir);
  virtual void save_bz(string dir);			// save topic assignments
  
  virtual ~Base() {}
 protected:
  // update estimate of a biterm
  void update_biterm(Biterm& bi);
  
  // reset topic proportions for biterm b
  void reset_biterm_topic(Biterm& bi);
  
  // assign topic proportions for biterm b
  void assign_biterm_topic(Biterm& bi, int k);
  
  // compute condition distribution p(z|b)
  void compute_pz_b(Biterm& bi, Pvec<double>& p);

  virtual void save_pz(string pt);
  virtual void save_pw_z(string pt);
};

#endif
