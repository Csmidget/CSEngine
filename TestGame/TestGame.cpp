//#include "CSEngine/CSEngine.h"
#include "Program.h"
#include "CSEngine/CSEngine.h"

int main(int argc, char** argv)
{
    if (CSEngine::Application::Init(argc, argv)) {

        Program::Init();

        CSEngine::Application::Run();

    }
    else {
        std::cout << "Unable to initialize engine" << std::endl;
    }

    return 0;
}
