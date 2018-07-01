#pragma once
#include "../../VASConfig.hpp"

#ifdef VAS_USE_MIXER
#include "Fading.hpp"
#include "../SDLComponentBase.hpp"
#include "../RWops.hpp"
#include "Flags.hpp"

namespace vas::sdl
{
	namespace mixer
	{
		class VAS_DECLSPEC Music : public SDLComponentBase<Mix_Music, Music>
		{
		public:
			Music();
			Music(const std::string& file);
			Music(const Music& other);
			Music(Music&& other);

			explicit Music(Mix_Music* other);
			~Music();

			MusicType getMusicType();

			void load(const std::string& file);
			void loadRaw(sdl::rwops::RWops* src, bool freeSrc = true);
			void loadRawTyped(sdl::rwops::RWops* src, MusicType type, bool freeSrc = true);

			void fadeIn(int duration, int loops = -1);
			void fadeInAt(double position, int duration, int loops = -1);
			void play(int loops = -1);

			static void fadeOut(int duration);
			static Fading fading();
			static void pause();
			static void resume();
			static void rewind();
			static bool isPlaying();
			static bool isPaused();
			static void stop();

			/* Set the current position in the music stream.
			This returns 0 if successful, or -1 if it failed or isn't implemented.
			This function is only implemented for MOD music formats (set pattern
			order number) and for OGG, FLAC, MP3_MAD, and MODPLUG music (set
			position in seconds), at the moment.
			*/
			static bool setPosition(double position);

			/* Set the volume in the range of 0-128 of a specific channel or chunk.
			If the specified channel is -1, set volume for all channels.
			Returns the original volume.
			If the specified volume is -1, just return the current volume.
			*/
			static int volume(int volume);

			Music& operator=(const Music& rhs);
			Music& operator=(Music&& rhs);
			Music& operator=(std::nullptr_t);

			static void VAS_PROTOTYPE_DEFINE_DEF_DELETER(Mix_Music);
		};
	}
}
#endif // VAS_USE_MIXER
