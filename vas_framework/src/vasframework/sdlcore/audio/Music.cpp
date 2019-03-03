//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#include "Music.hpp"

#ifdef VAS_USE_MIXER
namespace vas::sdl
{
	namespace mixer
	{
		Music::Music()
		{
		}

		Music::Music(const std::string & file)
		{
			load(file);
		}

		Music::Music(Mix_Music * other, bool owner)
		{
			if (owner) componentInstance = std::shared_ptr<Mix_Music>{ other, &Mix_FreeMusic };
			else componentInstance = std::shared_ptr<Mix_Music>{ other, [](Mix_Music* i) { return; } };
		}

		MusicType Music::getMusicType()
		{
			return static_cast<MusicType>(Mix_GetMusicType(&*this->componentInstance));
		}

		void Music::load(const std::string & file)
		{
			this->componentInstance = std::shared_ptr<Mix_Music>{ Mix_LoadMUS(file.c_str()), &Mix_FreeMusic };
		}

		void Music::loadRaw(sdl::rwops::RWops * src, bool freeSrc)
		{
			Mix_LoadMUS_RW(src, freeSrc ? 1 : 0);
		}

		void Music::loadRawTyped(sdl::rwops::RWops * src, MusicType type, bool freeSrc)
		{
			this->componentInstance = std::shared_ptr<Mix_Music>{ Mix_LoadMUSType_RW(src, static_cast<Mix_MusicType>(type), freeSrc ? 1 : 0), &Mix_FreeMusic };
		}

		void Music::fadeIn(int duration, int loops)
		{
			if (loops > 0) loops--;
			Mix_FadeInMusic(&*this->componentInstance, loops, duration);
		}

		void Music::fadeInAt(double position, int duration, int loops)
		{
			if (loops > 0) loops--;
			Mix_FadeInMusicPos(&*this->componentInstance, loops, duration, position);
		}

		void Music::play(int loops)
		{
			if (loops > 0) loops--;
			Mix_PlayMusic(&*this->componentInstance, loops);
		}

		void Music::fadeOut(int duration)
		{
			Mix_FadeOutMusic(duration);
		}

		Fading Music::fading()
		{
			return static_cast<Fading>(Mix_FadingMusic());
		}

		void Music::pause()
		{
			Mix_PauseMusic();
		}

		void Music::resume()
		{
			Mix_ResumeMusic();
		}

		void Music::rewind()
		{
			Mix_RewindMusic();
		}

		bool Music::isPlaying()
		{
			return Mix_PlayingMusic() == 1 ? true : false;
		}

		bool Music::isPaused()
		{
			return Mix_PausedMusic() == 0 ? false : true;
		}

		void Music::stop()
		{
			Mix_HaltMusic();
		}

		bool Music::setPosition(double position)
		{
			return Mix_SetMusicPosition(position) == 0 ? true : false;
		}

		int Music::volume(int volume)
		{
			return Mix_VolumeMusic(volume);
		}

		void Music::destroy()
		{
			componentInstance = nullptr;
		}

		bool Music::isNull()
		{
			return componentInstance == nullptr;
		}

		Music::operator Mix_Music*()
		{
			return componentInstance.get();
		}
		
		Music & Music::operator=(NullComponent_t)
		{
			componentInstance = nullptr;
			return *this;
		}
		
		bool Music::operator==(const Music & rhs)
		{
			return componentInstance == rhs.componentInstance;
		}
		
		bool Music::operator==(NullComponent_t)
		{
			return isNull();
		}
		
		bool Music::operator!=(const Music & rhs)
		{
			return !operator==(rhs);
		}
		
		bool Music::operator!=(NullComponent_t)
		{
			return !operator==(nullcomponent);
		}
	}
}
#endif // VAS_USE_MIXER
