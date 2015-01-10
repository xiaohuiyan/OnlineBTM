#!/bin/bash
# -------- twitter ------------
data=twitter
W=98857
end_day=2
K=20

method=obtm
#method=ibtm

alpha=0.01
beta=0.01

data_dir=/home/xh/mp/onlineBTM/data/$data/

doc_dir=${data_dir}mid/docs/
pt_init=${data_dir}init/mat/d0_bz.k$k
res_dir=${data_dir}${method}/mat/

echo "=============== Topic Learning ============="
echo 'batch BTM init:'$pt_init
if [ "$method" = "obtm" ]; then
	niter=100
	./src/run obtm $K $W $end_day $alpha $beta $pt_init $doc_dir $res_dir $niter
elif [ "$method" = "ibtm" ]; then
	win=2000000
	n_rej=100
	./src/run ibtm $K $W $end_day $alpha $beta $pt_init $doc_dir $res_dir $win $n_rej
else
	echo "Unrecognized method:"$method
	exit
fi

echo "================ Infer P(z|d)==============="
doc_infer_pt=${data_dir}mid/doc_wid.txt
for day in `seq 1 $end_day`; do
 	res_dir=${data_dir}${method}/mat/d${day}_
 	echo 'infer:'$doc_infer_pt
 	./init/btm inf $k $doc_infer_pt $res_dir
done

echo "================ Topic Display ============="
for day in `seq 0 $end_day`; do
	echo "---------- day $day --------------"
	python tran.py $K $day
done