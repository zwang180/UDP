CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lboost_system -lc++abi

all : test

test :	main.o UDPClient.o
	$(LD) main.o UDPClient.o $(LDFLAGS) -o test
main.o : main.cpp UDPClient.h
	$(CXX) $(CXXFLAGS) main.cpp
UDPClient.o : UDPClient.cpp UDPClient.h
	$(CXX) $(CXXFLAGS) UDPClient.cpp
clean :
	rm test *.o
