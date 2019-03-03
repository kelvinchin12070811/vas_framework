//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#include "Chunk.hpp"

#ifdef VAS_USE_MIXER
namespace vas::sdl
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

		Chunk::Chunk(Mix_Chunk * instance, bool owner)
		{
			if (owner) componentInstance = std::shared_ptr<Mix_Chunk>{ instance, &Mix_FreeChunk };
			else componentInstance = std::shared_ptr<Mix_Chunk>{ instance, [](Mix_Chunk* i) { return; } };
		}

		void Chunk::load(const std::string & file)
		{
			this->componentInstance = std::shared_ptr<Mix_Chunk>{ Mix_LoadWAV(file.c_str()), &Mix_FreeChunk };
		}

		void Chunk::loadRaw(rwops::RWops * src, bool freeSrc)
		{
			this->componentInstance = std::shared_ptr<Mix_Chunk>{ Mix_LoadWAV_RW(src, freeSrc ? 1 : 0), &Mix_FreeChunk };
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
			this->componentInstance = std::shared_ptr<Mix_Chunk>{ Mix_QuickLoad_WAV(mem), &Mix_FreeChunk };
		}

		void Chunk::quickLoadRaw(uint8_t * mem, uint32_t length)
		{
			this->componentInstance = std::shared_ptr<Mix_Chunk>{ Mix_QuickLoad_RAW(mem, length), &Mix_FreeChunk };
		}

		int Chunk::volume(int volumeLevel)
		{
			return Mix_VolumeChunk(&*this->componentInstance, volumeLevel);
		}

		void Chunk::destroy()
		{
			componentInstance = nullptr;
		}

		bool Chunk::isNull()
		{
			return componentInstance == nullptr;
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

		Chunk::operator Mix_Chunk*()
		{
			return componentInstance.get();
		}
		
		Chunk & Chunk::operator=(NullComponent_t)
		{
			componentInstance = nullptr;
			return *this;
		}
		
		bool Chunk::operator==(const Chunk & rhs)
		{
			return componentInstance == rhs.componentInstance;
		}
		
		bool Chunk::operator!=(const Chunk & rhs)
		{
			return !operator==(rhs);
		}
		
		bool Chunk::operator==(NullComponent_t)
		{
			return isNull();
		}
		
		bool Chunk::operator!=(NullComponent_t)
		{
			return !operator==(nullcomponent);
		}
	}
}
#endif // VAS_USE_MIXER
