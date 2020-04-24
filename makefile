all: in2post.x

in2post.x: in2post.cpp stack.h stack.hpp
	g++ -std=c++11 in2post.cpp -o in2post.x
