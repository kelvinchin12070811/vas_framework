#include "NBTTreeTest.hpp"
#include <vasframework/container/nbt/JsonSerializer.hpp>
#include <vasframework/container/nbt/JsonDeserializer.hpp>
#include <vasframework/util/TextTools.hpp>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <sstream>
namespace scene
{
	const vas::sreflex::ReflectAbleAutoRegistrar<NBTTreeTest> NBTTreeTest::__registrar{};
	NBTTreeTest::NBTTreeTest()
	{
		//serializeTest();
		deserializeTest();
	}

	NBTTreeTest::~NBTTreeTest()
	{
	}

	void NBTTreeTest::tick()
	{
		AbstractFrameCountingScene::tick();
	}

	void NBTTreeTest::draw()
	{
		AbstractFrameCountingScene::draw();
	}

	void NBTTreeTest::serializeTest()
	{
		tag = std::make_unique<vas::NBTCompoundTag>();
		tag->insert("scene_name", std::make_shared<vas::StringTag>(vas::sreflex::getObjectName<NBTTreeTest>()));
		tag->insert("time", std::make_shared<vas::Int64Tag>(87686));

		{
			auto otherTag = std::make_unique<vas::NBTCompoundTag>();
			otherTag->insert("pos", std::make_unique<vas::Int32Tag>(35));

			auto testArray = std::make_unique<vas::ArrayTag<int>>();
			*testArray = std::move(vas::ArrayTag<int>{ 1, 2, 3 });
			otherTag->insert("testArray", std::move(testArray));

			otherTag->insert("pos2", std::make_unique<vas::Vector2Tag>(vas::Vector2(34.5f, 67.8f)));

			tag->insert("otherTag", std::move(otherTag));
		}

		vas::JsonSerializer archiver;
		tag->serialize("root", archiver);
		rapidjson::StringBuffer buff;
		auto& doc = archiver.getDocument();
		rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buff);
		doc.Accept(writer);

		vas::Cout() << buff.GetString() << std::endl;
	}

	void NBTTreeTest::deserializeTest()
	{
		std::unique_ptr<vas::NBTCompoundTag>tag = std::make_unique<vas::NBTCompoundTag>();
		tag->insert("scene_name", std::make_unique<vas::StringTag>());
		tag->insert("time", std::make_unique<vas::Uint64Tag>());
		{
			auto player = std::make_unique<vas::NBTCompoundTag>();
			player->insert("position", std::make_unique<vas::Vector2Tag>());
			player->insert("items", std::make_unique<vas::ArrayTag<std::string>>());
			tag->insert("player", std::move(player));
		}

		std::string json =
			"{\n"
			"    \"root\": {\n"
			"        \"scene_name\": \"scene::test_scene\",\n"
			"        \"time\": 6754,\n"
			"        \"player\": {\n"
			"            \"position\": [\n"
			"                34.67,\n"
			"                145.5\n"
			"            ],\n"
			"            \"items\": [\n"
			"                \"diamond_sword\",\n"
			"                \"diamond\",\n"
			"                \"stone\"\n"
			"            ]\n"
			"        }\n"
			"    }\n"
			"}";
		vas::Cout() << "test json:" << std::endl;
		vas::Cout() << json << std::endl;

		vas::JsonDeserializer unpack{ std::ostringstream(json) };
		tag->serialize("root", unpack);

		vas::JsonSerializer pack;
		tag->serialize("root", pack);

		rapidjson::StringBuffer buff;
		rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buff);
		pack.getDocument().Accept(writer);

		vas::Cout() << std::endl;
		vas::Cout() << "after unpack:" << std::endl;
		vas::Cout() << buff.GetString() << std::endl;
	}
}