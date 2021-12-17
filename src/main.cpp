#include "helpers.h"

int main(int argc, char *argv[]) {
  string contents = getScratchOutput(
      "/home/bergsans/Documents/dev/display-message/scratch-output");
  graphics sdl = initSDL(contents.c_str());
  renderLoop(sdl);
  quitSDL(sdl);
  return 0;
}
