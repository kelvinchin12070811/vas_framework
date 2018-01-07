#pragma once
#include "IObjectFactory.hpp"

namespace sreflex
{
	template <typename IObjectType>
	class SREFLEX_DLLEXPORT IObjectAutoRegister
	{
	public:
		IObjectAutoRegister(const std::string& name)
		{
			//IObjectFactory::getMap()->insert(std::make_pair(name, &sreflex::createObjectBase<IObjectType>));
			sreflex::__registerInstance(name, &sreflex::createObjectBase<IObjectType>);
		}
	};
}