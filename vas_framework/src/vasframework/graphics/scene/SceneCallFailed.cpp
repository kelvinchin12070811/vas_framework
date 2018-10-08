#include <sstream>
#include "SceneCallFailed.hpp"

namespace vas
{
	SceneCallFailed::SceneCallFailed()
	{
	}

	SceneCallFailed::SceneCallFailed(const std::string& sceneName):
		sceneName(sceneName)
	{
	}

	SceneCallFailed::~SceneCallFailed()
	{
	}

	const char * SceneCallFailed::what() const
	{
		if (sceneName.empty())
		{
			return "Unable to call targeted scene from instance, make sure you have enough memory and it is a child of vas::Scene.";
		}
		std::stringstream ss;
		ss << "Scene Manager is unable to call the scene \"" << sceneName << "\". May be it is not yet registered or is not "
			<< "a child of vas::Scene. Make sure you have enough of memory.";

		return ss.str().c_str();
	}
}