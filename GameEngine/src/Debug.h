//Acts as an interface between the engine and the debug outputs. This could be files or just the normal iostreams.
//Defaulted to cout and cerr streams.

#ifndef GAME_ENGINE_DEBUG_H
#define GAME_ENGINE_DEBUG_H

#include <string>
#include <iostream>

//TODO: add optional file output streams to allow propper logging of debug info.

namespace GameEngine
{
	class Debug
	{
	public:

		template<class Arg, typename... Args>
		inline static void Log(Arg&& _logStr, Args&&... args)
		{
#if _DEBUG
			std::cout << std::forward<Arg>(_logStr);
			using expander = int[];
			(void)expander {
				0, (void(std::cout << std::forward<Args>(args)), 0)...
			};

			std::cout << std::endl;
#endif
		}//Debug::Log()

		template<class Arg, typename... Args>
		inline static void LogError(Arg&& _logStr, Args&&... args)
		{
#if _DEBUG
			std::cerr << std::forward<Arg>(_logStr);
			using expander = int[];
			(void)expander {
				0, (void(std::cerr << std::forward<Args>(args)), 0)...
			};

			std::cerr << std::endl;
#endif
		}//Debug::LogError()

	};
}
#endif