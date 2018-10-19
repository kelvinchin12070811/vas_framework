#pragma once
#include "../../VASConfig.hpp"

#ifdef VAS_USE_MIXER
#include <SDL_mixer.h>
#include "../SDLComponentBase.hpp"
#include "../RWops.hpp"
#include "Fading.hpp"

namespace vas::sdl
{
	namespace mixer
	{
		/** @addtogroup sdl_mixer
			  @{
		*/
		/** @brief The internal format for an audio chunk.
			  @note If the channel index is set to -1, the first free channel will be use to play the audio.
		*/
		class VAS_DECLSPEC Chunk : public SDLComponentBase<Mix_Chunk, Chunk>
		{ /** @} */
		public:
			Chunk(); /**< create empty chunk. */
			explicit Chunk(int channel); /**< Create empty chunk and allocate channel to it. */
			/** Create chunk and load audio from file.
				  @param file File to load.
				  @param channel allocate channel to chunk.
			*/
			Chunk(const std::string& file, int channel = -1);
			Chunk(const Chunk& rhs);
			Chunk(Chunk&& rhs);
			/**< Reference from Mix_Chunk. */
			explicit Chunk(Mix_Chunk* instance, SDLComponentBase::DeleterType deleter = &notDeleteDeleter);
			~Chunk();

			/** Load from a file.
				  @param file File to load.
			*/
			void load(const std::string& file);
			/** Load from binary data.
				  @param src Binary data of audio.
				  @param freeSrc Free the source automaticaly.
			*/
			void loadRaw(rwops::RWops* src, bool freeSrc = true);
			/** Set channel index of chunk. */
			void setChannel(int channel);
			/** Get index of channel allocated of chunk. */
			int getChannel();
			/** Get the fading state of chunk. */
			Fading fading();

			/** Fade in the channel.
				  @param channel Channel to use.
				  @param duration Effect duration in miliseconds.
				  @param loops Times for audio to loop, infinity loop if <= 0.
				  @param terminateDuration Tells the api to stop the channel at duration in milisecond, -1 for not timed.
			*/
			void fadeIn(int channel, uint32_t duration, int loops = 1, int terminateDuration = -1);
			/** Fade in the channel on the chunk's allocated channel.
				  @param duration Effect duration in miliseconds.
				  @param loops Times for audio to loop, infinity loop if <= 0.
				  @param terminateDuration Tells the api to stop the channel at duration in milisecond, -1 for not timed.
			*/
			void fadeIn(uint32_t duration, int loops = 1, int terminateDuration = -1);
			/** Fade out the channel.
				  @param duration Effect duration in miliseconds.
			*/
			void fadeOut(int duration);

			/** Play channel.
				  @param channel Channel to use.
				  @param loops Times for audio to loop, infinity loop if <= 0.
				  @param terminateDuration Tells the api to stop the channel at duration in milisecond, -1 for not timed.
			*/
			void play(int channel, int loops = 1, int terminateDuration = -1);
			/** Play channel on chunk's allocated channel.
				  @param loops Times for audio to loop, infinity loop if <= 0.
				  @param terminateDuration Tells the api to stop the channel at duration in milisecond, -1 for not timed.
			*/
			void play(int loops = 1, int terminateDuration = -1);

			void pause(); /**< Pause the audio. */
			void resume(); /**< Resume the audio. */
			bool isPaused(); /**< Determine if the audio is paused. */
			bool isPlaying(); /**< Determine if the audio is playing. */
			void stop(); /**< Stop (Halt) the audio. */

			/** Load a wave file of the mixer format from a memory buffer */
			void quickLoadWAV(uint8_t* mem);

			/** Load raw audio data of the mixer format from a memory buffer */
			void quickLoadRaw(uint8_t* mem, uint32_t length);

			/** Set the volume in the range of 0-128 of a specific channel or chunk.
			If the specified channel is -1, set volume for all channels.
			Returns the original volume.
			If the specified volume is -1, just return the current volume.
			*/
			int volume(int volumeLevel);

			/** @name Public common functions.
				  The common functions to controll the entier system of the mixer.
				  @{
			*/
			static void fadeOut(int channel, int duration); /**< Fade out chunk. */
			static void fadeOutGroup(int tag, int duration); /**< Fade entire group. */
			static Fading fading(int channel); /**< Get fading state of a channel. */
			static void pause(int channel); /**< Pause a channel. */
			static void resume(int channel); /**< Resume a channel. */
			static bool isPaused(int channel); /**< Determine if a channel is paused. */
			static bool isPlaying(int channel); /**< Determine if a channel is playing. */
			static void stop(int channel); /**< Stop(Halt) a channel. */
			static void stopGroup(int tag); /**< Stop entire group. */
			/** @} */

			static Chunk getChunk(int channel); /**< Get chunk that playing on a specified channel. */

			Chunk& operator=(const Chunk& rhs);
			Chunk& operator=(Chunk&& rhs);
			Chunk& operator=(std::nullptr_t);

			static void VAS_PROTOTYPE_DEFINE_DEF_DELETER(Mix_Chunk);
		private:
			int channel{ -1 };
		};
	}
}
#endif // VAS_USE_MIXER
