#include "screen.hpp"

#define SCREEN_WIDTH 640	
#define SCREEN_HEIGHT 480

int main(int argc, char *argv[]){
	
	Screen *mainScreen = new Screen(SCREEN_WIDTH, SCREEN_HEIGHT);

	mainScreen->init();
	mainScreen->run();

	delete(mainScreen);
	return 0;
}

