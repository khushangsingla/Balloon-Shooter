#ifndef VECTOR_H
#define VECTOR_H

#ifndef STD_HEADERS
#include "std_headers.h"
#endif

class Vector{
	private:
		double x,y;
	public:
		Vector(){};
		Vector(double x,double y);
		Vector operator+(Vector v2);
		double getX();
		double getY();
		Vector operator*(double k);
};
Vector operator*(double k,Vector v);

#endif
