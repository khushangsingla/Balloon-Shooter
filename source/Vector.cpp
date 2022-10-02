#include "Vector.h"


Vector::Vector(double x,double y){
	this->x=x;
	this->y=y;
}
Vector Vector::operator+(Vector v2){//for sum of two vectors.
	Vector ans(this->x+v2.x,this->y+v2.y);
	return ans;
}
double Vector::getX(){
	return x;
}
double Vector::getY(){
	return y;
}
Vector Vector::operator*(double k){
	Vector ans(x*k,y*k);
	return ans;
}

Vector operator*(double k,Vector v){
	Vector ans=v*k;
	return ans;
}
