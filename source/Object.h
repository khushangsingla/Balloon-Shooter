#ifndef OBJECT_H
#define OBJECT_H

#ifndef STD_HEADERS
#include "std_headers.h"
#endif

#ifndef CONSTANTS_H
#include "constants.h"
#endif

#ifndef VECTOR_H
#include "Vector.h"
#endif

class Object : public Fl_Widget{//The superclass for various objects
	protected:
		Vector pos,vel;
		int w,h;
		int color;
	public:
		Vector getPosition();
		Object(Vector pos,Vector vel,int w, int h,int color);
		virtual void draw()=0;
		virtual void updatePosition();
		virtual void drawobj(int color_to_use)=0;
		virtual void refresh();
};

#endif
