// file array.cpp

#include <iostream>
#include "array.h"

using namespace std;

Array::Array() {
	length = 0;
	data = 0;
}

Array::Array(int numberofintegers, int value) {
	length = numberofintegers;
	data = new int[numberofintegers];
	for(int i=0; i<length; ++i)
		data[i] = value;
}

Array::Array(const Array& a) {
	length = a.length;
	data = new int[length];
	for(int i=0; i<length; ++i)
		data[i] = a.data[i];
}

Array::~Array() {
	delete [] data;
}

Array& Array::operator=(const Array& a) {
	if( this != &a ) {
		delete [] data;
		length = a.length;
	        data = new int[length];
        	for(int i=0; i<length; ++i)
                	data[i] = a.data[i];
	}
	return *this;
}
