
#include "SDL\SDL.h"
#include "WindowEvent_SDL.h"

namespace CSEngine
{
	WindowEvent_SDL::WindowEvent_SDL(const SDL_Event& _event)
	{
		data1 = _event.window.data1;
		data2 = _event.window.data2;

		switch (_event.window.event)
		{
		case SDL_WINDOWEVENT_SHOWN: type = WINDOWEVENT_SHOWN; break;
		case SDL_WINDOWEVENT_HIDDEN: type = WINDOWEVENT_HIDDEN; break;
		case SDL_WINDOWEVENT_EXPOSED: type = WINDOWEVENT_EXPOSED; break;
		case SDL_WINDOWEVENT_MOVED: type = WINDOWEVENT_MOVED; break;
		case SDL_WINDOWEVENT_RESIZED: type = WINDOWEVENT_RESIZED; break;
		case SDL_WINDOWEVENT_SIZE_CHANGED: type = WINDOWEVENT_SIZE_CHANGED; break;
		case SDL_WINDOWEVENT_MINIMIZED: type = WINDOWEVENT_MINIMIZED; break;
		case SDL_WINDOWEVENT_MAXIMIZED: type = WINDOWEVENT_MAXIMIZED; break;
		case SDL_WINDOWEVENT_RESTORED: type = WINDOWEVENT_RESTORED; break;
		case SDL_WINDOWEVENT_ENTER: type = WINDOWEVENT_ENTER; break;
		case SDL_WINDOWEVENT_LEAVE: type = WINDOWEVENT_LEAVE; break;
		case SDL_WINDOWEVENT_FOCUS_GAINED: type = WINDOWEVENT_FOCUS_GAINED; break;
		case SDL_WINDOWEVENT_FOCUS_LOST: type = WINDOWEVENT_FOCUS_LOST; break;
		case SDL_WINDOWEVENT_CLOSE: type = WINDOWEVENT_CLOSE; break;
		case SDL_WINDOWEVENT_TAKE_FOCUS: type = WINDOWEVENT_TAKE_FOCUS; break;
		case SDL_WINDOWEVENT_HIT_TEST: type = WINDOWEVENT_HIT_TEST; break;
		default: type = WINDOWEVENT_NONE;
		}

	}
}