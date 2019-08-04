#include "RendererFactory.h"
#include "Renderer.h"
#include "Renderer_SDL.h"

namespace GameEngine
{
	namespace Rendering
	{
		std::shared_ptr<Renderer> RendererFactory::CreateRenderer()
		{
			std::shared_ptr<Renderer> renderer{ std::make_shared<Renderer_SDL>() };
			renderer->Init();
			return renderer;
		}
	}
} 