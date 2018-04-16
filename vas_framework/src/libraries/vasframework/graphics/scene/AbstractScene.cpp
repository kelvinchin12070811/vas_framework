#include "AbstractScene.hpp"

namespace vas
{
	AbstractScene::AbstractScene()
	{
	}

	AbstractScene::~AbstractScene()
	{
	}

	void AbstractScene::tick()
	{
		if (IsRenderAssistanceReady)
			this->__renderAssistance->tick();
	}

	void AbstractScene::draw()
	{
		if (IsRenderAssistanceReady)
			this->__renderAssistance->draw();
	}

	void AbstractScene::Signal_beforeTerminate()
	{
		return;
	}

	void AbstractScene::Signal_afterTerminate()
	{
		return;
	}

	void AbstractScene::Signal_beforeSceneCall()
	{
		return;
	}

	void AbstractScene::Signal_afterSceneCall()
	{
		return;
	}

	bool AbstractScene::__isRenderAssistanceEnabled()
	{
		return __enableRenderAssistance;
	}
}