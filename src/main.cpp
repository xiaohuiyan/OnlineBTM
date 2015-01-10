#include <cstdlib>
#include <string.h>
#include <string>
#include <iostream>
#include <ctime>

#include "str_util.h"
#include "base.h"
#include "obtm.h"
#include "ibtm.h"

using namespace std;

int main(int argc, char* argv[]) {
  int i = 1;
  string method(argv[i++]);
  // common parameters
  int K = atoi(argv[i++]);          // topic number
  int W = atoi(argv[i++]);			// vocabulary size
  int end_day = atoi(argv[i++]);	// 
  double alpha = atof(argv[i++]);   // hyperparameters of p(z)
  double beta = atof(argv[i++]);    // hyperparameters of p(w|z)
  string pt_init(argv[i++]);
  string doc_dir(argv[i++]);
  string res_dir(argv[i++]);
  printf("=== %s: end_day %d , K %d, W %d, alpha %f, beta %f ====\n",
		 method.c_str(), end_day, K, W, alpha, beta);
  
  Base* mod;
  // model-sepcific parameters
  if (method == "obtm") {
	int n_iter = atoi(argv[i++]);
	mod = new Obtm(K, W, alpha, beta, n_iter);
	printf("Model=obtm, n_iter=%d\n", n_iter);
  }
  else if (method == "ibtm") {
	int win = atoi(argv[i++]);
	int n_rej = atoi(argv[i++]);
	mod = new Ibtm(K, W, alpha, beta, win, n_rej);
	printf("Model=ibtm, win=%d, n_rej=%d\n", win, n_rej);
  }
  else {
	cout << "Unrecognized method:" << argv[1] << endl;
	exit(-1);
  }
  
  // load model init file
  mod->load_init(pt_init);

  for (int day = 1; day <= end_day; ++day) {
	cout << "# day " << day << endl;
	string pt_doc = doc_dir + str_util::itos(day) + ".txt";
	
	clock_t start = clock();
	mod->proc_dfile(pt_doc);
	clock_t end = clock();
	printf("%s, cost %fs\n", method.c_str(), double(end - start)/CLOCKS_PER_SEC);

	// save results
	string res_pfx = res_dir + "d" + str_util::itos(day) + "_";
	mod->save_res(res_pfx);
	mod->save_bz(res_pfx);
  }

  delete mod;
}
