#include "helpers.h"
#include <string>

int main(int argc, char *argv[]) {
  application app;
  if (argc == 1) {
    app.message = getScratchOutput(
        "/home/bergsans/Documents/dev/display-message/scratch-output");
  } else {
    app = processArguments(argc, argv, app);
  }
  graphics sdl = initSDL(app);
  renderLoop(sdl);
  quitSDL(sdl);
  return 0;
}
