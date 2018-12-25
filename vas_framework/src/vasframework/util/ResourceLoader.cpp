#include "ResourceLoader.hpp"
#include "../manager/AudioManger.hpp"
#include "../manager/TextureManager.hpp"

using namespace vas::resource_type;

namespace vas
{
	ResourceLoader::ResourceLoader(bool freeResources):
		freeResources(freeResources)
	{
	}

	ResourceLoader::~ResourceLoader()
	{
		unload();
	}

	void ResourceLoader::unload(const std::string& resourceId)
	{
		if (resourcesList.empty()) return;
		if (!resourceId.empty())
		{
			for (auto& itr : resourcesList)
				itr->unload();
			resourcesList.clear();
		}
		else
		{
			auto itr = std::find_if(resourcesList.begin(), resourcesList.end(), [&](decltype(resourcesList)::const_reference itr)
			{
				return itr->id == resourceId;
			});
			if (itr != resourcesList.end())
			{
				(*itr)->unload();
				resourcesList.erase(itr);
			}
		}
	}

	void ResourceLoader::load(std::unique_ptr<ResourceMetatype> meta)
	{
		meta->load();
		resourcesList.insert(std::move(meta));
	}

	void ResourceLoader::load(std::initializer_list<std::unique_ptr<ResourceMetatype>> meta)
	{
		for (auto& itr : meta)
		{
			itr->load();
			resourcesList.insert(std::move(const_cast<std::unique_ptr<ResourceMetatype>&>(itr)));
		}
	}

	void ResourceLoader::setFreeResources(bool value)
	{
		this->freeResources = value;
	}

	bool ResourceLoader::isFreeResources() const
	{
		return this->freeResources;
	}
}