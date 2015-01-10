#ifndef _DOC_H
#define _DOC_H

#include <string>
#include <vector>
#include <cassert>
#include <sstream>

#include "biterm.h"

using namespace std;

class Doc {
private:
  vector<int> ws;				// word sequence
  //int day;
  
public: 
  Doc(const string& s) {read_doc(s);}

  int size() const {return ws.size();}
  
  const vector<int>& get_ws() const {return ws;}
  
  const int get_w(int i) const {
	assert(i < ws.size());
	return ws[i];
  }

  //const int get_day() const {return day;}

  void gen_biterms(vector<Biterm>& bs) const {
	for (int i = 0; i < ws.size()-1; ++i)
	  for (int j = i+1; j < ws.size(); ++j)
		bs.push_back( Biterm(ws[i], ws[j]) );
  }

private:
  void read_doc(const string& s) {
    istringstream iss(s);
	//iss >> day;
	
	int w;
    while (iss >> w)  ws.push_back(w);
  }
};
  
#endif
