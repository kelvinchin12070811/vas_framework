#include "Scene.hpp"

namespace vas
{
	void Scene::tick()
	{
		if (IsRenderAssistanceReady)
			this->__renderAssistance->tick();
	}

	void Scene::draw()
	{
		if (IsRenderAssistanceReady)
			this->__renderAssistance->draw();
	}

	void Scene::beforeTerminate()
	{
		return;
	}

	void Scene::afterTerminate()
	{
		return;
	}

	void Scene::beforeSceneCall()
	{
		return;
	}

	void Scene::afterSceneCall()
	{
		return;
	}

	bool Scene::__isRenderAssistanceEnabled()
	{
		return __enableRenderAssistance;
	}
}