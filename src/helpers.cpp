#include "helpers.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <fstream>
#include <sstream>

SDL_Color Blue = {0, 255, 255};

position getPosition() {
  SDL_DisplayMode screen;
  SDL_GetCurrentDisplayMode(0, &screen);
  position pos;
  pos.x = (screen.w / 2) + 400;
  pos.y = (screen.h / 2) + 400;
  return pos;
}

graphics initSDL(application app) {
  if (SDL_Init(SDL_INIT_VIDEO) == ERROR || TTF_Init() == ERROR) {
    cout << "Initialization failed" << endl;
    exit(1);
  }
  graphics sdl;
  position pos = getPosition();
  sdl.window = SDL_CreateWindow("output", pos.x, pos.y, 800, 800, 0);
  sdl.renderer = SDL_CreateRenderer(sdl.window, -1, SDL_RENDERER_ACCELERATED);
  sdl.font = TTF_OpenFont(
      "/home/bergsans/.local/share/fonts/iosevka-regular.ttf", app.fontSize);
  if (sdl.font == NULL) {
    cout << "Initialization of font failed" << endl;
    exit(1);
  }
  sdl.surface =
      TTF_RenderText_Blended_Wrapped(sdl.font, app.message.c_str(), Blue, 770);
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

void quitSDL(graphics sdl) {
  SDL_FreeSurface(sdl.surface);
  SDL_DestroyTexture(sdl.message);
  SDL_DestroyRenderer(sdl.renderer);
  SDL_DestroyWindow(sdl.window);
  SDL_Quit();
}

application processArguments(int len, char *args[], application app) {
  for (int i = 1; i < len; i++) {
    if (args[i] == string("-message")) {
      app.message = i++ < len ? args[i] : "";
    } else if (args[i] == string("-width")) {
      app.width = i++ < len ? atoi(args[i]) : app.width;
    } else if (args[i] == string("-height")) {
      app.height = i++ < len ? atoi(args[i]) : app.height;
    } else if (args[i] == string("-fontsize")) {
      app.fontSize = i++ < len ? atoi(args[i]) : app.fontSize;
      cout << app.fontSize;
    } else if (args[i] == string("--help")) {
      cout << "Display Message v. 0.1" << endl;
      cout << "\n"
           << "flags:" << endl;
      cout << "-message \"{text...}\"" << endl;
      cout << "-width {int}" << endl;
      cout << "-height {int}" << endl;
      cout << "-fontsize {int}" << endl;
      cout << "\n"
           << "./build/msg -message \"Hello, world!\" -width 500 -heigt 500 "
              "-fontsize 15"
           << endl;
      exit(0);
    } else {
      std::cerr << "invalid argument";
      exit(1);
    }
  }
  return app;
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
