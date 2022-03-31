#pragma once
#include <iostream>

template <typename T>
class P {
public:
	virtual void print() =0 ;
	virtual ~P() =0;
};

 P<int>::~P() {}

template <typename T>
class C : public P<typename T> {
	T x;
public:
	C(T _x) : x(_x) {}
	void print() { std::cout << x; }
	~C() {}
};