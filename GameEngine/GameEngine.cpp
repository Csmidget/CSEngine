#include <Application.h>
#include <Program.h>

#include <iostream>

//#define DEBUGMODE "Debug"

int main(int argc, char *argv[]) {

	if (GameEngine::Application::Init(argc, argv)) {

		Program::Init();

		GameEngine::Application::Run();

	}
	else {
		std::cout << "Unable to initialize engine" << std::endl;
	}



	return 0;

}//Main
