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

struct application {
  string message;
  int width = 800;
  int height = 800;
  int fontSize = 30;
};

struct position {
  int x;
  int y;
};

const int ERROR = -1;

position getPosition();

void renderLoop(graphics sdl);

graphics initSDL(application app);

void quitSDL(graphics sdl);

string getScratchOutput(string fileName);

application processArguments(int len, char *args[], application app);
