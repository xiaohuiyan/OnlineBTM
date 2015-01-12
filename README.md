# Code of Online Biterm Topic Model

  The package contains two online algorithms for Biterm Topic Model (BTM): online BTM (oBTM) and incremental BTM (iBTM). oBTM fits an individual BTM in a time slice by using the sufficient statistics as Dirichlet priors; iBTM trains a single model over a biterm stream using incremental Gibbs sampler.

More detail can be referred to the following paper:

   > Xueqi Cheng, Xiaohui Yan, Yanyan Lan, and Jiafeng Guo. BTM: Topic Modeling over Short Texts. TKDE, 2014. 

## Usage ##

The code includes a runnable example, you can run it by:

       $ script/runExample.sh

It trains BTM over the documents in *sample-data/0.txt, 1.txt, ...* and output the topics. The *n.txt* contains the training documents in time slice (supposed to be day) *n*, where each line represents one document with words separated by space as:
> word1 word2 word3 ....

(*Note: the sample data is only used for illustration of the usage of the code. It is not the data set used in the paper.*)

You can change the paths of data files and parameters in *script/runExample.sh* to run over your own data. 

Indeed, the *runExample.sh* processes the input documents in 4 steps.

**1. Index the words in the documents**   
   To simplify the main code, we provide a python script to map each word to a unique ID (starts from 0) in the documents. 

    $ python script/indexDocs.py <doc_dir> <dwid_dir> <voca_pt>
      doc_dir     input doc dir to be indexed, each file records docs in a day, while each line in a file is a doc with the format "word word ..."
      dwid_dir   output doc dir after indexing, each file records docs in a day, while each line is a doc with the format "wordId wordId ..."
      voca_pt   output vocabulary file, each line is a word with the format "wordId    word"

**2. Topic learning** 

       $ ./src/run obtm <K> <W> <alpha> <beta> <n_iter> <docs_dir> <model_dir>
       or
       $ ./src/run ibtm <K> <W> <alpha> <beta> <n_iter> <docs_dir> <model_dir> <win> <n_rej>
    	K	int, number of topics
    	W	int, size of vocabulary
    	alpha	double, Symmetric Dirichlet prior of P(z), like 1
    	beta	double, Symmetric Dirichlet prior of P(w|z), like 0.01
    	docs_dir    string, path of training docs
    	model_dir	string, path of output directory
        win     int, windows size of incremental Gibbs sampler
        n_rej   int, rejuvenation sequence size of incremental Gibbs sampler

   The results will be written into the directory "model_dir":   
   - k20.pw_z: a K*M matrix for P(w|z), suppose K=20   
   - k20.pz:   a K*1 matrix for P(z), suppose K=20
   
**3. Inference topic proportions for documents, i.e., P(z|d)**     
   If you need to analysis the topic proportions of each documents, just run the following common to infer that using the model estimated.

    $ ./src/inf <type> <K> <day> <docs_dir> <model_dir>
      K	int, number of topics, like 20
      day   int, the nth day, like 0, 1, ..
      type	 string, 3 choices:sum_w, sum_b, mix. sum_b is used in our paper.
      docs_dir	string, path of training docs
      model_dir	string, output directory

   The result will be output to "model_dir":   
   - k20.day0.pz_d: a N*K matrix for P(z|d), suppose K=20 and day=0

**4. Results display**    
   Finally, we also provide a python script to illustrate the top words of the topics and their proportions in the collection. 

       $ python topicDisplay.py <model_dir> <K> <voca_pt>
	     model_dir    the output dir of BTM
	     K    the number of topics
	     voca_pt    the vocabulary file


## History ##
- 2015-01-12, v0.5, improve the usability of the code
- 2013-09-25, v0.1

If you have any questions, feel free to contact: [Xiaohui Yan](http://shortext.org "Xiaohui Yan")(xhcloud@gmail.com).
