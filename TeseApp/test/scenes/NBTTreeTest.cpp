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
		serializeTest();
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
		auto tag = vas::NBTCompoundTag::create({
			{ "scene_name", vas::StringTag::create(vas::sreflex::getObjectName<NBTTreeTest>()) },
			{ "time", vas::Int64Tag::create(87686) },
			{ "otherTag", vas::NBTCompoundTag::create({
				{ "pos", vas::Int32Tag::create(35) },
				{ "testArray", vas::ArrayTag<vas::Int32Tag::TagType>::create({ 1, 2, 3 }) },
				{ "pos2", vas::Vector2Tag::create({ 34.5f, 64.8f }) }
			}) },
			{ "testArray", vas::ObjectListTag::create({
				vas::NBTCompoundTag::create({
					{ "name", vas::StringTag::create("player 1") },
					{ "id", vas::Uint64Tag::create(1) }
				}),
				vas::NBTCompoundTag::create({
					{ "name", vas::StringTag::create("player 2") },
					{ "id", vas::Uint64Tag::create(2) }
				}),
				vas::NBTCompoundTag::create({
					{ "name", vas::StringTag::create("player 3") },
					{ "id", vas::Uint64Tag::create(3) }
				})
			}) }
		});

		vas::JsonSerializer archiver;
		tag->serialize("root", archiver);

		vas::Cout() << archiver.getJSON() << std::endl;
	}

	void NBTTreeTest::deserializeTest()
	{
		auto tag = vas::NBTCompoundTag::create({
			{ "scene_name", vas::StringTag::create() },
			{ "time", vas::Uint64Tag::create() },
			{ "player", vas::NBTCompoundTag::create({
				{ "position", vas::Vector2Tag::create() },
				{ "items", vas::ArrayTag<vas::StringTag::TagType>::create() }
			}) }
		});

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

		std::ostringstream ss(json);
		vas::JsonDeserializer unpack(std::move(ss));
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