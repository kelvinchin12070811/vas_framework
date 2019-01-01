//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#include "AudioManger.hpp"

#ifdef VAS_USE_MIXER
#include <boost/algorithm/clamp.hpp>
#include "../util/CommonTools.hpp"
#include "../math/Clock.hpp"
#include "../sdlcore/SDLCoreException.hpp"

using namespace std::chrono_literals;

const float vas::AudioManager::DefValue::MAX_AUDIO{ 128.0f };

namespace vas
{
	AudioManager & AudioManager::getInstance()
	{
		static AudioManager instance;
		return instance;
	}

	void AudioManager::cacheChunk(const std::string & id, sdl::mixer::Chunk chunk)
	{
		chunkCache[id] = std::move(chunk);
	}

	void AudioManager::cacheChunk(const std::string & fileName)
	{
		sdl::mixer::Chunk temp(fileName);
		cacheChunk(fileName, std::move(temp));
	}

	void AudioManager::cacheMusic(const std::string & id, sdl::mixer::Music music)
	{
		musicCache[id] = music;
	}

	void AudioManager::cacheMusic(const std::string & fileName)
	{
		sdl::mixer::Music temp{ fileName };
		cacheMusic(fileName, std::move(temp));
	}

	void AudioManager::removeChunkFromCache(const std::string & id)
	{
		chunkCache.erase(id);
	}

	void AudioManager::removeMusicFromCache(const std::string & id)
	{
		musicCache.erase(id);
	}

	sdl::mixer::Chunk AudioManager::getChunkFromCache(const std::string & id)
	{
		auto chunk = chunkCache.find(id);
		return chunk == chunkCache.end() ? sdl::mixer::Chunk{} : chunk->second;
	}

	sdl::mixer::Music AudioManager::getMusicFromCache(const std::string & id)
	{
		auto music = musicCache.find(id);
		return music == musicCache.end() ? sdl::mixer::Music{} : music->second;
	}

	bool AudioManager::isChunkCacheEmpty()
	{
		return chunkCache.empty();
	}

	bool AudioManager::isMusicCacheEmpty()
	{
		return musicCache.empty();
	}

	size_t AudioManager::chunkCacheSize()
	{
		return chunkCache.size();
	}

	size_t AudioManager::musicCacheSize()
	{
		return musicCache.size();
	}

	void AudioManager::clearChunkCache()
	{
		chunkCache.clear();
	}

	void AudioManager::clearMusicCache()
	{
		musicCache.clear();
	}

	void AudioManager::clearAllCache()
	{
		clearChunkCache();
		clearMusicCache();
	}

	void AudioManager::playBGM(const std::string & file, const std::chrono::milliseconds & fadeInTime, int loop)
	{
		if (bgm.isPlaying()) bgm.stop();

		if (lastFileName[0] != file)
		{
			if (auto& music = getMusicFromCache(file); music != sdl::emptycomponent)
			{
				bgm = music;
			}
			else
			{
				bgm.load(file);
				if (bgm == sdl::emptycomponent) throw sdl::SDLCoreException{};
			}
			lastFileName[0] = file;
		}
		bgm.fadeIn(static_cast<int>(fadeInTime.count()), loop);
	}

	void AudioManager::playBGS(const std::string & file, const std::chrono::milliseconds & fadeInTime, int loop)
	{
		if (bgs.isPlaying()) bgs.stop();
		if (lastFileName[1] != file)
		{
			if (auto& chunk = getChunkFromCache(file); chunk != sdl::emptycomponent)
			{
				bgs = chunk;
				bgs.setChannel(0);
			}
			else
			{
				bgs.load(file);
				if (bgs == sdl::emptycomponent) throw sdl::SDLCoreException{};
			}
			lastFileName[1] = file;
		}
		bgs.fadeIn(static_cast<uint32_t>(fadeInTime.count()), loop);
	}

	void AudioManager::playME(const std::string & file, const std::chrono::milliseconds & fadeInTime, int loop)
	{
		if (me.isPlaying()) me.stop();
		if (lastFileName[2] != file)
		{
			if (auto& chunk = getChunkFromCache(file); chunk != sdl::emptycomponent)
			{
				me = chunk;
				me.setChannel(1);
			}
			else
			{
				me.load(file);
				if (me == sdl::emptycomponent) throw sdl::SDLCoreException{};
			}
			lastFileName[2] = file;
		}
		me.fadeIn(static_cast<uint32_t>(fadeInTime.count()), loop);
	}

	void AudioManager::playSE(const std::string & file, const std::chrono::milliseconds & fadeInTime, int loop)
	{
		if (se.isPlaying()) se.stop();
		if (lastFileName[3] != file)
		{
			if (auto& chunk = getChunkFromCache(file); chunk != sdl::emptycomponent)
			{
				se = chunk;
				se.setChannel(2);
			}
			else
			{
				se.load(file);
				if (se == sdl::emptycomponent) throw sdl::SDLCoreException{};
			}
			lastFileName[3] = file;
		}
		se.fadeIn(static_cast<uint32_t>(fadeInTime.count()), loop);
	}

	void AudioManager::stopBGM(const std::chrono::milliseconds & fadeOutTime)
	{
		if (bgm.isPlaying())
			bgm.fadeOut(static_cast<int>(fadeOutTime.count()));
	}

	void AudioManager::stopBGS(const std::chrono::milliseconds & fadeOutTime)
	{
		if (bgs.isPlaying())
			bgs.fadeOut(static_cast<int>(fadeOutTime.count()));
	}

	void AudioManager::stopME(const std::chrono::milliseconds & fadeOutTime)
	{
		if (me.isPlaying())
			me.fadeOut(static_cast<int>(fadeOutTime.count()));
	}

	void AudioManager::stopSE(const std::chrono::milliseconds & fadeOutTime)
	{
		if (se.isPlaying())
			se.fadeOut(static_cast<int>(fadeOutTime.count()));
	}

	void AudioManager::pauseBGM(const std::chrono::milliseconds & fadeOutTime)
	{
		if (fadeOutTime.count() == 0)
		{
			bgm.pause();
			return;
		}
		//TODO: Make BGM Auto Pause when ME is playing
		/*fadeWorker = std::thread([&]()->void
		{
			using namespace std::chrono_literals;
			auto& bgm = AudioManager::getInstance().getBGM();
			float volumeDec = bgm.volume(-1) / static_cast<float>(fadeOutTime.count());
			Clock clock;
			while (true)
			{
				clock.reset();
				if (bgm.volume(-1) == 0) break;

				float newVolume = bgm.volume(-1) - volumeDec;
				bgm.volume(newVolume);
				auto now = clock.currentTick();
				if (now < 1ms)
					std::this_thread::sleep_for(1ms - now);
			}
		});*/
	}

	void AudioManager::resumeBGM(const std::chrono::milliseconds & fadeInTime)
	{
		if (fadeInTime.count() == 0)
		{
			bgm.resume();
			return;
		}
	}

	sdl::mixer::Music AudioManager::getBGM()
	{
		return bgm;
	}

	sdl::mixer::Chunk AudioManager::getBGS()
	{
		return bgs;
	}

	sdl::mixer::Chunk AudioManager::getME()
	{
		return me;
	}

	sdl::mixer::Chunk AudioManager::getSE()
	{
		return se;
	}

	float AudioManager::getBGMVolume()
	{
		return bgmVolume;
	}

	float AudioManager::getBGSVolume()
	{
		return bgsVolume;
	}

	float AudioManager::getMEVolume()
	{
		return meVolume;
	}

	float AudioManager::getSEVolume()
	{
		return seVolume;
	}

	void AudioManager::setBGMVolume(float value)
	{
		bgmVolume = boost::algorithm::clamp(value, 0, AudioManager::DefValue::MAX_AUDIO);
		bgm.volume(static_cast<int>(bgmVolume));
	}

	void AudioManager::setBGSVolume(float value)
	{
		bgsVolume = boost::algorithm::clamp(value, 0, AudioManager::DefValue::MAX_AUDIO);
		bgs.volume(static_cast<int>(bgsVolume));
	}

	void AudioManager::setMEVolume(float value)
	{
		meVolume = boost::algorithm::clamp(value, 0, AudioManager::DefValue::MAX_AUDIO);
		me.volume(static_cast<int>(meVolume));
	}

	void AudioManager::setSEVolume(float value)
	{
		seVolume = boost::algorithm::clamp(value, 0, AudioManager::DefValue::MAX_AUDIO);
		se.volume(static_cast<int>(seVolume));
	}

	void AudioManager::clear()
	{
		clearAllCache();
		bgm.destroy();
		bgs.destroy();
		me.destroy();
		se.destroy();
	}

	void AudioManager::tick()
	{
	}

	/*std::array<float, 1>& AudioManager::getLastVolume()
	{
		return lastVolume;
	}

	std::array<float, 4>& AudioManager::getVolume()
	{
		return volume;
	}*/

	AudioManager::AudioManager()
	{
	}

	AudioManager::~AudioManager()
	{
	}
}
#endif // VAS_USE_MIXER
