#include "balloon.h"

Balloon::Balloon(Vector* pos,Vector* vel,int color) : Object(*pos,*vel,BALLOON_WIDTH,BALLOON_HEIGHT,color){}

void Balloon::draw(){
	fl_color(color);
	fl_pie(pos.getX()-w/2,pos.getY()-h/2,w,h,0,360);
}

void Balloon::drawobj(int color_to_use){
	fl_color(color_to_use);
	fl_pie(pos.getX()-w/2,pos.getY()-h/2,w,h,0,360);
}
