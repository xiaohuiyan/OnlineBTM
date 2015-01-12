#!/usr/bin/env python
#coding=utf-8
# translate word into id in documents
import sys, os

w2id = {}

def indexDir(dir, res_dir):
    for f in os.listdir(dir):
        indexFile(dir + f, res_dir + f)
    
def indexFile(pt, res_pt):
    print 'index file: ', pt
    wf = open(res_pt, 'w')
    for l in open(pt):
        ws = l.strip().split()
        for w in ws:
            if not w2id.has_key(w):
                w2id[w] = len(w2id)
                
        wids = [w2id[w] for w in ws]        
        print >>wf, ' '.join(map(str, wids))
        
    print 'write file: ', res_pt


def write_w2id(res_pt):
    print 'write:', res_pt
    wf = open(res_pt, 'w')
    for w, wid in sorted(w2id.items(), key=lambda d:d[1]):
        print >>wf, '%d\t%s' % (wid, w)
        
        
if __name__ == '__main__':
    if len(sys.argv) < 4:
        print 'Usage: python %s <doc_dir> <dwid_dir> <voca_pt>' % sys.argv[0]
        print '\tdoc_dir   input doc dir to be indexed, each file records docs in a day, while each line in a file is a doc with the format "word word ..."'
        print '\tdwid_dir   output doc dir after indexing, each file records docs in a day, while each line is a doc with the format "wordId wordId ..."'
        print '\tvoca_pt   output vocabulary file, each line is a word with the format "wordId    word"' 
        exit(1)
        
    doc_dir = sys.argv[1]
    dwid_dir = sys.argv[2]
    voca_pt = sys.argv[3]
    indexDir(doc_dir, dwid_dir)
    print 'n(w)=', len(w2id)
    write_w2id(voca_pt)
