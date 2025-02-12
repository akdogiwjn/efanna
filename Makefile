GXX=g++ -std=c++11
#OPTM=-O3 -msse2 -msse4 -fopenmp
OPTM=-O3 -march=native -fopenmp
CPFLAGS=$(OPTM) -Wall -DINFO
LDFLAGS=$(OPTM) -Wall -lboost_timer -lboost_chrono -lboost_system -DINFO

INCLUDES=-I./ -I./algorithm -I./general

SAMPLES=$(patsubst %.cc, %, $(wildcard samples/*.cc samples_hashing/*.cc))
SAMPLE_OBJS=$(foreach sample, $(SAMPLES), $(sample).o)

HEADERS=$(wildcard ./*.hpp ./*/*.hpp)

#EFNN is currently header only, so only samples will be compiled

#SHARED_LIB=libefnn.so
#OBJS=src/efnn.o

# all: $(SHARED_LIB) $(SAMPLES)

#$(SHARED_LIB): $(OBJS)
#	$(GXX) $(LDFLAGS) $(LIBS) $(OBJS) -shared -o $(SHARED_LIB)

# $(SAMPLES): %: %.o
# 	$(GXX) $^ -o $@ $(LDFLAGS) $(LIBS)

# %.o: %.cpp $(HEADERS)
# 	$(GXX) $(CPFLAGS) $(INCLUDES) -c $*.cpp -o $@

# %.o: %.cc $(HEADERS)
# 	$(GXX) $(CPFLAGS) $(INCLUDES) -c $*.cc -o $@

tree: samples/efanna_index_buildtrees.o
	$(GXX) $^ -o samples/tree $(LDFLAGS) $(LIBS)
samples/efanna_index_buildtrees.o: samples/efanna_index_buildtrees.cc $(HEADERS)
	$(GXX) $(CPFLAGS) $(INCLUDES) -c $*.cc -o $@

eva:samples/evaluate_tree.o
	$(GXX) $^ -o samples/eva $(LDFLAGS) $(LIBS)
samples/evaluate_tree.o: samples/evaluate_tree.cc $(HEADERS)
	$(GXX) $(CPFLAGS) $(INCLUDES) -c $*.cc -o $@

clean:
	rm -rf $(OBJS)
	rm -rf $(SHARED_LIB)
	rm -rf $(SAMPLES)
	rm -rf $(SAMPLE_OBJS)
