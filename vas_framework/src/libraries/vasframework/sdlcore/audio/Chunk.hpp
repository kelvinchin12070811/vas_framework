#pragma once
#include <SDL_mixer.h>
#include "../../VASConfig.hpp"
#include "../SDLComponentBase.hpp"
#include "../RWops.hpp"
#include "Fading.hpp"

namespace sdl
{
	namespace mixer
	{
		class VAS_DECLSPEC Chunk : public SDLComponentBase<Mix_Chunk, Chunk>
		{
		public:
			Chunk();
			Chunk(const std::string& file);
			Chunk(const Chunk& rhs);
			Chunk(Chunk&& rhs);
			explicit Chunk(Mix_Chunk* instance, SDLComponentBase::DeleterType deleter = &notDeleteDeleter);
			~Chunk();

			void load(const std::string& file);
			void loadRaw(rwops::RWops* src, bool freeSrc = true);

			//int terminateDuration = -1, this varaible tells the api to terminate the channel at duration in milisecond
			void fadeIn(int channel, int duration, int loops = 1, int terminateDuration = -1);

			//int terminateDuration = -1, this varaible tells the api to terminate the channel at duration in milisecond
			void play(int channel, int loops = 1, int terminateDuration = -1);

			/* Load a wave file of the mixer format from a memory buffer */
			void quickLoadWAV(uint8_t* mem);

			/* Load raw audio data of the mixer format from a memory buffer */
			void quickLoadRaw(uint8_t* mem, uint32_t length);

			/* Set the volume in the range of 0-128 of a specific channel or chunk.
			If the specified channel is -1, set volume for all channels.
			Returns the original volume.
			If the specified volume is -1, just return the current volume.
			*/
			int volume(int volumeLevel);

			static void fadeOut(int channel, int duration);
			static void fadeOutGroup(int tag, int duration);
			static Fading fading(int channel);
			static void pause(int channel);
			static void resume(int channel);
			static bool isPaused(int channel);
			static bool isPlaying(int channel);
			static void stop(int channel);
			static void stopGroup(int tag);

			static Chunk getChunk(int channel);

			Chunk& operator=(const Chunk& rhs);
			Chunk& operator=(Chunk&& rhs);
			Chunk& operator=(std::nullptr_t);

			static void VAS_PROTOTYPE_DEFINE_DEF_DELETER(Mix_Chunk);
		};
	}
}