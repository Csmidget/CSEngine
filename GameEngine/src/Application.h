#ifndef GAME_ENGINE_APPLICATION_H
#define GAME_ENGINE_APPLICATION_H

namespace GameEngine {

	class Object;
	class GameObject;
	class Input;


	class Renderer;


	//! The central class of the engine. Manages Initialization, Updating and Quitting. Also stores a list of all game objects currently loaded.
	class Application {

	private:
		//!Set to false to turn off program
		static bool run;

		//!Current ticks since program launch
		static unsigned int currentTicks;
		//!Previous record of current ticks
		static unsigned int lastTicks;

		//!Real Delta Time in milliseconds
		static int rdt;
		//!Real Delta Time in Seconds 
		static float rdts;

		static std::shared_ptr<Renderer> renderer;
		static std::shared_ptr<Input> input;

		//!Calls Update on all active game objects
		static void Update();

		//!Refreshes the rdt & rdts variables based on change in time since last call.
		static void RefreshDeltaTime();

		//!Destroys list of GameObject's and closes SDL window
		static void Quit();
	public:
		static std::vector<std::shared_ptr<GameObject>> gameObjects;

		//!Initializes the SDL window, Renderer and Camera
		static bool Init(int argc, char* argv[]);

		//!The central game loop
		static void Run();

		//! Marks an Object for destruction. This can be a GameObject or Component.
		/*! The Object will be removed on the next update iteration.
		  \param _o The Object to be destroyed
		*/
		static void Destroy(std::shared_ptr<Object> _o);

		//! Adds a GameObject to the list of active GameObject's
		static void AddGameObject(std::shared_ptr<GameObject> _go);

		//!Returns the time since last update in milliseconds
		static int Rdt() { return rdt; }

		//!Returns the time since last update in seconds
		static float Rdts() { return rdts; }
		
		static std::weak_ptr<Renderer> Renderer() { return renderer; }

		static std::weak_ptr<Input> Input() { return input; }

		//!Stops the program
		static void Stop() { run = false; }

	};

}//namespace GameEngine

#endif
