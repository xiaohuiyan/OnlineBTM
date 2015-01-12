CC=g++
CFLAGS=-c -pipe -O3
#SRC=$(wildcard *.cpp)
MODEL_EXE=run infer

all:$(MODEL_EXE) 

run:obtm.o ibtm.o main.o
	$(CC) $^ -o $@

infer:infer.o
	$(CC) $^ -o $@

main.o:obtm.h ibtm.h
obtm.o:obtm.h biterm.h doc.h
ibtm.o:ibtm.h biterm.h doc.h
infer.o:infer.h doc.h

%.o:%.cpp
	$(CC) $(INCLUDE) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(MODEL_EXE)
