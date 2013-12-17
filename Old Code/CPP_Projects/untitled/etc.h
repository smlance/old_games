#ifndef ETCH
#define ETCH

void init();
void loop();
void cleanUp();

SDL_Surface *loadImage(std::string);
void applySurface(int, int, SDL_Surface*, SDL_Surface*, SDL_Rect * = NULL);

#endif
