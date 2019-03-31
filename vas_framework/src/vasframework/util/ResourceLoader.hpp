//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#pragma once
#include <vector>
#include "ResourceMetatype.hpp"
#include "../VASConfig.hpp"

namespace vas
{
	/**
	 * @ingroup util
	 * @{
	 */
	/**
	 * @brief Automatic resources management utility with RAII.
	 * 
	 * The automatic resources management utility which will automatically release resource when out of scope.
	 */
	class VAS_DECLSPEC ResourceLoader
	{ /** @} */
	public:
		/**
		 * Construct new instance
		 * @param[in] freeResources Free the resources when out of scope.
		 */
		ResourceLoader(bool freeResources = true);
		ResourceLoader(const ResourceLoader&) = delete;
		ResourceLoader(ResourceLoader&&) = delete;
		~ResourceLoader();

		ResourceLoader& operator=(const ResourceLoader&) = delete;
		ResourceLoader& operator=(ResourceLoader&&) = delete;

		/**
		 * Unload a single resource or all resources
		 * @param[in] resourceId ID of resource to unload, unload all if empty.
		 */
		void unload(const std::string& resourceId = "");

		/**
		 * Load a single resource.
		 * @param[in] meta Meta data of resource.
		 */
		void load(std::unique_ptr<resource_type::ResourceMetatype> meta);
		/**
		 * Load multiple resources with initializer list.
		 * @param[in] meta List of meta data of resources.
		 */
		void load(std::initializer_list<std::unique_ptr<resource_type::ResourceMetatype>> meta);

		void setFreeResources(bool value);
		bool isFreeResources() const;
	private:
		std::vector<std::unique_ptr<resource_type::ResourceMetatype>> resourcesList;
		/**
		 * Determine if unload all resource during destructing the object.
		 * ####Mutators
		 * -# void setFreeResources(bool value)
		 * 
		 * ####Accessors
		 * -# bool isFreeResources() const
		 */
		bool freeResources;
	};
}