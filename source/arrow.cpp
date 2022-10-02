#include "arrow.h"

Arrow::Arrow(Vector* pos,Vector* vel) ://constructor
	Object(*pos,*vel,0,0,ARROW_COLOR){
		acc=Vector(0,GRAVITY);
	}
void Arrow::drawobj(int color_to_use){
	fl_color(color_to_use);
	fl_line_style(0,ARROW_WIDTH,0);
	double angle=atan(vel.getY()*-1.0/vel.getX());
	fl_line(pos.getX(),pos.getY(),pos.getX()-ARROW_LENGTH*cos(angle),pos.getY()+ARROW_LENGTH*sin(angle));
}
void Arrow::draw(){
	drawobj(ARROW_COLOR);
}
void Arrow::updatePosition(){//to take the effect of acceleration.
	vel=vel+acc*STEP_TIME;
	pos=pos+vel*STEP_TIME;
}

