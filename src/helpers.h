#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

using namespace std;

struct graphics {
  SDL_Window *window;
  SDL_Renderer *renderer;
  TTF_Font *font;
  SDL_Surface *surface;
  SDL_Event event;
  SDL_Texture *message;
  SDL_Rect rect;
  SDL_bool isRenderLoop;
};

struct position {
  int x;
  int y;
};

void renderLoop(graphics sdl);

graphics initSDL(const char *fileContent);

string getScratchOutput(string fileName);

position getPosition();

void quitSDL(graphics sdl);
