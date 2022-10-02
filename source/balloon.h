#ifndef BALLOON_H
#define BALLOON_H

#ifndef OBJECT_H
#include "Object.h"
#endif

#ifndef VECTOR_H
#include "Vector.h"
#endif

#ifndef CONSTANTS_H
#include "constants.h"
#endif

#ifndef STD_HEADERS
#include "std_headers.h"
#endif

class Balloon : public Object{
	public:
		Balloon(Vector* pos,Vector* vel,int color);
		virtual void draw();
		virtual void drawobj(int color_to_use);
};

#endif
