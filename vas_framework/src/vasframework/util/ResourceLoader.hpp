#pragma once
#include <set>
#include "ResourceMetatype.hpp"

namespace vas
{
	class ResourceLoader
	{
	public:
		ResourceLoader(bool freeResources = true);
		ResourceLoader(const ResourceLoader&) = delete;
		ResourceLoader(ResourceLoader&&) = delete;
		~ResourceLoader();

		ResourceLoader& operator=(const ResourceLoader&) = delete;
		ResourceLoader& operator=(ResourceLoader&&) = delete;

		void unload(const std::string& resourceId = "");

		void load(std::unique_ptr<resource_type::ResourceMetatype> meta);
		void load(std::initializer_list<std::unique_ptr<resource_type::ResourceMetatype>> meta);

		void setFreeResources(bool value);
		bool isFreeResources() const;
	private:
		std::set<std::unique_ptr<resource_type::ResourceMetatype>> resourcesList;
		bool freeResources;
	};
}