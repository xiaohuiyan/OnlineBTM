CC=g++
CFLAGS=-c -pipe -O3
#SRC=$(wildcard *.cpp)
MODEL_OBJ=base.o btmUpto.o obtm.o ibtm.o main.o
MODEL_EXE=run

all:$(MODEL_EXE) 

$(MODEL_EXE):$(MODEL_OBJ)
	$(CC) $(MODEL_OBJ) -o $@

main.o:base.h obtm.h ibtm.h
base.h.o:base.h biterm.h doc.h
btmUpto.o:base.h biterm.h doc.h
obtm.o:obtm.h base.h biterm.h doc.h
ibtm.o:ibtm.h base.h biterm.h doc.h

%.o:%.cpp
	$(CC) $(INCLUDE) $(CFLAGS) $< -o $@

clean:
	rm -rf $(MODEL_OBJ) $(MODEL_EXE)
