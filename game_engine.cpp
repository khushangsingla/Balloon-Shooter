#include<iostream>
#include <stdexcept>
#include<cmath>
#include<stdlib.h>
#include<FL/Fl.H>
#include<FL/Fl_Window.H>
#include<FL/Fl_Box.H>
#include<FL/fl_draw.H>
#include<ctime>
#include<time.h>
#include<vector>
#include<string>
//List of constants used
#define WINDOW_X 1280
#define WINDOW_Y 720
#define ARROW_COLOR 120
#define BACKGROUND 0
const double STEP_TIME=0.01;
const int GRAVITY=500;
const int BALLOON_WIDTH=WINDOW_X/20;
const int BALLOON_HEIGHT=WINDOW_Y/8;
const int BALLOON_SPEED=150;
const int BALLOON_COLOR=58;
const int ARROW_WIDTH=2;
const int ARROW_LENGTH=WINDOW_X/13;
const int ARROW_SPEED=1000;
const int TIME_DIFF=3;
const int BOW_COLOR=73;
const int BOW_STRING_COLOR=48;
const int BOW_WIDTH=WINDOW_X/14;
const int BOW_HEIGHT=3*WINDOW_Y/16;
const int BOW_CENTER_X=3*WINDOW_X/40;
const int BOW_CENTER_Y=25*WINDOW_Y/32;
const int BOW_THICKNESS=5;
const int BOW_STRING_THICKNESS=3;
const double TIME_REDN=STEP_TIME/10;
using namespace std;
class Vector{
	private:
		double x,y;
	public:
		Vector(){}
		Vector(double x,double y){
			this->x=x;
			this->y=y;
		}
		Vector operator+(Vector v2){//for sum of two vectors.
			Vector ans(this->x+v2.x,this->y+v2.y);
			return ans;
		}
		double getX(){
			return x;
		}
		double getY(){
			return y;
		}
		Vector operator*(double k){
			Vector ans(x*k,y*k);
			return ans;
		}
};
Vector operator*(double k,Vector v){
	Vector ans=v*k;
	return ans;
}
class Object : public Fl_Widget{//The superclass for various objects
	protected:
		Vector pos,vel;
		int w,h;
		int color;
	public:
		Vector getPosition(){
			return pos;
		}
		Object(Vector pos,Vector vel,int w, int h,int color) : Fl_Widget(pos.getX(),pos.getY(),w,h){
			this->pos=pos;
			this->vel=vel;
			this->color=color;
			this->w=w;
			this->h=h;
		}
		virtual void draw()=0;
		virtual void updatePosition(){
			pos=pos+vel*STEP_TIME;
		}
		virtual void drawobj(int color_to_use)=0;
		virtual void refresh(){
			this->drawobj(BACKGROUND);
			this->updatePosition();
			this->drawobj(this->color);
		}
};
class Balloon : public Object{
	public:
		Balloon(Vector* pos,Vector* vel,int color) : Object(*pos,*vel,BALLOON_WIDTH,BALLOON_HEIGHT,color){}
		virtual void draw(){
			fl_color(color);
			fl_pie(pos.getX()-w/2,pos.getY()-h/2,w,h,0,360);
		}
		virtual void drawobj(int color_to_use){
			fl_color(color_to_use);
			fl_pie(pos.getX()-w/2,pos.getY()-h/2,w,h,0,360);
		}
};
class Arrow : public Object{
	Vector acc;
	public:
		Arrow(Vector* pos,Vector* vel) ://constructor
			Object(*pos,*vel,0,0,ARROW_COLOR){
				acc=Vector(0,GRAVITY);
			}
		void drawobj(int color_to_use){
			fl_color(color_to_use);
			fl_line_style(0,ARROW_WIDTH,0);
			double angle=atan(vel.getY()*-1.0/vel.getX());
			fl_line(pos.getX(),pos.getY(),pos.getX()-ARROW_LENGTH*cos(angle),pos.getY()+ARROW_LENGTH*sin(angle));
		}
		void draw(){
			drawobj(ARROW_COLOR);
		}
		virtual void updatePosition(){//to take the effect of acceleration.
			vel=vel+acc*STEP_TIME;
			pos=pos+vel*STEP_TIME;
		}
};
class IdleBow : public Fl_Widget{
	public:
		IdleBow() :
			Fl_Widget(0,0,WINDOW_X,WINDOW_Y){}
		void draw(){
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
};
class StretchedBow : public Fl_Widget{
	double angle;
	public:
		StretchedBow() :
			Fl_Widget(0,0,WINDOW_X,WINDOW_Y){}
		void setAngle(double angle){
			this->angle=angle;
		}
		double getAngle(){
			return angle;
		}
		void draw(){
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
};
class GameEngine : public Fl_Widget{//the draw function of this class controls the functioning of the game.
	private:
		vector<Balloon*> balloons;
		vector<Arrow*> arrows;
		IdleBow* idle_bow;
		StretchedBow* stretched_bow;
		double time_diff=TIME_DIFF;
		double time_redn=TIME_REDN;
		time_t start_time;
		int Score;
		static void Timer_CB(void *userdata) {
			GameEngine *o = (GameEngine*)userdata;
			o->redraw();
			Fl::repeat_timeout(STEP_TIME, Timer_CB, userdata);
		}
	public:
		GameEngine()://Constructor
			Fl_Widget(0,0,WINDOW_X,WINDOW_Y){
				Score=0;
				idle_bow=new IdleBow();
				stretched_bow=new StretchedBow();
				stretched_bow->hide();
				balloons.push_back(new Balloon(new Vector(500,WINDOW_Y),new Vector(0,-1*BALLOON_SPEED),BALLOON_COLOR));
				start_time=time(NULL);
				Fl::add_timeout(STEP_TIME, Timer_CB, (void*)this);
		}
		~GameEngine(){//Destructor
			for(int i=0;i<balloons.size();i++){
				delete balloons[i];
			}
			for(int j=0;j<arrows.size();j++){
				delete arrows[j];
			}
			delete idle_bow;
			delete stretched_bow;
		}
		void draw(){
			fl_color(BACKGROUND);
			fl_polygon(0,0,90,0,90,90,0,90);
			fl_color(93);
			fl_font(FL_HELVETICA,40);
			char score_ch[10];
			string score_str=to_string(Score);
			for(int i=0;i<score_str.length();i++){
				score_ch[i]=score_str[i];
				score_ch[i+1]='\0';
			}
			fl_draw(score_ch,50,50);
			time_t curr_time=time(NULL);
			//Balloons pop randomly and move.
			if(curr_time-start_time > time_diff){
				start_time=curr_time;
				int curr_x=rand()%(WINDOW_X-4*BALLOON_WIDTH)+3*BALLOON_WIDTH;
				balloons.push_back(new Balloon(new Vector(curr_x,WINDOW_Y),new Vector(0,-1*BALLOON_SPEED),BALLOON_COLOR));
				balloons[balloons.size()-1]->draw();
			}
			for(int i=0;i<balloons.size();i++){
				if(balloons[i]->getPosition().getY()<-1*BALLOON_HEIGHT){
					balloons[i]->drawobj(BACKGROUND);
					delete balloons[i];
					balloons.erase(balloons.begin()+i);
					i--;
				}
			}
			if(time_diff>1)
				time_diff-=time_redn;
			for(int i=0;i<balloons.size();i++){
				balloons[i]->refresh();
			}
			for(int i=0;i<arrows.size();i++){
				arrows[i]->refresh();
			}
			for(int i=0;i<arrows.size();i++){
				if(arrows[i]->getPosition().getY()>WINDOW_Y+ARROW_LENGTH || arrows[i]->getPosition().getX()>WINDOW_X+ARROW_LENGTH){
					delete arrows[i];
					arrows.erase(arrows.begin()+i);
					i--;
				}
			}
			//to check for collisions
			for(int i=0;i<arrows.size();i++){
				for(int j=0;j<balloons.size();j++){
					int x_a=arrows[i]->getPosition().getX();
					int y_a=arrows[i]->getPosition().getY();
					int x_b=balloons[j]->getPosition().getX();
					int y_b=balloons[j]->getPosition().getY();
					bool is_colliding=true;
					is_colliding=is_colliding && x_a<x_b+BALLOON_WIDTH*49/100 && x_a>x_b-BALLOON_WIDTH*49/100;
					is_colliding= is_colliding && y_a<y_b+BALLOON_HEIGHT*49/100 && y_a>y_b-BALLOON_HEIGHT*49/100;
					if(is_colliding){
						balloons[j]->drawobj(BACKGROUND);
						delete balloons[j];
						balloons.erase(balloons.begin()+j);
						j--;
						Score++;
					}
				}
			}
			idle_bow->redraw();
		}
		virtual int handle(int e){
			if(e==FL_PUSH){
				if(Fl::event_x()<BOW_CENTER_X && Fl::event_x()>BOW_CENTER_X-BOW_WIDTH && Fl::event_y()>BOW_CENTER_Y-BOW_WIDTH/2 && Fl::event_y()<BOW_CENTER_Y+BOW_WIDTH/2){
					idle_bow->hide();
					stretched_bow->show();
					e=FL_DRAG;
				}
				else
					return 0;
			}
			if(e==FL_DRAG){
				int deno=(BOW_CENTER_X-Fl::event_x());
				if(deno!=0){
					stretched_bow->hide();
					stretched_bow->setAngle(atan(1.0*(Fl::event_y()-BOW_CENTER_Y)/(BOW_CENTER_X-Fl::event_x())));
					stretched_bow->show();
				}
				return 1;
			}
			if(e==FL_RELEASE){
				idle_bow->show();
				stretched_bow->hide();
				arrows.push_back(new Arrow(new Vector(BOW_CENTER_X+ARROW_LENGTH*cos(stretched_bow->getAngle())/2,BOW_CENTER_Y-ARROW_LENGTH*sin(stretched_bow->getAngle())/2),new Vector(ARROW_SPEED*cos(stretched_bow->getAngle()),ARROW_SPEED*sin(-1*stretched_bow->getAngle()))));
				return 1;
			}
			return 0;
		}
};
int main(int argc, char* argv[]){
	srand(time(0));
	Fl_Window MyWindow(WINDOW_X,WINDOW_Y,"Balloon Shooter");
	MyWindow.color(BACKGROUND);
	GameEngine game;
	MyWindow.show();
	return(Fl::run());
}
