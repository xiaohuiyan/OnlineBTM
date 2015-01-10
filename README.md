# Code of Online Biterm Topic Model

  The package contains two online algorithms for Biterm Topic Model (BTM): online BTM (oBTM) and incremental BTM (iBTM). oBTM fits an individual BTM in a time slice by using the sufficient statistics as Dirichlet priors; iBTM trains a single model over a biterm stream using incremental Gibbs sampler.

More detail can be referred to the following paper:

   > Xueqi Cheng, Xiaohui Yan, Yanyan Lan, and Jiafeng Guo. BTM: Topic Modeling over Short Texts. TKDE, 2014. 

## Usage ##

1. Topic learning:

       $ ./src/run obtm <K> <W> <alpha> <beta> <n_iter> <pt_input> <pt_outdir>
       or
       $ ./src/run ibtm <K> <W> <alpha> <beta> <n_iter> <pt_input> <pt_outdir> <win> <n_rej>
    	K	int, number of topics
    	W	int, size of vocabulary
    	alpha	double, Symmetric Dirichlet prior of P(z), like 1
    	beta	double, Symmetric Dirichlet prior of P(w|z), like 0.01
    	pt_input    string, path of training docs
    	pt_outdir	string, path of output directory
        win     int, windows size of incremental Gibbs sampler
        n_rej   int, rejuvenation sequence size of incremental Gibbs sampler

2. Inference topic proportions for documents, i.e., P(z|d):

        $ ./src/btm inf <type> <K> <pt_input> <pt_outdir>
    	K	int, number of topics, like 20
    	type	 string, 3 choices:sum_w, sum_b, mix. sum_b is used in our paper.
    	pt_input	string, path of training docs
    	pt_outdir	string, output directory


3. Results display

       $ python script/tran.py <K> <day>

  Output the topics with top 10 words of the toy example.

4. Run a complete toy example

       $ bat.sh

## Input & Output Format ##

1. Input

 The input file contains all the training documents with their time slice (for example, a day) ids. Each line records a short text document with the following format:
       time_slice_id     wid1 wid2 ....
 
 Both the two types of ids are integers starts from 0. A sample input file is given in *smaple-data/doc_wids.txt*. (*Note: the sample data is only used for illustration of the usage of the code. It is not the data set used in the paper.*)


2. Output

 The estimation program will output into the directory "outputs":   
 - pw_z.k20.d1: a K*M matrix for P(w|z), suppose K=20 and day = 1 
 - pz.k20.d1:   a K*1 matrix for P(z), suppose K=20 and day = 1

 The inference program will produce:   
 - pz_d.k20.d1: a N*K matrix for P(z|d), suppose K=20 and day = 1

## History ##
- 2013-09-25, v0.1

If you have any questions, feel free to contact: [Xiaohui Yan](http://shortext.org "Xiaohui Yan")(xhcloud@gmail.com).
