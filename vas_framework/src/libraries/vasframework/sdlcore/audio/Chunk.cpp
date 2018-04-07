#include "Chunk.hpp"

#ifdef VAS_USE_MIXER
namespace sdl
{
	namespace mixer
	{
		Chunk::Chunk()
		{
		}

		Chunk::Chunk(int channel) :
			channel(channel)
		{
		}

		Chunk::Chunk(const std::string & file, int channel) :
			channel(channel)
		{
			load(file);
		}

		Chunk::Chunk(const Chunk & rhs) :
			SDLComponentBase(rhs.componentInstance)
		{
		}

		Chunk::Chunk(Chunk && rhs) :
			SDLComponentBase(std::move(rhs.componentInstance))
		{
		}

		Chunk::Chunk(Mix_Chunk * instance, SDLComponentBase::DeleterType deleter) :
			SDLComponentBase(instance, deleter)
		{
		}

		Chunk::~Chunk()
		{
		}

		void Chunk::load(const std::string & file)
		{
			this->componentInstance = createRawComponent<Mix_Chunk>(Mix_LoadWAV(file.c_str()), &defDeleter);
		}

		void Chunk::loadRaw(rwops::RWops * src, bool freeSrc)
		{
			this->componentInstance = createRawComponent<Mix_Chunk>(Mix_LoadWAV_RW(src, freeSrc ? 1 : 0), &defDeleter);
		}

		void Chunk::setChannel(int channel)
		{
			this->channel = channel;
		}

		int Chunk::getChannel()
		{
			return channel;
		}

		Fading Chunk::fading()
		{
			return static_cast<Fading>(Mix_FadingChannel(channel));
		}

		void Chunk::fadeIn(int channel, uint32_t duration, int loops, int terminateDuration)
		{
			if (loops > 0) loops--;
			Mix_FadeInChannelTimed(channel, &*this->componentInstance, loops, duration, terminateDuration);
		}

		void Chunk::fadeIn(uint32_t duration, int loops, int terminateDuration)
		{
			fadeIn(channel, duration, loops, terminateDuration);
		}

		void Chunk::fadeOut(int duration)
		{
			fadeOut(channel, duration);
		}

		void Chunk::play(int channel, int loops, int terminateDuration)
		{
			if (loops > 0) loops--;
			Mix_PlayChannelTimed(channel, &*this->componentInstance, loops, terminateDuration);
		}

		void Chunk::play(int loops, int terminateDuration)
		{
			play(channel, loops, terminateDuration);
		}

		void Chunk::pause()
		{
			pause(channel);
		}

		void Chunk::resume()
		{
			resume(channel);
		}

		bool Chunk::isPaused()
		{
			return isPaused(channel);
		}

		bool Chunk::isPlaying()
		{
			return isPlaying(channel);
		}

		void Chunk::stop()
		{
			stop(channel);
		}

		void Chunk::quickLoadWAV(uint8_t * mem)
		{
			this->componentInstance = createRawComponent<Mix_Chunk>(Mix_QuickLoad_WAV(mem), &defDeleter);
		}

		void Chunk::quickLoadRaw(uint8_t * mem, uint32_t length)
		{
			this->componentInstance = createRawComponent<Mix_Chunk>(Mix_QuickLoad_RAW(mem, length), &defDeleter);
		}

		int Chunk::volume(int volumeLevel)
		{
			return Mix_VolumeChunk(&*this->componentInstance, volumeLevel);
		}

		void Chunk::fadeOut(int channel, int duration)
		{
			Mix_FadeOutChannel(channel, duration);
		}

		void Chunk::fadeOutGroup(int tag, int duration)
		{
			Mix_FadeOutGroup(tag, duration);
		}

		Fading Chunk::fading(int channel)
		{
			return static_cast<Fading>(Mix_FadingChannel(channel));
		}

		void Chunk::pause(int channel)
		{
			Mix_Pause(channel);
		}

		void Chunk::resume(int channel)
		{
			Mix_Resume(channel);
		}

		bool Chunk::isPaused(int channel)
		{
			return Mix_Paused(channel) == 1;
		}

		bool Chunk::isPlaying(int channel)
		{
			return Mix_Playing(channel) == 1;
		}

		void Chunk::stop(int channel)
		{
			Mix_HaltChannel(channel);
		}

		void Chunk::stopGroup(int tag)
		{
			Mix_HaltGroup(tag);
		}

		Chunk Chunk::getChunk(int channel)
		{
			return static_cast<Chunk>(Mix_GetChunk(channel));
		}

		Chunk & Chunk::operator=(const Chunk & rhs)
		{
			this->componentInstance = rhs.componentInstance;
			return *this;
		}

		Chunk & Chunk::operator=(Chunk && rhs)
		{
			this->componentInstance = std::move(rhs.componentInstance);
			return *this;
		}

		Chunk & Chunk::operator=(std::nullptr_t)
		{
			this->componentInstance = nullptr;
			return *this;
		}

		void Chunk::VAS_PROTOTYPE_DEFINE_DEF_DELETER(Mix_Chunk)
		{
			Mix_FreeChunk(instance);
		}
	}
}
#endif // VAS_USE_MIXER
