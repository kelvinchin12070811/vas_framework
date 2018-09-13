#include "AudioManger.hpp"

#ifdef VAS_USE_MIXER
#include <boost/algorithm/clamp.hpp>
#include "../util/CommonTools.hpp"
#include "../math/Clock.hpp"
#include "../sdlcore/SDLCoreException.hpp"

using namespace std::chrono_literals;

const float vas::AudioManger::DefValue::MAX_AUDIO = 128.0f;

namespace vas
{
	AudioManger & AudioManger::getInstance()
	{
		static AudioManger instance;
		return instance;
	}

	void AudioManger::cacheChunk(const std::string & id, sdl::mixer::Chunk chunk)
	{
		chunkCache[id] = std::move(chunk);
	}

	void AudioManger::cacheChunk(const std::string & fileName)
	{
		sdl::mixer::Chunk temp(fileName);
		cacheChunk(fileName, std::move(temp));
	}

	void AudioManger::cacheMusic(const std::string & id, sdl::mixer::Music music)
	{
		musicCache[id] = music;
	}

	void AudioManger::cacheMusic(const std::string & fileName)
	{
		sdl::mixer::Music temp(fileName);
		cacheMusic(fileName, std::move(temp));
	}

	void AudioManger::removeChunkFromCache(const std::string & id)
	{
		chunkCache.erase(id);
	}

	void AudioManger::removeMusicFromCache(const std::string & id)
	{
		musicCache.erase(id);
	}

	sdl::mixer::Chunk AudioManger::getChunkFromCache(const std::string & id)
	{
		auto chunk = chunkCache.find(id);
		return chunk == chunkCache.end() ? sdl::mixer::Chunk() : chunk->second;
	}

	sdl::mixer::Music AudioManger::getMusicFromCache(const std::string & id)
	{
		auto music = musicCache.find(id);
		return music == musicCache.end() ? sdl::mixer::Music() : music->second;
	}

	bool AudioManger::isChunkCacheEmpty()
	{
		return chunkCache.empty();
	}

	bool AudioManger::isMusicCacheEmpty()
	{
		return musicCache.empty();
	}

	size_t AudioManger::chunkCacheSize()
	{
		return chunkCache.size();
	}

	size_t AudioManger::musicCacheSize()
	{
		return musicCache.size();
	}

	void AudioManger::clearChunkCache()
	{
		chunkCache.clear();
	}

	void AudioManger::clearMusicCache()
	{
		musicCache.clear();
	}

	void AudioManger::clearAllCache()
	{
		clearChunkCache();
		clearMusicCache();
	}

	void AudioManger::playBGM(const std::string & file, const std::chrono::milliseconds & fadeInTime, int loop)
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
				if (bgm == sdl::emptycomponent) throw sdl::SDLCoreException();
			}
			lastFileName[0] = file;
		}
		bgm.fadeIn(static_cast<int>(fadeInTime.count()), loop);
	}

	void AudioManger::playBGS(const std::string & file, const std::chrono::milliseconds & fadeInTime, int loop)
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
				if (bgs == sdl::emptycomponent) throw sdl::SDLCoreException();
			}
			lastFileName[1] = file;
		}
		bgs.fadeIn(static_cast<uint32_t>(fadeInTime.count()), loop);
	}

	void AudioManger::playME(const std::string & file, const std::chrono::milliseconds & fadeInTime, int loop)
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
				if (me == sdl::emptycomponent) throw sdl::SDLCoreException();
			}
			lastFileName[2] = file;
		}
		me.fadeIn(static_cast<uint32_t>(fadeInTime.count()), loop);
	}

	void AudioManger::playSE(const std::string & file, const std::chrono::milliseconds & fadeInTime, int loop)
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
				if (se == sdl::emptycomponent) throw sdl::SDLCoreException();
			}
			lastFileName[3] = file;
		}
		se.fadeIn(static_cast<uint32_t>(fadeInTime.count()), loop);
	}

	void AudioManger::stopBGM(const std::chrono::milliseconds & fadeOutTime)
	{
		if (bgm.isPlaying())
			bgm.fadeOut(static_cast<int>(fadeOutTime.count()));
	}

	void AudioManger::stopBGS(const std::chrono::milliseconds & fadeOutTime)
	{
		if (bgs.isPlaying())
			bgs.fadeOut(static_cast<int>(fadeOutTime.count()));
	}

	void AudioManger::stopME(const std::chrono::milliseconds & fadeOutTime)
	{
		if (me.isPlaying())
			me.fadeOut(static_cast<int>(fadeOutTime.count()));
	}

	void AudioManger::stopSE(const std::chrono::milliseconds & fadeOutTime)
	{
		if (se.isPlaying())
			se.fadeOut(static_cast<int>(fadeOutTime.count()));
	}

	void AudioManger::pauseBGM(const std::chrono::milliseconds & fadeOutTime)
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
			auto& bgm = AudioManger::getInstance().getBGM();
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

	void AudioManger::resumeBGM(const std::chrono::milliseconds & fadeInTime)
	{
		if (fadeInTime.count() == 0)
		{
			bgm.resume();
			return;
		}
	}

	sdl::mixer::Music AudioManger::getBGM()
	{
		return bgm;
	}

	sdl::mixer::Chunk AudioManger::getBGS()
	{
		return bgs;
	}

	sdl::mixer::Chunk AudioManger::getME()
	{
		return me;
	}

	sdl::mixer::Chunk AudioManger::getSE()
	{
		return se;
	}

	float AudioManger::getBGMVolume()
	{
		return bgmVolume;
	}

	float AudioManger::getBGSVolume()
	{
		return bgsVolume;
	}

	float AudioManger::getMEVolume()
	{
		return meVolume;
	}

	float AudioManger::getSEVolume()
	{
		return seVolume;
	}

	void AudioManger::setBGMVolume(float value)
	{
		bgmVolume = boost::algorithm::clamp(value, 0, AudioManger::DefValue::MAX_AUDIO);
		bgm.volume(static_cast<int>(bgmVolume));
	}

	void AudioManger::setBGSVolume(float value)
	{
		bgsVolume = boost::algorithm::clamp(value, 0, AudioManger::DefValue::MAX_AUDIO);
		bgs.volume(static_cast<int>(bgsVolume));
	}

	void AudioManger::setMEVolume(float value)
	{
		meVolume = boost::algorithm::clamp(value, 0, AudioManger::DefValue::MAX_AUDIO);
		me.volume(static_cast<int>(meVolume));
	}

	void AudioManger::setSEVolume(float value)
	{
		seVolume = boost::algorithm::clamp(value, 0, AudioManger::DefValue::MAX_AUDIO);
		se.volume(static_cast<int>(seVolume));
	}

	void AudioManger::clear()
	{
		clearAllCache();
		bgm.destroy();
		bgs.destroy();
		me.destroy();
		se.destroy();
	}

	void AudioManger::tick()
	{
	}

	/*std::array<float, 1>& AudioManger::getLastVolume()
	{
		return lastVolume;
	}

	std::array<float, 4>& AudioManger::getVolume()
	{
		return volume;
	}*/

	AudioManger::AudioManger()
	{
	}

	AudioManger::~AudioManger()
	{
	}
}
#endif // VAS_USE_MIXER
