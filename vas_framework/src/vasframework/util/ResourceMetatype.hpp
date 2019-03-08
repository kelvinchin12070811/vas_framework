//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#pragma once
#include <string>
#include <functional>

namespace vas
{
	namespace resource_type
	{
		/** @addtogroup util
			  @{
		*/
		/** @brief Metatype of generic resources  loader. */
		class ResourceMetatype
		{
		public:
			/** Create metadata of resource's identifier
				  @param path Path to resource.
				  @param id ID of the resource, path as id if empty.
			*/
			ResourceMetatype(const std::string& path, const std::string& id, std::function<void(ResourceMetatype*)> customLoader);

			virtual ~ResourceMetatype() = default;

			const std::string path; /**< Path to the resources. */
			const std::string id; /**< ID of the resources, register this as the identifier of the resources. */
			const std::function<void(ResourceMetatype*)> customLoader; /**< Custom loader to load the resource. */

			virtual void load() = 0; /**< Load the targeted resource with id. */
			virtual void unload() = 0; /**< Unload the targeted resource with id. */
		};

		/**@brief Metadata of vas::sdl::mixer::Music type of resources. */
		class Music : public ResourceMetatype
		{
		public:
			/** Create metadata of resource's identifier
				  @param path Path to resource.
				  @param id ID of the resource, path as id if empty.
			*/
			Music(const std::string& path, const std::string& id = "", std::function<void(ResourceMetatype*)> customLoader = nullptr);
			void load() override;
			void unload() override;
		};

		/** @brief Metadata of vas::sdl::mixer::Chunk type of resources. */
		class Chunk : public ResourceMetatype
		{
		public:
			/** Create metadata of resource's identifier
				  @param path Path to resource.
				  @param id ID of the resource, path as id if empty.
			*/
			Chunk(const std::string& path, const std::string& id = "", std::function<void(ResourceMetatype*)> customLoader = nullptr);
			void load() override;
			void unload() override;
		};

		/** @brief Metadata of vas::sdl::Texture type of resources. */
		class Texture : public ResourceMetatype
		{
		public:
			/** Create metadata of resource's identifier
				  @param path Path to resource.
				  @param id ID of the resource, path as id if empty.
			*/
			Texture(const std::string& path, const std::string& id = "", std::function<void(ResourceMetatype*)> customLoader = nullptr);
			void load() override;
			void unload() override;
		};
		/** @} */

		/** @brief Metadata of vas::sdl::ttf::Font type of resources. */
		class Fonts : public ResourceMetatype
		{
		public:
			/** Create metadata of resource's identifier
				  @param path Path to ttf font.
				  @param size Size of the font.
				  @param id ID of the font, path as id if empty.
			*/
			Fonts(const std::string& path, uint32_t size, const std::string& id = "",
				std::function<void(ResourceMetatype*)> customLoader = nullptr);
			void load() override;
			void unload() override;
		private:
			uint32_t size{ 0 };
		};
	}
}