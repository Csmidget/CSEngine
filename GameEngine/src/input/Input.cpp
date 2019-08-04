#include "Input.h"
#include "Input_SDL.h"

namespace GameEngine
{
	//==============================================================================
	std::shared_ptr<Input> CreateInput()
	{
		return std::make_shared<Input_SDL>();
	}
}

