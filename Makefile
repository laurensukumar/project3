
GXX49_VERSION := $(shell g++4.9 --version 2>/dev/null)

ifdef GXX49_VERSION
	CXX_COMMAND := g++4.9
else
	CXX_COMMAND := g++
endif

CXX = ${CXX_COMMAND} -std=c++11 -Wall

all: sort_timing run_test

run_test: sort_comparison_test
	./sort_comparison_test

headers: json.hpp rubrictest.hpp timer.hpp sort_comparison.hpp

sort_comparison_test: headers sort_comparison_test.cpp
	${CXX} sort_comparison_test.cpp -o sort_comparison_test

sort_timing: headers sort_timing.cpp
	${CXX} sort_timing.cpp -o sort_timing

clean:
	rm -f sort_comparison_test sort_timing
