#include <iostream>
#include <fstream>

#include "sampler.h"
#include "str_util.h"

#include "doc.h"
#include "ibtm.h"

Ibtm::Ibtm(int K, int W, double a, double b, int win, int n_rej):
  Base(K, W, a, b), win(win), n_rej(n_rej), n_b(0) {}

// using batch results to initialize nb_z and nwz
void Ibtm::load_init(string pt) {
  cout << "load bz: " << pt << endl;

  ifstream rf(pt.c_str());
  if (!rf) {
	cout << "[Error] file not find： " << pt << endl;
	exit(1);
  }

  string line;
  int wi, wj, k;
  while (getline(rf, line)) {
	Biterm bi(line);
	if (bs.size() < win)
	  bs.push_back(bi);
	else
	  bs[n_b % win] = bi;
	
	// update recorders
	int k = bi.get_z();
	++nwz[bi.get_wi()][k];
	++nwz[bi.get_wj()][k];
	++nb_z[k];
	++n_b;
  }
  cout << "init n(b):" << n_b << ", bs size:" << bs.size() << endl;
}

void Ibtm::proc_dfile(string pt) {
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
	vector<Biterm> bis;
	doc.gen_biterms(bis);

    for (int b = 0; b < bis.size(); ++b)
      proc_biterm(bis[b]);

	++n_d;	  
  }
  cout << "n(d) in dfile:" << n_d
	   << ", overall n(b):" << n_b << endl;
}

void Ibtm::proc_biterm(Biterm& bi) {
  update_biterm(bi);
  
  // rejuvenate
  vector<int> idxs;
  gen_rej_idx(idxs);

  for (int i = 0; i < idxs.size(); ++i)
	update_biterm(bs[idxs[i]]);
  
  // add to rejuvenated list
  if (bs.size() < win) {
	bs.push_back(bi);
  }
  else {
	assert( bs.size() == win );
	bs[n_b % win] = bi;
  }
  
  // update the biterm counter
  ++n_b;
}

//select biterms index from [0, L-1] for rejevantation
// using fixing window + ... distribution
void Ibtm::gen_rej_idx(vector<int>& idxs) {
  // for samll L, less rejuvenate
  int L = bs.size();
  for (int n = 0; n < min(L-100, n_rej); ++n) {
	int idx = Sampler::uni_sample(L);
	idxs.push_back(idx);
  }
}

// format:wi   wj    z 
void Ibtm::save_bz(string dir) {
  string pt = dir + "bz.k" + str_util::itos(K);
  cout << "save bz: " << pt << endl;
  
  ofstream wf(pt.c_str());
  for (int b = max(long(0), n_b - win); b < n_b; ++b)
	wf << bs[b % win].str() << endl;
}
