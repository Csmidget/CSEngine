#include <SDL/SDL.h>

#include "CSEngine_Common.h"
#include "Input.h"
#include "Input_SDL.h"

namespace CSEngine
{
	//==============================================================================
	std::shared_ptr<Input> CreateInput()
	{
		return std::make_shared<Input_SDL>();
	}
}

