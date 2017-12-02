#include "AudioManager.hpp"
#include "../util/CommonTools.hpp"
#include "../util/TextTools.hpp"
#include "../base/Base.hpp"
#include <boost/algorithm/clamp.hpp>

using namespace std;

namespace vas
{
	const float AudioManager::maxVolume = 128;
	AudioManager & AudioManager::getInstance()
	{
#ifndef SETTINGS_INIT_AUDIO
		throw std::runtime_error(u8"Cannot use Audio Manager scene Audio module not inited");
#endif // SETTINGS_INIT_AUDIO

		static AudioManager instance;
		return instance;
	}

	void AudioManager::playBgm(const std::wstring & path, float fadeInDuration, int times)
	{
		if (Mix_PlayingMusic())
			Mix_HaltMusic();
		bgm = SDLFunctionBridge::newMixMusic(Mix_LoadMUS(str_cast<std::string>(path).c_str()));
		if (bgm == nullptr) throw std::runtime_error(SDL_GetError());
		if (Mix_FadeInMusic(bgm.get(), times, static_cast<int>(fadeInDuration * 1000)) < 0) throw std::runtime_error(SDL_GetError());
	}

	void AudioManager::playBgs(const std::string& path, float fadeInDuration)
	{
		if (Mix_Playing(static_cast<int>(Channel::bgs)))
			Mix_HaltChannel(static_cast<int>(Channel::bgs));
		bgs = SDLFunctionBridge::newMixChunk(Mix_LoadWAV(path.c_str()));
		if (bgs == nullptr) throw std::runtime_error(SDL_GetError());
		if (Mix_FadeInChannel(static_cast<int>(Channel::bgs), bgs.get(), -1, static_cast<int>(fadeInDuration * 1000)) < 0) throw std::runtime_error(SDL_GetError());
	}

	void AudioManager::playBgs(const std::wstring & path, float fadeInDuration)
	{
		std::string temp = str_cast<std::string>(path);
		playBgs(temp, fadeInDuration);
	}

	void AudioManager::playMe(const std::string & path, int times, float fadeInDuration)
	{
		this->crossFadeDuration = fadeInDuration * Base::getInstance().getFPS();
		if (fadeInDuration != 0)
			alternatedVolume[1] = 0;

		if (times <= 0) throw std::logic_error("Play Music Effect for infinite times"s);
		if (Mix_Playing(static_cast<int>(Channel::me)))
			Mix_HaltChannel(static_cast<int>(Channel::me));

		me = SDLFunctionBridge::newMixChunk(Mix_LoadWAV(path.c_str()));
		if (me == nullptr) throw std::runtime_error(SDL_GetError());
		if (Mix_PlayingMusic())
		{
			if (Mix_PlayChannel(static_cast<int>(Channel::me), me.get(), times - 1) < 0)
				throw std::runtime_error(SDL_GetError());
		}
		else
		{
			if (Mix_FadeInChannel(static_cast<int>(Channel::me), me.get(), times - 1, static_cast<int>(fadeInDuration * 1000)) < 0)
				throw std::runtime_error(SDL_GetError());
			crossFadeDuration = 0;
		}
	}

	void AudioManager::playMe(const std::wstring & path, int times, float fadeInDuration)
	{
		std::string temp = str_cast<std::string>(path);
		playMe(temp, times, fadeInDuration);
	}

	void AudioManager::playSe(const std::wstring & path, int times, float fadeInDuration)
	{
		if (times <= 0) throw std::logic_error("Play Sound Effect for infinite times"s);
		if (Mix_Playing(static_cast<int>(Channel::se)))
			Mix_HaltChannel(static_cast<int>(Channel::se));
		se = SDLFunctionBridge::newMixChunk(Mix_LoadWAV(str_cast<std::string>(path).c_str()));
		if (se == nullptr) throw std::runtime_error(SDL_GetError());
		if (Mix_FadeInChannel(static_cast<int>(Channel::se), se.get(), times - 1, static_cast<int>(fadeInDuration * 1000)) < 0) throw std::runtime_error(SDL_GetError());
	}

	void AudioManager::stopBgm(float fadeOutDuration)
	{
		if (Mix_PlayingMusic())
			Mix_FadeOutMusic(static_cast<int>(fadeOutDuration * 1000));
	}

	void AudioManager::stopBgs(float fadeOutDuration)
	{
		if (Mix_Playing(static_cast<int>(Channel::bgs)))
			Mix_FadeOutChannel(static_cast<int>(Channel::bgs), static_cast<int>(fadeOutDuration * 1000));
	}

	void AudioManager::stopMe(float fadeOutDuration)
	{
		if (Mix_Playing(static_cast<int>(Channel::me)))
			Mix_FadeOutChannel(static_cast<int>(Channel::me), static_cast<int>(fadeOutDuration * 1000));
	}

	void AudioManager::stopSe(float fadeOutDuration)
	{
		if (Mix_Playing(static_cast<int>(Channel::se)))
			Mix_FadeOutChannel(static_cast<int>(Channel::se), static_cast<int>(fadeOutDuration * 1000));
	}

	void AudioManager::stopAll()
	{
		stopBgm();
		stopBgs();
		stopMe();
		stopSe();
	}

	void AudioManager::cleanAll()
	{
#ifdef SETTINGS_INIT_AUDIO
		stopAll();
		if (bgm != nullptr) bgm = nullptr;
		if (bgs != nullptr) bgs = nullptr;
		if (se != nullptr) se = nullptr;
		if (me != nullptr) me = nullptr;
		Mix_Quit();
#endif // SETTINGS_INIT_AUDIO
	}

	float & AudioManager::getVolume(Channel channel)
	{
		return masterVolume[static_cast<int>(channel)];
	}

	bool AudioManager::isChannelPlaying(Channel channel)
	{
		if (channel == Channel::bgm)
			return Mix_PlayingMusic() != 0;
		else if (channel == Channel::all)
			return Mix_PlayingMusic() != 0 || Mix_Playing(static_cast<int>(channel)) != 0;
		else
			return Mix_Playing(static_cast<int>(channel)) != 0;
	}

	void AudioManager::tick()
	{
		//process algorithm
		//me-bgm crossfade
		if (Mix_Playing(static_cast<int>(Channel::me)) && Mix_PlayingMusic()) // changing track bgm -> me
		{
			if (crossFadeDuration != 0)
			{
				if (alternatedVolume[1] < masterVolume[static_cast<int>(Channel::me)] || alternatedVolume[0] > 0)
				{
					float bgmDecreaseRate = masterVolume[static_cast<int>(Channel::bgm)] / crossFadeDuration;
					float meIncreaseRate = masterVolume[static_cast<int>(Channel::me)] / crossFadeDuration;

					alternatedVolume[0] -= bgmDecreaseRate;
					alternatedVolume[1] += meIncreaseRate;
					if (alternatedVolume[0] <= 0)
						Mix_PauseMusic();
				}
			}
			else
				Mix_PauseMusic();
		}
		else if (!Mix_Playing(static_cast<int>(Channel::me)) && (Mix_PausedMusic() || alternatedVolume[0] < masterVolume[static_cast<int>(Channel::bgm)])) // changing track me -> bgm
		{
			Mix_ResumeMusic();
			if (crossFadeDuration != 0)
			{
				if (alternatedVolume[0] < masterVolume[static_cast<int>(Channel::bgm)])
				{
					alternatedVolume[0] += masterVolume[static_cast<int>(Channel::bgm)] / crossFadeDuration;
				}
				else
					crossFadeDuration = 0;
			}
		}
		//end

		if (crossFadeDuration == 0)
		{
			alternatedVolume[0] = masterVolume[static_cast<int>(Channel::bgm)];
			alternatedVolume[1] = masterVolume[static_cast<int>(Channel::me)];
		}
		clampVolume();
		Mix_VolumeMusic(static_cast<int>(alternatedVolume[0]));
		Mix_Volume(static_cast<int>(Channel::bgs), static_cast<int>(masterVolume[static_cast<int>(Channel::bgs)]));
		Mix_Volume(static_cast<int>(Channel::me), static_cast<int>(alternatedVolume[1]));
		Mix_Volume(static_cast<int>(Channel::se), static_cast<int>(masterVolume[static_cast<int>(Channel::se)]));
	}

	AudioManager::AudioManager()
	{
	}


	AudioManager::~AudioManager()
	{
		cleanAll();
	}

	void AudioManager::clampVolume()
	{
		for (float& value : masterVolume)
			value = boost::algorithm::clamp(value, 0, maxVolume);

		alternatedVolume[0] = boost::algorithm::clamp(alternatedVolume[0], 0, masterVolume[static_cast<int>(Channel::bgm)]);
		alternatedVolume[1] = boost::algorithm::clamp(alternatedVolume[1], 0, masterVolume[static_cast<int>(Channel::me)]);
	}
}
