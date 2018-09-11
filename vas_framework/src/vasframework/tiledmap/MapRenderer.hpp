#pragma once
#include <vector>
#include "maplayers/TileLayer.hpp"
#include "../graphics/sprites/SpriteSheet.hpp"
#include "container/TilesetsBundle.hpp"

namespace vas
{
	class VAS_DECLSPEC MapRenderer : public DrawAble
	{
	public:
		MapRenderer(TileLayer* layer, const sdl::Point& mapSize, const sdl::Point& tileSize, const TilesetsBundle& bundle);
		~MapRenderer();

		void tick() override;
		void draw(sdl::Renderer* renderer = nullptr, Camera* camera = nullptr) override;

	public: //Setters
		void setStaticOnCamera(bool value);
		
	public: //Getters
		bool isStaticOnCamera();

	private:
		TileLayer* layer;
		TilesetsBundle* bundle;
		sdl::Point mapSize;
		sdl::Point tileSize;
		bool staticOnCamera = false;
	};
}