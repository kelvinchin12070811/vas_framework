//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#pragma once
#include "../../VASConfig.hpp"

#ifdef VAS_USE_MIXER
#include <cstdint>
#include <SDL2/SDL_mixer.h>

namespace vas::sdl
{
	namespace mixer
	{
		/**
		 * @ingroup sdl_mixer
		 * @{
		 */
		/** @brief Initialization options for sdl_mixer. */
		struct MixInitFlags
		{
			using FlagsType = int; /**< Flags type. */
			static const FlagsType flac = 0x00000001; /**< flac audio. */
			static const FlagsType mod = 0x00000002; /**< mod audio. */
			static const FlagsType modplug = 0x00000004; /**< modplug audio. */
			static const FlagsType mp3 = 0x00000008; /**< mp3 audio. */
			static const FlagsType ogg = 0x00000010; /**< ogg audio. @note SDL_mixer on SDL 2.0.7 can't load ogg libarary for some reason. */
			static const FlagsType fluidsynth = 0x00000020; /**< fluidsynth audio. */
			static const FlagsType all = flac | mod | modplug | mp3 | ogg | fluidsynth; /**< all type of audio. */
			//static const FlagsType commonType = flac | mp3 | ogg; // For specific reason, SDL_mixer on SDL 2.0.7 don't load ogg
		};

		/** @brief Default values of mixer::openAudio(). */
		struct DefaultValues
		{
			static const int frequency = 44100; /**< default frequency (44.1 kHz). */
			static const int channelCount = 2; /**< 2 channel stereo audio. */
			static const int chunkSize = 1024; /**< 1KB chunk size. */
			static const int format = MIX_DEFAULT_FORMAT; /**< mixer default format. */
			static const uint8_t maxVolume = 128; /**< default maximum volume of sdl_mixer. */
		};

		/** @brief Type of the music stream. */
		enum class MusicType {
			none = MUS_NONE, /**< NONE. */
			cmd = MUS_CMD, /**< cmd. */
			wav = MUS_WAV, /**< wav. */
			mod = MUS_MOD, /**< mod. */
			mid = MUS_MID, /**< mid. */
			ogg = MUS_OGG, /**< ogg. */
			mp3 = MUS_MP3, /**< mp3. */
			//mp3Mad = Mix_MusicType::MUS_MP3_MAD_UNUSED,
			flac = MUS_FLAC, /**< flac. */
			//modplug = MUS_MODPLUG
		};
		/** @} */
	}
}
#endif // VAS_USE_MIXER
