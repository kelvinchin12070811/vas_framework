#pragma once
#include <boost/signals2.hpp>
#include "../VASConfig.hpp"
#include "../sdlcore/SDLCore.hpp"
#include "../container/Switch.hpp"

namespace vas
{
	class VAS_DECLSPEC Base
	{
	public:
		static Base& getInstance();

		void init();
		void startGameLoop();
		void clean();
	private:
		Base();
		~Base();

		void tick();
		void draw();

		Switch exec{ on };
	};

	inline Base& BaseApi()
	{
		return vas::Base::getInstance();
	}
}