#include <iostream>
#include <fstream>
#include "doc.h"
#include "obtm.h"

Obtm::Obtm(int K, int W, double a, double b, int n_iter):
  Base(K, W, a, b), n_iter(n_iter) {}

// using batch results to initialize nb_z and nwz
void Obtm::load_init(string pt) {
  cout << "load bz: " << pt << endl;

  ifstream rf(pt.c_str());
  if (!rf) {
	cout << "[Error] file not find： " << pt << endl;
	exit(1);
  }

  string line;
  int wi, wj, k;
  int n_b = 0;
  while (getline(rf, line)) {
	istringstream iss(line);
	iss >> wi >> wj >> k;
	++nwz[wi][k];
	++nwz[wj][k];
	++nb_z[k];
	++n_b;
  }
  cout << "init n(b):" << n_b << endl;
}

void Obtm::proc_dfile(string pt) {
  cout << "load docs: " << pt << endl;
  ifstream rf(pt.c_str());
  if (!rf) {
	cout << "file not find:" << pt << endl;
	exit(-1);
  }

  string line;
  int n_d = 0;
  while(getline(rf, line)) {
	if (n_d > 0 && n_d % 100000 == 0)
	  cout << "read doc:" << n_d << endl;
	
	Doc doc(line);
	doc.gen_biterms(bs);
	++n_d;	  
  }
  cout << "n(d) in dfile:" << n_d << endl;
  proc_biterms();
  // biterms are discard after processing
  bs.clear();
}

void Obtm::proc_biterms() {
  cout << "begin estimate, n(b) = " << bs.size() << endl;
  // update biterms in this day
  for (int it = 0; it < n_iter; ++it) {
	//printf( "it %d/%d\n", it, n_iter);
	
	for (int b = 0; b < bs.size(); ++b)
	  update_biterm(bs[b]);
  }
}
