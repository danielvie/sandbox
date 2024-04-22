// file array.h

#ifndef ARRAY_H
#define ARRAY_H

class Array {

public:
	Array();
	Array(int numberofintegers, int value);
	Array(const Array&);
	~Array();
	Array& operator=(const Array&);

private:
	int *data;
	int length;
};

#endif
