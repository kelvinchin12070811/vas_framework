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

		Music::Music(const Music & other) :
			SDLComponentBase(other.componentInstance)
		{
		}

		Music::Music(Music && other) :
			SDLComponentBase(std::move(other.componentInstance))
		{
		}

		Music::Music(Mix_Music * other) :
			SDLComponentBase(other, &notDeleteDeleter)
		{
		}

		Music::~Music()
		{
		}

		MusicType Music::getMusicType()
		{
			return static_cast<MusicType>(Mix_GetMusicType(&*this->componentInstance));
		}

		void Music::load(const std::string & file)
		{
			this->componentInstance = createRawComponent<Mix_Music>(Mix_LoadMUS(file.c_str()), &defDeleter);
		}

		void Music::loadRaw(sdl::rwops::RWops * src, bool freeSrc)
		{
			Mix_LoadMUS_RW(src, freeSrc ? 1 : 0);
		}

		void Music::loadRawTyped(sdl::rwops::RWops * src, MusicType type, bool freeSrc)
		{
			this->componentInstance = createRawComponent<Mix_Music>(Mix_LoadMUSType_RW(src, static_cast<Mix_MusicType>(type), freeSrc ? 1 : 0), &defDeleter);
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

		Music & Music::operator=(const Music & rhs)
		{
			this->componentInstance = rhs.componentInstance;
			return *this;
		}

		Music & Music::operator=(Music && rhs)
		{
			this->componentInstance = std::move(rhs.componentInstance);
			return *this;
		}

		Music & Music::operator=(std::nullptr_t)
		{
			this->componentInstance = nullptr;
			return *this;
		}

		void Music::VAS_PROTOTYPE_DEFINE_DEF_DELETER(Mix_Music)
		{
			Mix_FreeMusic(instance);
		}
	}
}
#endif // VAS_USE_MIXER
