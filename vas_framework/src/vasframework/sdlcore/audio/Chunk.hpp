//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#pragma once
#include "../../VASConfig.hpp"

#ifdef VAS_USE_MIXER
#include <SDL2/SDL_mixer.h>
#include "../SDLComponentBase.hpp"
#include "../RWops.hpp"
#include "Fading.hpp"

namespace vas::sdl
{
	namespace mixer
	{
		/**
		 * @ingroup sdl_mixer
		 * @{
		 */
		/**
		 * @brief The internal format for an audio chunk.
		 * @note If the channel index is set to -1, the first free channel will be use to play the audio.
		 */
		class VAS_DECLSPEC Chunk
		{ /** @} */
		public:
			Chunk(); /**< create empty chunk. */
			explicit Chunk(int channel); /**< Create empty chunk and allocate channel to it. */
			/**
			 * Create chunk and load audio from file.
			 * @param[in] file File to load.
			 * @param[in] channel allocate channel to chunk.
			 */
			Chunk(const std::string& file, int channel = -1);
			/**
			 * Reference from Mix_Chunk.
			 * @param[in] instance Instance of raw component.
			 * @param[in] owner Determine if this is one of the owner of @p instance.
			 */
			explicit Chunk(Mix_Chunk* instance, bool owner = false);

			/**
			 * Load from a file.
			 * @param[in] file File to load.
			 */
			void load(const std::string& file);
			/**
			 * Load from binary data.
			 * @param[in] src Binary data of audio.
			 * @param[in] freeSrc Free the source automaticaly.
			 */
			void loadRaw(rwops::RWops* src, bool freeSrc = true);
			/** Set channel index of chunk. */
			void setChannel(int channel);
			/** Get index of channel allocated of chunk. */
			int getChannel();
			/** Get the fading state of chunk. */
			Fading fading();

			/**
			 * Fade in the channel.
			 * @param[in] channel Channel to use.
			 * @param[in] duration Effect duration in miliseconds.
			 * @param[in] loops Times for audio to loop, infinity loop if <= 0.
			 * @param[in] terminateDuration Tells the api to stop the channel at duration in milisecond, -1 for not timed.
			 */
			void fadeIn(int channel, uint32_t duration, int loops = 1, int terminateDuration = -1);
			/**
			 * Fade in the channel on the chunk's allocated channel.
			 * @param[in] duration Effect duration in miliseconds.
			 * @param[in] loops Times for audio to loop, infinity loop if <= 0.
			 * @param[in] terminateDuration Tells the api to stop the channel at duration in milisecond, -1 for not timed.
			 */
			void fadeIn(uint32_t duration, int loops = 1, int terminateDuration = -1);
			/**
			 * Fade out the channel.
			 * @param[in] duration Effect duration in miliseconds.
			 */
			void fadeOut(int duration);

			/**
			 * Play channel.
			 * @param[in] channel Channel to use.
			 * @param[in] loops Times for audio to loop, infinity loop if <= 0.
			 * @param[in] terminateDuration Tells the api to stop the channel at duration in milisecond, -1 for not timed.
			 */
			void play(int channel, int loops = 1, int terminateDuration = -1);
			/**
			 * Play channel on chunk's allocated channel.
			 * @param[in] loops Times for audio to loop, infinity loop if <= 0.
			 * @param[in] terminateDuration Tells the api to stop the channel at duration in milisecond, -1 for not timed.
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

			/**
			 * Set the volume in the range of 0-128 of a specific channel or chunk. If the specified channel is -1, set 
			 * volume for all channels.
			 * 
			 * @return the original volume. If the specified volume is -1, just return the current volume.
			 */
			int volume(int volumeLevel);

			void destroy(); /**< Destroy instance. */
			bool isNull(); /**< Check if instance is nullcomponent. */

			/**
			 * @name Public common functions.
			 * The common functions to controll the entier system of the mixer.
			 * @{
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
			static Chunk getChunk(int channel); /**< Get chunk that playing on a specified channel. */
			/** @} */

			/**
			 * @name Overloaded operators
			 * @{
			 */
			explicit operator Mix_Chunk*(); /**< Cast to raw component. */
			Chunk& operator=(NullComponent_t);

			bool operator==(const Chunk& rhs); /**< Compare if two instance are equal. */
			bool operator!=(const Chunk& rhs); /**< Compare if two instance are not equal. */
			bool operator==(NullComponent_t); /**< Determine if instance is nullcomponent. */
			bool operator!=(NullComponent_t); /**< Determine if instance is not nullcomponent. */
			/** @} */
		private:
			int channel{ -1 };
			std::shared_ptr<Mix_Chunk> componentInstance;
		};
	}
}
#endif // VAS_USE_MIXER
