#include "TiledMapTest.hpp"
#include <boost/lexical_cast.hpp>

#include "../libraries/VASFramework/util/CommonTools.hpp"
#include "../libraries/VASFramework/util/TextTools.hpp"
#include "../libraries/VASFramework/manager/AudioManager.hpp"
#include "../libraries/VASFramework/base/Base.hpp"
#include "../libraries/VASFramework/manager/InputManager.hpp"
#include "../libraries/VASFramework/base/BasicErrorHandler.hpp"

using namespace vas::operator_plugins;

namespace scene
{
	TiledMapTest::TiledMapTest()
	{
		CallRenderAssistance;
		vas::CommonToolsAPI().messenger(L"已加载场景"s + VAS_TEXTTOOLS_GETVARNAME(scene::TiledMapTest));
		map = std::make_shared<vas::TMXPraser>(L"assets/maps/animated map.tmx"s);

		size_t layerCount = map->getMapData().size() - 1;
		auto colisionDataRaw = map->getMapData().back().get();

		SDL_Rect test = vas::SDLFunctionBridge::newSDLRect(0, 0, 168, 356);
		test += vas::SDLFunctionBridge::newSDLRect(15, 15);

		for (const auto& itr : colisionDataRaw)
			colisionData.push_back(itr != 0 ? true : false);

		colisionData.data();

		for (size_t index = 0; index < layerCount; index++)
			RenderAssistance->insert(L"tile layer "s + boost::lexical_cast<std::wstring>(index), std::make_shared<vas::MapRenderer>(map, index));

		vas::CommonToolsAPI().messenger(L"tileset count: "s + boost::lexical_cast<std::wstring>(map->getTilesets().size()));
		vas::CommonToolsAPI().messenger(L"size of vas::Boolean: " + boost::lexical_cast<std::wstring>(sizeof(vas::Boolean)));

		int facing = vas::defExcep<int>([&]()->int
		{
			return map->getObjectgroups().at(L"entitiess"s)[L"player"s].customProperties[L"facing"s].get<int>(0);
		});

		std::wstring startupBGM = vas::defExcep<std::wstring>([&]()->std::wstring
		{
			return map->getMapProperties()[L"startup bgm"s].get<std::wstring>();
		});

		if (!startupBGM.empty())
		{
			startupBGM = L"assets/"s + startupBGM.substr(startupBGM.rfind(L"../") + 3);
			vas::AudioManagerAPI().playBgm(startupBGM, map->getMapProperties()[L"fadein duration"].get<float>());
		}
		vas::CameraAPI().setPosition(map->getObjectgroups().at(L"entities"s)[L"player"s].position);
	}

	TiledMapTest::~TiledMapTest()
	{
	}

	void TiledMapTest::tick()
	{
		float moveSpeed = 1;
		if (vas::InputManagerAPI().keyTriggeredLive(SDL_SCANCODE_LSHIFT) && vas::InputManagerAPI().keyTriggeredLive(SDL_SCANCODE_LCTRL))
			moveSpeed = 20;
		else if (vas::InputManagerAPI().keyTriggeredLive(SDL_SCANCODE_LSHIFT))
			moveSpeed = 5;
		else if (vas::InputManagerAPI().keyTriggeredLive(SDL_SCANCODE_LCTRL))
			moveSpeed = 10;

		if (vas::InputManagerAPI().keyTriggeredLive(SDL_SCANCODE_UP))
			vas::CameraAPI().move(vas::Vector2(0, -moveSpeed));
		else if (vas::InputManagerAPI().keyTriggeredLive(SDL_SCANCODE_DOWN))
			vas::CameraAPI().move(vas::Vector2(0, moveSpeed));
		if (vas::InputManagerAPI().keyTriggeredLive(SDL_SCANCODE_LEFT))
			vas::CameraAPI().move(vas::Vector2(-moveSpeed, 0));
		else if (vas::InputManagerAPI().keyTriggeredLive(SDL_SCANCODE_RIGHT))
			vas::CameraAPI().move(vas::Vector2(moveSpeed, 0));
		map->tick();

		auto& camera = vas::CameraAPI();
		auto& cameraPos = camera.getPosition();
		if (camera.getXOffset() < 0)
			camera.setPosition(vas::Vector2(0 + vas::BaseAPI().getRenderLogicSize().x / 2, cameraPos.y));
		if (camera.getYOffset() < 0)
			camera.setPosition(vas::Vector2(cameraPos.x, 0 + vas::BaseAPI().getRenderLogicSize().y / 2));

		SceneBase::tick();
	}

	void TiledMapTest::draw()
	{
		SceneBase::draw();
	}

	void TiledMapTest::eventSlot(SDL_Event & eventBus)
	{
		switch (eventBus.type)
		{
			case SDL_EventType::SDL_KEYDOWN:
				if (vas::InputManagerAPI().keyTriggered(SDL_SCANCODE_ESCAPE))
				{
					vas::BaseAPI().postEvent(SDL_EventType::SDL_QUIT);
					vas::BaseAPI().ignoreQuitEvent();
				}
				break;
		}
	}
}