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
	/**
	 * @ingroup managers
	 * @{
	 */
	/**
	 * @brief Managing multichannel audio with only one object.
	 * 
	 * AudioManager is a simple audio playback library that build on top of sdl_mixer. AudioManager are able to perform
	 * lots of simple and common ways to manage audio playback and audio streaming. For more advance usage,
	 * use sdl::mixer::Music and sdl::mixer::channel directly.
	 * 
	 * @note The AudioManager used up sdl_mixer's music channel and channel 0 - 2 of chunk channel.
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

		/**
		 * Get the singletone instance of AudioManager
		 */
		static AudioManager& getInstance();

		/**
		 * Add a chunk to cache.
		 * @param[in] id Unique id of the chunk, can be file name.
		 * @param[in] chunk Chunk need to cache.
		 */
		void cacheChunk(const std::string& id, sdl::mixer::Chunk chunk);
		/**
		 * Preload a file to cache.
		 * @param[in] fileName File name of a file, also use as unique id of the cache.
		 * @throw vas::sdl::SCLCoreException when fail to create chunk.
		 */
		void cacheChunk(const std::string& fileName);

		/**
		 * Add a music to cache.
		 * @param[in] id Unique id of the music, can be file name.
		 * @param[in] music Music need to cache.
		 */
		void cacheMusic(const std::string& id, sdl::mixer::Music music);
		/**
		 * Preload a file to cache.
		 * @param[in] fileName File name of a file, also use as unique id of the cache.
		 * @throw vas::sdl::SDLCoreException when fail to create music.
		 */
		void cacheMusic(const std::string& fileName);

		/**
		 * Remove a chunk from cache.
		 * @param[in] id Unique id of the cache.
		 */
		void removeChunkFromCache(const std::string& id);
		/**
		 * Remove a music from cache.
		 * @param[in] id Unique id of the cache.
		 */
		void removeMusicFromCache(const std::string& id);

		/**
		 * Return a chunk in cache.
		 * @param[in] id Unique id of a cache.
		 * @return sdl::mixer::Chunk corresponded to the id, sdl::nullcomponent if resource not located.
		 */
		sdl::mixer::Chunk getChunkFromCache(const std::string& id);
		/**
		 * Return a music in cache.
		 * @param[in] id Unique id of a cache.
		 * @return sdl::mixer::Music corresponded to the id, sdl::nullcomponent if resource not located.
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

		/**
		 * Start streaming bgm from file or id. Play from cache instead if resource located in cache.
		 * @param[in] file File name of the audio.
		 * @param[in] fadeInTime Duration for audio fading in.
		 * @param[in] loop Times for the audio stream repeat, if it is less than or equal to 0, the playback will be looping endless.
		 * @throw vas::sdl::SDLCoreException if failed to create vas::sdl::Music
		 */
		void playBGM(const std::string& file, const std::chrono::milliseconds& fadeInTime = std::chrono::milliseconds(0), int loop = -1);
		/**
		 * Start BGS playback from file or id. Play from cache instead if resource located in cache.
		 * @param[in] file File name of the audio.
		 * @param[in] fadeInTime Duration for audio fading in.
		 * @param[in] loop Times for the audio stream repeat, looping endlessly if less than or equal to 0.
		 * @throw vas::sdl::SDLCoreException if failed to create vas::sdl::Chunk
		 */
		void playBGS(const std::string& file, const std::chrono::milliseconds& fadeInTime = std::chrono::milliseconds(0), int loop = 1);
		/**
		 * Start ME playback from file or id. Play from cache instead if resource located in cache.
		 * @param[in] file File name of the audio.
		 * @param[in] fadeInTime Duration for audio fading in.
		 * @param[in] loop Times for the audio stream repeat, looping endlessly if less than or equal to 0.
		 * @throw vas::sdl::SDLCoreException if failed to create vas::sdl::Chunk
		 */
		void playME(const std::string& file, const std::chrono::milliseconds& fadeInTime = std::chrono::milliseconds(0), int loop = 1);
		/**
		 * Start SE playback from file or id. Play from cache instead if resource located in cache.
		 * @param[in] file File name of the audio.
		 * @param[in] fadeInTime Duration for audio fading in.
		 * @param[in] loop Times for the audio stream repeat, looping endlessly if less than or equal to 0.
		 * @throw vas::sdl::SDLCoreException if failed to create vas::sdl::Chunk
		 */
		void playSE(const std::string& file, const std::chrono::milliseconds& fadeInTime = std::chrono::milliseconds(0), int loop = 1);

		/**
		 * Stop BGM playback.
		 * @param[in] fadeOutTime Duration for audio fading out.
		 */
		void stopBGM(const std::chrono::milliseconds& fadeOutTime = std::chrono::milliseconds(0));
		/**
		 * Stop BGS playback.
		 * @param[in] fadeOutTime Duration for audio fading out.
		 */
		void stopBGS(const std::chrono::milliseconds& fadeOutTime = std::chrono::milliseconds(0));
		/**
		 * Stop ME playback.
		 * @param[in] fadeOutTime Duration for audio fading out.
		 */
		void stopME(const std::chrono::milliseconds& fadeOutTime = std::chrono::milliseconds(0));
		/**
		 * Stop SE playback.
		 * @param[in] fadeOutTime Duration for audio fading out.
		 */
		void stopSE(const std::chrono::milliseconds& fadeOutTime = std::chrono::milliseconds(0));

		/**
		 * Pause the playback of BGM.
		 * @param[in] fadeOutTime Duration for audio fading out.
		 */
		void pauseBGM(const std::chrono::milliseconds& fadeOutTime = std::chrono::milliseconds(0));
		/**
		 * Resume paused BGM.
		 * @param[in] fadeInTime Duration for audio fading in.
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
		/**
		 * Volume of bgm
		 * ####Mutators
		 * -# void setBGMVolume(float volume)
		 * 
		 * ####Accessors
		 * -# float getBGMVolume()
		 */
		float bgmVolume{ AudioManager::DefValue::MAX_AUDIO };
		/**
		 * Volume of bgs
		 * ####Mutators
		 * -# void setBGSVolume(float volume)
		 * 
		 * ####Accessors
		 * -# float getBGSVolume()
		 */
		float bgsVolume{ AudioManager::DefValue::MAX_AUDIO };
		/**
		 * Volume of me
		 * ####Mutators
		 * -# void setMEVolume(float volume)
		 * 
		 * ####Accessors
		 * -# float getMEVolume()
		 */
		float meVolume{ AudioManager::DefValue::MAX_AUDIO };
		/**
		 * Volume of se
		 * ####Mutators
		 * -# void setSEVolume(float volume)
		 * 
		 * ####Accessors
		 * -# float getSEVolume()
		 */
		float seVolume{ AudioManager::DefValue::MAX_AUDIO };
		//std::array<float, 1> lastVolume{ 0 };

		/**
		 * Current bgm instance
		 * ####Accessors
		 * -# sdl::mixer::Music getBGM()
		 */
		sdl::mixer::Music bgm;
		/**
		 * Current bgs instance
		 * ####Accessors
		 * -# sdl::mixer::Music getBGS()
		 */
		sdl::mixer::Chunk bgs{ 0 };
		/**
		 * Current me instance
		 * ####Accessors
		 * -# sdl::mixer::Music getME()
		 */
		sdl::mixer::Chunk me{ 1 };
		/**
		 * Current se instance
		 * ####Accessors
		 * -# sdl::mixer::Music getSE()
		 */
		sdl::mixer::Chunk se{ 2 };
		std::map<std::string, sdl::mixer::Chunk> chunkCache;
		std::map<std::string, sdl::mixer::Music> musicCache;
		//std::thread fadeWorker;
	};
}
#endif // VAS_USE_MIXER
