#include "CSEngine.h"
#include "Game/Program.h"

#define DEBUGMODE "Debug"



int main(int argc, char *argv[]) {

  if (CSEngine::Application::Init(argc, argv)) {

    Program::Init();

    CSEngine::Application::Run();

  }
  else {
    std::cout << "Unable to initialize engine" << std::endl;
  }

  return 0;

}//Main
