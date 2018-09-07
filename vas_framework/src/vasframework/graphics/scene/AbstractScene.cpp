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

	void AbstractScene::beforeTerminate()
	{
		return;
	}

	void AbstractScene::afterTerminate()
	{
		return;
	}

	void AbstractScene::beforeSceneCall()
	{
		return;
	}

	void AbstractScene::afterSceneCall()
	{
		return;
	}

	bool AbstractScene::__isRenderAssistanceEnabled()
	{
		return __enableRenderAssistance;
	}
}