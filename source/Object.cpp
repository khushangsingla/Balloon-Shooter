#include "Object.h"
Vector Object::getPosition(){
	return pos;
}
Object::Object(Vector pos,Vector vel,int w, int h,int color) : Fl_Widget(pos.getX(),pos.getY(),w,h){
	this->pos=pos;
	this->vel=vel;
	this->color=color;
	this->w=w;
	this->h=h;
}
void Object::updatePosition(){
	pos=pos+vel*STEP_TIME;
}
void Object::refresh(){
	this->drawobj(BACKGROUND);
	this->updatePosition();
	this->drawobj(this->color);
}

