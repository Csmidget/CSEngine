#ifndef GAME_ENGINE_SDL_RENDERER_H
#define GAME_ENGINE_SDL_RENDERER_H

namespace CSEngine {

		class Renderer_SDL : public Renderer{

		private:

			SDL_Window* mainWindow;
			SDL_GLContext mainContext;

			//!Initializes SDL_Window and any other renderer specific functions
			bool Init() override;
			//!Destroys the SDL Window and GL context.
			void Destroy() override;
			//!Replaces the buffer with the buffer drawn this frame.
			void Update() override;
			//!Redraws the GL scene. Calls Draw on all GameObjects
			void Draw(std::vector<std::shared_ptr<GameObject>>& _objects) override;	
		
		public:
			void GetWindowSize(int *w, int *h) const override;
			
			float ScreenWidth() const override { return screenWidth; }
			float ScreenHeight() const override { return screenHeight; }

		};
}
#endif
