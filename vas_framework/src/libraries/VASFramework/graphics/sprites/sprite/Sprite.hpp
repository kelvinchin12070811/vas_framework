#pragma once
#include <string>
#include <memory>
#include <SDL.h>
#include "../../render_item/RenderAbleBase.hpp"
#include "../../move_able/MoveAble.hpp"
#include "../../../math/Colour.hpp"

namespace vas
{
	class VAS_FRAMEWORK_DLLEXPORT Sprite : public RenderAbleBase, public MoveAble
	{
	public:
		Sprite();
		Sprite(const std::wstring& path, const Vector2& position, bool buffer = true);
		~Sprite();
		void tick() override;
		void draw() override;

		void createSprite(const std::wstring& path, const Vector2& position, bool buffer = true);
		void setColour(const Colour& colour);

		std::shared_ptr<SDL_Texture> getTexture();
		const std::shared_ptr<SDL_Texture> getTexture() const;
		const Colour& getColour();

		bool isBuffered() const;
	protected:
		std::wstring key;
		Colour colourOverlay = ColourPresets::white;

		std::shared_ptr<SDL_Texture> texture = nullptr;

		bool _isBuffered = true;
	};
}