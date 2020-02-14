#include "CSEngine_Common.h" 

#include "SDL/SDL.h"

#include "Renderer.h"
#include "Renderer_SDL.h"

namespace GameEngine
{
		std::shared_ptr<Renderer> RendererFactory::CreateRenderer()
		{
			std::shared_ptr<Renderer> renderer{ std::make_shared<Renderer_SDL>() };
			renderer->Init();
			return renderer;
		}
} 