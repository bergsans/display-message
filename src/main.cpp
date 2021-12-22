#include "helpers.h"
#include <string>
#include <unistd.h>

int main(int argc, char *argv[]) {
  bool isTerminal = isatty(fileno(stdin));
  string maybePipeMessage = "";
  if (!isTerminal) {
    for (std::string line; std::getline(std::cin, line);) {
      maybePipeMessage += line + "\n";
    }
  }
  config app = processArguments(argc, argv, maybePipeMessage);
  graphics sdl = initSDL(app);
  renderLoop(sdl);
  quitSDL(sdl);
  return 0;
}
