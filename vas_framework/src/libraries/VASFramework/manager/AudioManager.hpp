#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include <memory>
#include <array>
#include "../util/TextTools.hpp"
#include "../util/SDLFunctionBridge.hpp"

namespace vas
{
	class AudioManager
	{
	public:
		static AudioManager& getInstance();
		static const float maxVolume;
		enum class Channel : int { all = -1, bgm = 0, bgs = 1, me = 2, se = 3 };

		void playBgm(const std::wstring& path, float fadeInDuration = 0, int times = -1);
		void playBgs(const std::string& path, float fadeInDuration = 0);
		void playBgs(const std::wstring& path, float fadeInDuration = 0);
		void playMe(const std::string& path, int times = 1, float fadeInDuration = 0);
		void playMe(const std::wstring& path, int times = 1, float fadeInDuration = 0);
		void playSe(const std::wstring& path, int times = 1, float fadeInDuration = 0);

		void stopBgm(float fadeOutDuration = 0);
		void stopBgs(float fadeOutDuration = 0);
		void stopMe(float fadeOutDuration = 0);
		void stopSe(float fadeOutDuration = 0);
		void stopAll();

		void cleanAll();

		float & getVolume(Channel channel);
		bool isChannelPlaying(Channel channel);
		void tick();
	private:
		AudioManager();
		~AudioManager();
		void clampVolume();

		std::shared_ptr<Mix_Music> bgm = nullptr;
		std::shared_ptr<Mix_Chunk> bgs = nullptr;
		std::shared_ptr<Mix_Chunk> se = nullptr;
		std::shared_ptr<Mix_Chunk> me = nullptr;
		std::array<float, 4> masterVolume = { 128, 128, 128, 128 };
		std::array<float, 2> alternatedVolume = { 128, 128 };
		float crossFadeDuration = 0;
	};
	inline AudioManager& AudioManagerAPI() { return AudioManager::getInstance(); };
}
