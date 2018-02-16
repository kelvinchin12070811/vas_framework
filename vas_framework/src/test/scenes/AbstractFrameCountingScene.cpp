#include <Windows.h>
#include "AbstractFrameCountingScene.hpp"
#include "../../libraries/vasframework/base/Base.hpp"
#include "../../libraries/vasframework/util/TextTools.hpp"

namespace scene
{
	AbstractFrameCountingScene::AbstractFrameCountingScene()
	{
	}

	AbstractFrameCountingScene::~AbstractFrameCountingScene()
	{
	}

	void AbstractFrameCountingScene::tick()
	{
		vas::AbstractScene::tick();
		SetConsoleTitle(vas::TextTools::stows((boost::format("Last fps: %d") % vas::Base::getInstance().getLastFpsCount()).str()).c_str());
	}

	void AbstractFrameCountingScene::draw()
	{
		vas::AbstractScene::draw();
	}
}
