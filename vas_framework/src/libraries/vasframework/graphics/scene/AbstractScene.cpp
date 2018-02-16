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
		this->__renderAssistance->tick();
	}

	void AbstractScene::draw()
	{
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
}