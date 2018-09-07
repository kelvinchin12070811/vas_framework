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

	void AudioManger::playBGM(const std::string & file, const std::chrono::milliseconds & fadeInTime, int loop)
	{
		if (bgm.isPlaying()) bgm.stop();
		if (lastFileName[0] != file)
		{
			bgm.load(file);
			if (bgm == sdl::emptycomponent) throw sdl::SDLCoreException();
			lastFileName[0] = file;
		}
		bgm.fadeIn(static_cast<int>(fadeInTime.count()), loop);
	}

	void AudioManger::playBGS(const std::string & file, const std::chrono::milliseconds & fadeInTime, int loop)
	{
		if (bgs.isPlaying()) bgs.stop();
		if (lastFileName[1] != file)
		{
			bgs.load(file);
			if (bgs == sdl::emptycomponent) throw sdl::SDLCoreException();
			lastFileName[1] = file;
		}
		bgs.fadeIn(static_cast<uint32_t>(fadeInTime.count()), loop);
	}

	void AudioManger::playME(const std::string & file, const std::chrono::milliseconds & fadeInTime, int loop)
	{
		if (me.isPlaying()) me.stop();
		if (lastFileName[2] != file)
		{
			me.load(file);
			if (me == sdl::emptycomponent) throw sdl::SDLCoreException();
			lastFileName[2] = file;
		}
		me.fadeIn(static_cast<uint32_t>(fadeInTime.count()), loop);
	}

	void AudioManger::playSE(const std::string & file, const std::chrono::milliseconds & fadeInTime, int loop)
	{
		if (se.isPlaying()) se.stop();
		if (lastFileName[3] != file)
		{
			se.load(file);
			if (se == sdl::emptycomponent) throw sdl::SDLCoreException();
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
			auto& bgm = AudioManger::getInstance().BGM();
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

	sdl::mixer::Music AudioManger::BGM()
	{
		return bgm;
	}

	sdl::mixer::Chunk AudioManger::BGS()
	{
		return bgs;
	}

	sdl::mixer::Chunk AudioManger::ME()
	{
		return me;
	}

	sdl::mixer::Chunk AudioManger::SE()
	{
		return se;
	}

	float AudioManger::getBGMVolume()
	{
		return volume[0];
	}

	float AudioManger::getBGSVolume()
	{
		return volume[1];
	}

	float AudioManger::getMEVolume()
	{
		return volume[2];
	}

	float AudioManger::getSEVolume()
	{
		return volume[3];
	}

	void AudioManger::setBGMVolume(float value)
	{
		volume[0] = boost::algorithm::clamp(value, 0, AudioManger::DefValue::MAX_AUDIO);
		bgm.volume(static_cast<int>(volume[0]));
	}

	void AudioManger::setBGSVolume(float value)
	{
		volume[1] = boost::algorithm::clamp(value, 0, AudioManger::DefValue::MAX_AUDIO);
		bgs.volume(static_cast<int>(volume[1]));
	}

	void AudioManger::setMEVolume(float value)
	{
		volume[2] = boost::algorithm::clamp(value, 0, AudioManger::DefValue::MAX_AUDIO);
		me.volume(static_cast<int>(volume[2]));
	}

	void AudioManger::setSEVolume(float value)
	{
		volume[3] = boost::algorithm::clamp(value, 0, AudioManger::DefValue::MAX_AUDIO);
		se.volume(static_cast<int>(volume[3]));
	}

	void AudioManger::clear()
	{
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
