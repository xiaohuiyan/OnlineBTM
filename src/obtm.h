/**
 * Base model of online BTM
 * Author: Xiaohui Yan(l0he1g@gmail.com)
 * 2013-6-6
 */

#ifndef _OBTM_H
#define _OBTM_H
#include <string>
#include <vector>

#include "base.h"
using namespace std;

class Obtm : public Base {
private:
    int n_iter;

public:
  Obtm(int K, int W, double a, double b, int n_iter);

  void load_init(string pt);

  void proc_dfile(string pt);

private:
  void proc_biterms();
};


#endif
