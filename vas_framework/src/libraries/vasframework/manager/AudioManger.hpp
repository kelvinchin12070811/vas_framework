#pragma once
#include "../VASConfig.hpp"

#ifdef VAS_USE_MIXER
#include <array>
#include <thread>
#include <string>
#include <chrono>
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
		//enum class FadingState : uint8_t { none, bgm2me, me2bgm };
		static AudioManger& getInstance();

		void playBGM(const std::string& file, const std::chrono::milliseconds& fadeInTime = std::chrono::milliseconds(0), int loop = -1);
		void playBGS(const std::string& file, const std::chrono::milliseconds& fadeInTime = std::chrono::milliseconds(0), int loop = 1);
		void playME(const std::string& file, const std::chrono::milliseconds& fadeInTime = std::chrono::milliseconds(0), int loop = 1);
		void playSE(const std::string& file, const std::chrono::milliseconds& fadeInTime = std::chrono::milliseconds(0), int loop = 1);

		void stopBGM(std::chrono::milliseconds& fadeOutTime = std::chrono::milliseconds(0));
		void stopBGS(std::chrono::milliseconds& fadeOutTime = std::chrono::milliseconds(0));
		void stopME(std::chrono::milliseconds& fadeOutTime = std::chrono::milliseconds(0));
		void stopSE(std::chrono::milliseconds& fadeOutTime = std::chrono::milliseconds(0));

		void pauseBGM(std::chrono::milliseconds& fadeOutTime = std::chrono::milliseconds(0));

		void resumeBGM(std::chrono::milliseconds& fadeInTime = std::chrono::milliseconds(0));

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

		/*std::array<float, 1>& getLastVolume();
		std::array<float, 4>& getVolume();*/
	private:
		AudioManger();
		~AudioManger();

		std::array<std::string, 4> lastFileName;
		std::array<float, 4> volume{ 128.0f, 128.0f, 128.0f, 128.0f };
		std::array<float, 1> lastVolume{ 0 };

		sdl::mixer::Music bgm;
		sdl::mixer::Chunk bgs{ 0 };
		sdl::mixer::Chunk me{ 1 };
		sdl::mixer::Chunk se{ 2 };

		//std::thread fadeWorker;
	};
}
#endif // VAS_USE_MIXER
