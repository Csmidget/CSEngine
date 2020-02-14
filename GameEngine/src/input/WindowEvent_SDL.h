#ifndef GAME_ENGINE_WINDOW_EVENT_SDL_H
#define GAME_ENGINE_WINDOW_EVENT_SDL_H

#include "WindowEvent.h"

namespace GameEngine
{
	//To be expanded/reworked?
	struct WindowEvent_SDL : public WindowEvent
	{
		WindowEvent_SDL(const SDL_Event& _event);
	};
}

#endif