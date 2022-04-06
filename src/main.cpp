#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdio>
#include <iostream>

int main(int argc, char *argv[]){

	// if there is a problem, it says that
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
		std::cout << "Error: " << SDL_GetError();
	}

	SDL_Window* window = SDL_CreateWindow("AABB Collision Detection", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1080, 720, 0);

	Uint64 render_flags = SDL_RENDERER_ACCELERATED;

	SDL_Renderer* render = SDL_CreateRenderer(window, -1, render_flags);

	SDL_Surface* dog1;
	SDL_Surface* dog2;

	dog1 = IMG_Load("/Users/noahwillis/projects/AABB-Collisin-Detection/corgi-banana.jpg");
	dog2 = IMG_Load("/Users/noahwillis/projects/AABB-Collisin-Detection/dog2.jpg");

	SDL_Texture* texture1 = SDL_CreateTextureFromSurface(render, dog1);
	SDL_Texture* texture2 = SDL_CreateTextureFromSurface(render, dog2);

	SDL_FreeSurface(dog1);
	SDL_FreeSurface(dog2);
	
	SDL_Rect pos1;
	SDL_Rect pos2;

	SDL_QueryTexture(texture1, NULL, NULL, &pos1.w, &pos1.h);
	SDL_QueryTexture(texture2, NULL, NULL, &pos2.w, &pos2.h);

	pos1.w /= 4;
    pos1.h /= 4;
	pos2.w /= 4;
    pos2.h /= 4;

	pos1.x = (750 - pos1.w) / 2;
	pos2.x = (1250 - pos2.w) / 2;

	pos1.y = (1000 - pos1.h) / 2;
	pos2.y = (1000 - pos2.h) / 2;

	bool close = false;

	int speed = 500;

	while(!close){
		SDL_Event e;

		while(SDL_PollEvent(&e)){
			switch (e.type) {

			case SDL_QUIT:
				close = true;
				break;

			case SDL_KEYDOWN:
				// keyboard API for key pressed
				switch (e.key.keysym.scancode) {
				case SDL_SCANCODE_W:
					pos1.y -= speed / 30;
					break;
				case SDL_SCANCODE_UP:
					pos2.y -= speed / 30;
					break;
				case SDL_SCANCODE_A:
					pos1.x -= speed / 30;
					break;
				case SDL_SCANCODE_LEFT:
					pos2.x -= speed / 30;
					break;
				case SDL_SCANCODE_S:
					pos1.y += speed / 30;
					break;
				case SDL_SCANCODE_DOWN:
					pos2.y += speed / 30;
					break;
				case SDL_SCANCODE_D:
					pos1.x += speed / 30;
					break;
				case SDL_SCANCODE_RIGHT:
					pos2.x += speed / 30;
					break;
				default:
					break;
				}
				if(pos1.x < pos2.x + pos2.w &&
				pos1.x + pos1.w > pos2.x &&
				pos1.y < pos2.y + pos2.h &&
				pos1.y + pos1.h > pos2.y){
					SDL_SetTextureColorMod(texture1, 255, 0, 0);
					SDL_SetTextureColorMod(texture2, 255, 0, 0);
				}else{
					SDL_SetTextureColorMod(texture1, 255, 255, 255);
					SDL_SetTextureColorMod(texture2, 255, 255, 255);
				}
			}
		}
		SDL_RenderClear(render);
        SDL_RenderCopy(render, texture1, NULL, &pos1);
		SDL_RenderCopy(render, texture2, NULL, &pos2);
 
        SDL_RenderPresent(render);
 
        SDL_Delay(1000 / 60);
	}
	SDL_DestroyTexture(texture1);
	SDL_DestroyTexture(texture2);

	SDL_DestroyRenderer(render);

	SDL_DestroyWindow(window);
	
	SDL_Quit();

	return 0;
}