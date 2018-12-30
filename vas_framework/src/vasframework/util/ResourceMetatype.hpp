#pragma once
#include <string>

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
			ResourceMetatype(const std::string& path, const std::string& id = "");
			virtual ~ResourceMetatype() = default;

			const std::string path; /**< Path to the resources. */
			const std::string id; /**< ID of the resources, register this as the identifier of the resources. */

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
			Music(const std::string& path, const std::string& id = "");
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
			Chunk(const std::string& path, const std::string& id = "");
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
			Texture(const std::string& path, const std::string& id = "");
			void load() override;
			void unload() override;
		};
		/** @} */
	}
}