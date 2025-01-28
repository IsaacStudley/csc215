CXX = g++
CXXFLAGS = -std=c++11 -g

test: BigInt.cpp BigInt.h test_bigints.cpp
	$(CXX) $(CXXFLAGS) -o test test_bigints.cpp BigInt.cpp

clean:
	rm -f test