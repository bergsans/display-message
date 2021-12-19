#include "helpers.h"
#include <string>

int main(int argc, char *argv[]) {
  config app = processArguments(argc, argv);
  graphics sdl = initSDL(app);
  renderLoop(sdl);
  quitSDL(sdl);
  return 0;
}
