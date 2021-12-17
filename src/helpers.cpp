#include "helpers.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <fstream>
#include <sstream>

SDL_Color Blue = {0, 255, 255};

const int ERROR = -1;

void quitSDL(graphics sdl) {
  SDL_FreeSurface(sdl.surface);
  SDL_DestroyTexture(sdl.message);
  SDL_DestroyRenderer(sdl.renderer);
  SDL_DestroyWindow(sdl.window);
  SDL_Quit();
}

position getPosition() {
  SDL_DisplayMode screen;
  SDL_GetCurrentDisplayMode(0, &screen);
  position pos;
  pos.x = (screen.w / 2) + 400;
  pos.y = (screen.h / 2) + 400;
  return pos;
}

graphics initSDL(const char *fileContent) {
  if (SDL_Init(SDL_INIT_VIDEO) == ERROR || TTF_Init() == ERROR) {
    cout << "Initialization failed" << endl;
    exit(1);
  }
  graphics sdl;
  position pos = getPosition();
  sdl.window = SDL_CreateWindow("output", pos.x, pos.y, 800, 800, 0);
  sdl.renderer = SDL_CreateRenderer(sdl.window, -1, SDL_RENDERER_ACCELERATED);
  sdl.font =
      TTF_OpenFont("/home/bergsans/.local/share/fonts/iosevka-regular.ttf", 30);
  if (sdl.font == NULL) {
    cout << "Initialization of font failed" << endl;
    exit(1);
  }
  sdl.surface =
      TTF_RenderText_Blended_Wrapped(sdl.font, fileContent, Blue, 770);
  sdl.message = SDL_CreateTextureFromSurface(sdl.renderer, sdl.surface);
  int w = 0;
  int h = 0;
  SDL_QueryTexture(sdl.message, NULL, NULL, &w, &h);
  sdl.rect = {20, 30, w, h};
  sdl.isRenderLoop = SDL_FALSE;
  return sdl;
}

void renderLoop(graphics sdl) {
  while (!sdl.isRenderLoop) {
    SDL_PollEvent(&sdl.event);
    if (sdl.event.type == SDL_KEYDOWN &&
        sdl.event.key.keysym.sym == SDLK_ESCAPE) {
      sdl.isRenderLoop = SDL_TRUE;
    }
    SDL_RenderClear(sdl.renderer);
    SDL_RenderCopy(sdl.renderer, sdl.message, NULL, &sdl.rect);
    SDL_RenderPresent(sdl.renderer);
  }
}

string getScratchOutput(string fileName) {
  ifstream f(fileName);
  string content;
  if (f) {
    ostringstream ss;
    ss << f.rdbuf();
    content = ss.str();
  }
  return content;
}
