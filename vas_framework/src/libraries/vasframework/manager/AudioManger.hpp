#pragma once
#include <array>
#include <string>
#include <chrono>
#include "../VASConfig.hpp"
#include "../sdlcore/audio/MixCore.hpp"

namespace vas
{
	class VAS_DECLSPEC AudioManger
	{
	public:
		struct DefValue
		{
			static const float MAX_AUDIO;
		};
		enum class FadingState : uint8_t { none, fadeIn, fadeOut };
		static AudioManger& getInstance();

		void playBGM(const std::string& file, const std::chrono::milliseconds& fadeInTime = std::chrono::milliseconds(0), int loop = -1);
		void playBGS(const std::string& file, const std::chrono::milliseconds& fadeInTime = std::chrono::milliseconds(0), int loop = 1);
		void playME(const std::string& file, const std::chrono::milliseconds& fadeInTime = std::chrono::milliseconds(0), int loop = 1);
		void playSE(const std::string& file, const std::chrono::milliseconds& fadeInTime = std::chrono::milliseconds(0), int loop = 1);

		void stopBGM(std::chrono::milliseconds& fadeOutTime = std::chrono::milliseconds(0));
		void stopBGS(std::chrono::milliseconds& fadeOutTime = std::chrono::milliseconds(0));
		void stopME(std::chrono::milliseconds& fadeOutTime = std::chrono::milliseconds(0));
		void stopSE(std::chrono::milliseconds& fadeOutTime = std::chrono::milliseconds(0));

		sdl::mixer::Music& BGM();
		sdl::mixer::Chunk& BGS();
		sdl::mixer::Chunk& ME();
		sdl::mixer::Chunk& SE();

		float getBGMVolume();
		float getBGSVolume();
		float getMEVolume();
		float getSEVolume();

		void setBGMVolume(float value);
		void setBGSVolume(float value);
		void setMEVolume(float value);
		void setSEVolume(float value);

		void clear();
		void tick();
	private:
		AudioManger();
		~AudioManger();

		AudioManger::FadingState fadeState = AudioManger::FadingState::none;
		std::chrono::milliseconds crossFadeDuration;

		std::array<std::string, 4> lastFileName;
		std::array<float, 4> volume{ 128.0f, 128.0f, 128.0f, 128.0f };
		std::array<float, 2> volumeCache{ 128.0f, 128.0f };

		sdl::mixer::Music bgm;
		sdl::mixer::Chunk bgs{ 0 };
		sdl::mixer::Chunk me{ 1 };
		sdl::mixer::Chunk se{ 2 };
	};
}