//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#pragma once
#include <set>
#include "ResourceMetatype.hpp"

namespace vas
{
	/** @addtogroup util
		  @{
	*/
	/** @brief Automatic resources management utility with RAII.
		  
		  The automatic resources management utility which will automatically release resource when out of scope.
	*/
	class ResourceLoader
	{ /** @} */
	public:
		/** Construct new instance
			  @param freeResources Free the resources when out of scope.
		*/
		ResourceLoader(bool freeResources = true);
		ResourceLoader(const ResourceLoader&) = delete;
		ResourceLoader(ResourceLoader&&) = delete;
		~ResourceLoader();

		ResourceLoader& operator=(const ResourceLoader&) = delete;
		ResourceLoader& operator=(ResourceLoader&&) = delete;

		void unload(const std::string& resourceId = "");

		/** Load a single resource.
			  @param meta Meta data of resource.
		*/
		void load(std::unique_ptr<resource_type::ResourceMetatype> meta);
		/** Load multiple resources with initializer list.
			  @param meta List of meta data of resources.
		*/
		void load(std::initializer_list<std::unique_ptr<resource_type::ResourceMetatype>> meta);

		void setFreeResources(bool value);
		bool isFreeResources() const;
	private:
		std::set<std::unique_ptr<resource_type::ResourceMetatype>> resourcesList;
		/** [Read & Write] Determine if unload all resource during destructing the object.

			 - __mutators__
				-# void setFreeResources(bool value)
			 - __accessors__
				-# bool isFreeResources() const
		*/
		bool freeResources;
	};
}