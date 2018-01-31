#include "SceneBase.hpp"

namespace vas
{
	SceneBase::SceneBase()
	{
	}

	SceneBase::~SceneBase()
	{
	}

	void SceneBase::Signal_beforeTerminate()
	{
		return;
	}

	void SceneBase::Signal_afterTerminate()
	{
		return;
	}

	void SceneBase::Signal_beforeSceneCall()
	{
		return;
	}

	void SceneBase::Signal_afterSceneCall()
	{
		return;
	}
}