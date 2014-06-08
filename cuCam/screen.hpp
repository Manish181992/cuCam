#ifndef _SCREEN_H_
	#define _SCREEN_H_

#include <SDL.h>

#include <opencv2\objdetect\objdetect.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

#include "kernels.hpp"

	class Screen{

		private:
			int width;
			int height;
			int manType;

			SDL_Window *window;
			SDL_Surface *mainSurf;

			CvCapture *cam;

		public:
			Screen(int, int);
			~Screen();
			int init();
			int run();
	
	};
#endif