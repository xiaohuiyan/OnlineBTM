/**
 * Base model of online BTM
 * Author: Xiaohui Yan(l0he1g@gmail.com)
 * 2013-6-6
 */
#ifndef _IBTM_H
#define _IBTM_H

#include <string>
#include <vector>

#include "biterm.h"
#include "base.h"

using namespace std;

class Ibtm : public Base {
private:
  int n_rej;	// number of biterms to rejuvenate
  int win;		// size of the biterm sliding window
  long n_b;		// number of biterms processed
  
public:
  Ibtm(int K, int W, double a, double b, int win, int n_rej);
  void load_init(string pt);
  void proc_dfile(string pt);
  
  void save_bz(string dir);			// save topic assignments
private:
  void proc_biterm(Biterm& bi);
  void gen_rej_idx(vector<int>& idxs);
};


#endif
