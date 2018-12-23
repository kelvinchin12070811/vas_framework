#pragma once
#include <string>

namespace vas
{
	namespace resource_type
	{
		class ResourceMetatype
		{
		public:
			ResourceMetatype(const std::string& path, const std::string& id = "");
			virtual ~ResourceMetatype() = default;

			const std::string path;
			const std::string id;

			virtual void load() = 0;
			virtual void unload() = 0;
		};

		class Music : public ResourceMetatype
		{
		public:
			Music(const std::string& path, const std::string& id = "");
			void load() override;
			void unload() override;
		};

		class Chunk : public ResourceMetatype
		{
		public:
			Chunk(const std::string& path, const std::string& id = "");
			void load() override;
			void unload() override;
		};

		class Texture : public ResourceMetatype
		{
		public:
			Texture(const std::string& path, const std::string& id = "");
			void load() override;
			void unload() override;
		};
	}
}