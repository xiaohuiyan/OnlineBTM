#!/bin/bash
# run an toy example for BTM
set -e

K=20   # number of topics
W=48267   # vocabulary size

alpha=`echo "scale=3;50/$K"|bc`
beta=0.005
n_day=3
input_dir=../sample-data/
output_dir=../output/
dwid_dir=${output_dir}doc_wids/
model_dir=${output_dir}model/

voca_pt=${output_dir}voca.txt

method=ibtm   # must be obtm or ibtm

echo "=============== Index Docs ============="
python indexDocs.py $input_dir $dwid_dir $voca_pt

## learning parameters p(z) and p(z|w)
echo "=============== Topic Learning ============="
make -C ../src
## run obtm
if [ "$method" = "obtm" ]; then
	n_iter=500
	lam=1
	../src/run obtm $K $W $alpha $beta $dwid_dir $n_day $model_dir $n_iter $lam
else
	win=2000000
	n_rej=100
	../src/run ibtm $K $W $alpha $beta $dwid_dir $n_day $model_dir $win $n_rej
fi

# ## infer p(z|d) for each doc
echo "================ Infer P(z|d)==============="
for day in `seq 0 $[$n_day-1]`; do
	dwid_pt=${dwid_dir}${day}.txt
	echo "../src/infer sum_b $K $day $dwid_pt $model_dir"
	../src/infer sum_b $K $day $dwid_pt $model_dir
done

# ## output top words of each topic
# echo "================ Topic Display ============="
for day in `seq 0 $[$n_day-1]`; do
	echo "---------- day $day --------------"
	python topicDisplay.py $model_dir $K $day $voca_pt
done
