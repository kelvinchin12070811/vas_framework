#pragma once
#include <memory>
#include <vasframework/container/nbt/NBT.hpp>
#include "AbstractFrameCountingScene.hpp"

namespace scene
{
	class NBTTreeTest : public AbstractFrameCountingScene
	{
	public:
		NBTTreeTest();
		~NBTTreeTest();

		void tick() override;
		void draw() override;
	private:
		void serializeTest();
		void deserializeTest();
	private:
		static const vas::sreflex::ReflectAbleAutoRegistrar<NBTTreeTest> __registrar;
		std::unique_ptr<vas::NBTCompoundTag> tag;
	};
}