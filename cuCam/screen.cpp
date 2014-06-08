#include <stdio.h>

#include "screen.hpp"

Screen::Screen(int width, int height){
	this->width = width;
	this->height = height;
}

Screen::~Screen(){
	
	SDL_DestroyWindow(this->window);
	SDL_Quit();
}

int Screen::init(){
	
	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		printf("SDL Initialization falied %s", SDL_GetError());
		return -1;
	}else{

		if((this->window = SDL_CreateWindow("CuCam",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,this->width, this->height, SDL_WINDOW_SHOWN)) == NULL){
			printf("SDL_CreateWindow Error : %s", SDL_GetError());
			return -2;
		}else{
			this->mainSurf = SDL_GetWindowSurface(this->window);
		}
	}

	this->cam = cvCaptureFromCAM(0);
	if(!this->cam){
		printf("cvCaptureFromCam error");
		return -3;
	}

	this->manType = 0;
	
	return 0;
}

int Screen::run(){
	bool quit = false;
	SDL_Event e;

	IplImage *camImg = NULL;
	SDL_Surface *camSurf = NULL;

	while(!quit){
		
		while(SDL_PollEvent(&e) !=0){
			
			if(e.type == SDL_MOUSEBUTTONDOWN){
				if(e.button.button == SDL_BUTTON_LEFT){
					
					this->manType = (this->manType + 1)%2;
				}
				/*else{
					this->manType = (this->manType - 1)%2;
				}*/
			}
			else if(e.type == SDL_KEYDOWN){
				switch (e.key.keysym.sym)
				{
				case SDLK_SPACE:
					printf("Saving image");
					SDL_SaveBMP(camSurf, "image.bmp");
				default:
					break;
				}
			}
			else if(e.type == SDL_QUIT){
				quit = true;
			}
		}

		camImg = cvQueryFrame(this->cam);

		camSurf = SDL_CreateRGBSurfaceFrom((void *)camImg->imageData,camImg->width,
					camImg->height,
					camImg->depth*camImg->nChannels,
					camImg->widthStep,
					0xff0000, 0x00ff00, 0x0000ff, 0);

		if(camSurf == NULL){
			printf("Unable to convert Iplimage to SDL_Surface");
			return -1;
		}

		if(this->manType != 0){
			camSurf = manSurf(camSurf, this->manType);
		}
		SDL_BlitSurface(camSurf,NULL,this->mainSurf, NULL);

		SDL_UpdateWindowSurface(window);
	}

	return 0;
}