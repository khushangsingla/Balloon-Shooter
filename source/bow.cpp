#include "bow.h"

void IdleBow::draw(){
	fl_line_style(0,BOW_THICKNESS,0);
	fl_color(BOW_COLOR);
	fl_arc(BOW_CENTER_X-BOW_WIDTH/2,BOW_CENTER_Y-BOW_HEIGHT/2,BOW_WIDTH,BOW_HEIGHT,-90,90);
	fl_line_style(0,BOW_STRING_THICKNESS,0);
	fl_color(BOW_STRING_COLOR);
	fl_line(BOW_CENTER_X,BOW_CENTER_Y-BOW_HEIGHT/2,BOW_CENTER_X,BOW_CENTER_Y+BOW_HEIGHT/2);
	fl_line_style(0,ARROW_WIDTH,0);
	fl_color(ARROW_COLOR);
	fl_line(BOW_CENTER_X,BOW_CENTER_Y,BOW_CENTER_X+ARROW_LENGTH,BOW_CENTER_Y);
}

void StretchedBow::setAngle(double angle){
	this->angle=angle;
}

double StretchedBow::getAngle(){
	return angle;
}

void StretchedBow::draw(){
	fl_line_style(0,ARROW_WIDTH,0);
	fl_color(ARROW_COLOR);
	Vector arrow_end=Vector(BOW_CENTER_X-ARROW_LENGTH*cos(angle)/2.0,BOW_CENTER_Y+ARROW_LENGTH*sin(angle)/2);
	fl_line(arrow_end.getX(),arrow_end.getY(),BOW_CENTER_X+ARROW_LENGTH*cos(angle)/2.0,BOW_CENTER_Y-ARROW_LENGTH*sin(angle)/2.0);
	fl_line_style(0,BOW_THICKNESS,0);
	fl_color(BOW_COLOR);
	fl_begin_line();
	fl_arc(arrow_end.getX(),arrow_end.getY(),3*ARROW_LENGTH/5,angle*180/M_PI-60,angle*180/M_PI+60);
	fl_end_line();
	fl_line_style(0,BOW_STRING_THICKNESS,0);
	fl_color(BOW_STRING_COLOR);
	fl_line(arrow_end.getX(),arrow_end.getY(),3*ARROW_LENGTH*cos(angle+M_PI/3)/5+arrow_end.getX(),arrow_end.getY()-3*ARROW_LENGTH*sin(angle+M_PI/3)/5);
	fl_line(arrow_end.getX(),arrow_end.getY(),3*ARROW_LENGTH*cos(angle-M_PI/3)/5+arrow_end.getX(),arrow_end.getY()-3*ARROW_LENGTH*sin(angle-M_PI/3)/5);
}

