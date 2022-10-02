#ifndef GAME_ENGINE
#define GAME_ENGINE

#ifndef BOW_H
#include "bow.h"
#endif

#ifndef BALLOON_H
#include "balloon.h"
#endif

#ifndef ARROW_H
#include "arrow.h"
#endif

#ifndef OBJECT_H
#include "Object.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef VECTOR_H
#include "Vector.h"
#endif

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
		GameEngine();
		~GameEngine();
		void draw();
		virtual int handle(int e);
};

#endif
