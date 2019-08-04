#ifndef GAME_ENGINE_RENDERER_FACTORY_H
#define GAME_ENGINE_RENDERER_FACTORY_H

#include <memory>

namespace GameEngine {


	namespace Rendering {

		class Renderer;

		class RendererFactory
		{
			friend class Application;

			static std::shared_ptr<Renderer> CreateRenderer();
		};
	}
}
#endif
