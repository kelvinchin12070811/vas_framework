#include "SceneBase.hpp"

namespace vas
{
	SceneBase::SceneBase()
	{
	}


	SceneBase::~SceneBase()
	{
	}

	void SceneBase::tick()
	{
		if (RenderAssistance != nullptr)
			RenderAssistance->tick();
	}

	void SceneBase::draw()
	{
		if (RenderAssistance != nullptr)
			RenderAssistance->draw();
	}

	void SceneBase::Signal_beforeTerminate()
	{
	}

	void SceneBase::Signal_afterTerminate()
	{
	}

	void SceneBase::Signal_beforeSceneCall()
	{
	}

	void SceneBase::Signal_afterSceneCall()
	{
	}
}