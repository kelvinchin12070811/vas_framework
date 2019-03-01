//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#pragma once
#include "../VASConfig.hpp"
//TODO: Fix channel does not referenced if reference a channel
#ifdef VAS_USE_MIXER
#include <array>
#include <map>
#include <thread>
#include <string>
#include <chrono>
#include "../sdlcore/audio/MixCore.hpp"

namespace vas
{
	/** @addtogroup managers
		  @{
	*/
	/** @brief Managing multichannel audio with only one object.

		  AudioManager is a simple audio playback library that build on top of sdl_mixer. AudioManager are able to perform
		  lots of simple and common ways to manage audio playback and audio streaming. For more advance usage,
		  use sdl::mixer::Music and sdl::mixer::channel directly.

		  @note The AudioManager used up sdl_mixer's music channel and channel 0 - 2 of chunk channel.
	*/
	class VAS_DECLSPEC AudioManager
	{ /** @} */
	public:
		/** @brief The default value of AudioManager */
		struct DefValue
		{
			static const float MAX_AUDIO; /**< Highest value of volume in AudioManager, default is SDL_mixer's 128*/
		};
		//enum class FadingState : uint8_t { none, bgm2me, me2bgm };

		/** Get the singletone instance of AudioManager
		*/
		static AudioManager& getInstance();

		/** Add a chunk to cache.
			  @param id Unique id of the chunk, can be file name.
			  @param chunk Chunk need to cache.
		*/
		void cacheChunk(const std::string& id, sdl::mixer::Chunk chunk);
		/** Preload a file to cache.
			  @param fileName File name of a file, also use as unique id of the cache.
		*/
		void cacheChunk(const std::string& fileName);

		/** Add a music to cache.
			  @param id Unique id of the music, can be file name.
			  @param music Music need to cache.
		*/
		void cacheMusic(const std::string& id, sdl::mixer::Music music);
		/** Preload a file to cache.
			  @param fileName File name of a file, also use as unique id of the cache.
		*/
		void cacheMusic(const std::string& fileName);

		/** Remove a chunk from cache.
			  @param id Unique id of the cache.
		*/
		void removeChunkFromCache(const std::string& id);
		/** Remove a music from cache.
			  @param id Unique id of the cache.
		*/
		void removeMusicFromCache(const std::string& id);

		/** Return a chunk in cache.
			  @param id Unique id of a cache.
			  @return sdl::mixer::Chunk corresponded to the id, sdl::nullcomponent if resource not located.
		*/
		sdl::mixer::Chunk getChunkFromCache(const std::string& id);
		/** Return a music in cache.
			  @param id Unique id of a cache.
			  @return sdl::mixer::Music corresponded to the id, sdl::nullcomponent if resource not located.
		*/
		sdl::mixer::Music getMusicFromCache(const std::string& id);

		/** Check if the chunk cache is empty or not. */
		bool isChunkCacheEmpty();
		/** Check if the mucic cache is empty or not. */
		bool isMusicCacheEmpty();

		/** Get the size of the chunk cache. */
		size_t chunkCacheSize();
		/** Get the size of the music cache. */
		size_t musicCacheSize();

		/** Clear all cache in chunk cache. */
		void clearChunkCache();
		/** Clear all cache in music cache. */
		void clearMusicCache();
		/** Clear all cache in both music and chunk cache. */
		void clearAllCache();

		/** Start streaming bgm from file or id. Play from cache instead if resource located in cache.
			  @param file File name of the audio.
			  @param fadeInTime Duration for audio fading in.
			  @param loop Times for the audio stream repeat, if it is less than or equal to 0, the playback will be looping endless.
		*/
		void playBGM(const std::string& file, const std::chrono::milliseconds& fadeInTime = std::chrono::milliseconds(0), int loop = -1);
		/** Start BGS playback from file or id. Play from cache instead if resource located in cache.
			  @param file File name of the audio.
			  @param fadeInTime Duration for audio fading in.
			  @param loop Times for the audio stream repeat, looping endlessly if less than or equal to 0.
		*/
		void playBGS(const std::string& file, const std::chrono::milliseconds& fadeInTime = std::chrono::milliseconds(0), int loop = 1);
		/** Start ME playback from file or id. Play from cache instead if resource located in cache.
			  @param file File name of the audio.
			  @param fadeInTime Duration for audio fading in.
			  @param loop Times for the audio stream repeat, looping endlessly if less than or equal to 0.
		*/
		void playME(const std::string& file, const std::chrono::milliseconds& fadeInTime = std::chrono::milliseconds(0), int loop = 1);
		/** Start SE playback from file or id. Play from cache instead if resource located in cache.
			  @param file File name of the audio.
			  @param fadeInTime Duration for audio fading in.
			  @param loop Times for the audio stream repeat, looping endlessly if less than or equal to 0.
		*/
		void playSE(const std::string& file, const std::chrono::milliseconds& fadeInTime = std::chrono::milliseconds(0), int loop = 1);

		/** Stop BGM playback.
			  @param fadeOutTime Duration for audio fading out.
		*/
		void stopBGM(const std::chrono::milliseconds& fadeOutTime = std::chrono::milliseconds(0));
		/** Stop BGS playback.
			  @param fadeOutTime Duration for audio fading out.
		*/
		void stopBGS(const std::chrono::milliseconds& fadeOutTime = std::chrono::milliseconds(0));
		/** Stop ME playback.
			  @param fadeOutTime Duration for audio fading out.
		*/
		void stopME(const std::chrono::milliseconds& fadeOutTime = std::chrono::milliseconds(0));
		/** Stop SE playback.
			  @param fadeOutTime Duration for audio fading out.
		*/
		void stopSE(const std::chrono::milliseconds& fadeOutTime = std::chrono::milliseconds(0));

		/** Pause the playback of BGM.
			  @param fadeOutTime Duration for audio fading out.
		*/
		void pauseBGM(const std::chrono::milliseconds& fadeOutTime = std::chrono::milliseconds(0));
		/** Resume paused BGM.
			  @param fadeInTime Duration for audio fading in.
		*/
		void resumeBGM(const std::chrono::milliseconds& fadeInTime = std::chrono::milliseconds(0));

		sdl::mixer::Music getBGM();
		sdl::mixer::Chunk getBGS();
		sdl::mixer::Chunk getME();
		sdl::mixer::Chunk getSE();

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
		AudioManager();
		~AudioManager();

		std::array<std::string, 4> lastFileName;
		//std::array<float, 4> volume{ 128.0f, 128.0f, 128.0f, 128.0f };
		/** [Read & Write] Volume of bgm
			  - __mutators__
					-# void setBGMVolume(float volume)
			  - __accessors__
					-# float getBGMVolume()
		*/
		float bgmVolume{ AudioManager::DefValue::MAX_AUDIO };
		/** [Read & Write] Volume of bgs
			  - __mutators__
					-# void setBGSVolume(float volume)
			  - __accessors__
					-# float getBGSVolume()
		*/
		float bgsVolume{ AudioManager::DefValue::MAX_AUDIO };
		/** [Read & Write] Volume of me
			  - __mutators__
					-# void setMEVolume(float volume)
			  - __accessors__
					-# float getMEVolume()
		*/
		float meVolume{ AudioManager::DefValue::MAX_AUDIO };
		/** [Read & Write] Volume of se
			- __mutators__
					-# void setSEVolume(float volume)
			- __accessors__
					-# float getSEVolume()
		*/
		float seVolume{ AudioManager::DefValue::MAX_AUDIO };
		//std::array<float, 1> lastVolume{ 0 };

		/** [Read Only] Current bgm instance
			  - __accessors__
					-# sdl::mixer::Music getBGM()
		*/
		sdl::mixer::Music bgm;
		/** [Read Only] Current bgs instance
			  - __accessors__
					-# sdl::mixer::Music getBGS()
		*/
		sdl::mixer::Chunk bgs{ 0 };
		/** [Read Only] Current me instance
			  - __accessors__
					-# sdl::mixer::Music getME()
		*/
		sdl::mixer::Chunk me{ 1 };
		/** [Read Only] Current se instance
			  - __accessors__
					-# sdl::mixer::Music getSE()
		*/
		sdl::mixer::Chunk se{ 2 };
		std::map<std::string, sdl::mixer::Chunk> chunkCache;
		std::map<std::string, sdl::mixer::Music> musicCache;
		//std::thread fadeWorker;
	};
}
#endif // VAS_USE_MIXER
