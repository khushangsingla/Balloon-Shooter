#ifndef GAME_ENGINE
#include "gameEngine.h"
#endif

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

int main(int argc, char* argv[]){
	srand(time(0));
	Fl_Window MyWindow(WINDOW_X,WINDOW_Y,"Balloon Shooter");
	MyWindow.color(BACKGROUND);
	GameEngine game;
	MyWindow.show();
	return(Fl::run());
}
