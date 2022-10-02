#ifndef BOW_H
#define BOW_H

#ifndef STD_HEADERS
#include "std_headers.h"
#endif

#ifndef VECTOR_H
#include "Vector.h"
#endif

#ifndef CONSTANTS_H
#include "constants.h"
#endif

class IdleBow : public Fl_Widget{
	public:
		IdleBow() :
			Fl_Widget(0,0,WINDOW_X,WINDOW_Y){}
		void draw();
};
class StretchedBow : public Fl_Widget{
	double angle;
	public:
		StretchedBow() :
			Fl_Widget(0,0,WINDOW_X,WINDOW_Y){}
		void setAngle(double angle);
		double getAngle();
		void draw();
};

#endif
