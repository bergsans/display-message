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

struct config {
  string message;
  int width = 800;
  int height = 800;
  string fontPath = "/home/bergsans/.local/share/fonts/iosevka-regular.ttf";
  int fontSize = 30;
};

struct position {
  int x;
  int y;
};

const int ERROR = -1;

position getPosition();

void renderLoop(graphics sdl);

graphics initSDL(config app);

void quitSDL(graphics sdl);

string getScratchOutput(string fileName);

config processArguments(int len, char *args[]);
