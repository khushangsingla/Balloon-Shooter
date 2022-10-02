#include "gameEngine.h"

GameEngine::GameEngine()://Constructor
	Fl_Widget(0,0,WINDOW_X,WINDOW_Y){
		Score=0;
		idle_bow=new IdleBow();
		stretched_bow=new StretchedBow();
		stretched_bow->hide();
		balloons.push_back(new Balloon(new Vector(500,WINDOW_Y),new Vector(0,-1*BALLOON_SPEED),BALLOON_COLOR));
		start_time=time(NULL);
		Fl::add_timeout(STEP_TIME, Timer_CB, (void*)this);
}
GameEngine::~GameEngine(){//Destructor
	for(int i=0;i<balloons.size();i++){
		delete balloons[i];
	}
	for(int j=0;j<arrows.size();j++){
		delete arrows[j];
	}
	delete idle_bow;
	delete stretched_bow;
}
void GameEngine::draw(){
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
int GameEngine::handle(int e){
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

