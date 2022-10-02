#ifndef ARROW_H
#define ARROW_H

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

class Arrow : public Object{
	Vector acc;
	public:
		Arrow(Vector* pos,Vector* vel);
		void drawobj(int color_to_use);
		void draw();
		virtual void updatePosition();
};

#endif
