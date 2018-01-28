#pragma once
#include <cstdint>
#include <SDL_mixer.h>

namespace sdl
{
	namespace mixer
	{
		struct MixInitFlags
		{
			using FlagsType = int;
			static const FlagsType flac = 0x00000001;
			static const FlagsType mod = 0x00000002;
			static const FlagsType modplug = 0x00000004;
			static const FlagsType mp3 = 0x00000008;
			static const FlagsType ogg = 0x00000010;
			static const FlagsType fluidsynth = 0x00000020;
			static const FlagsType all = flac | mod | modplug | mp3 | ogg | fluidsynth;
			static const FlagsType commonType = flac | mp3 | ogg;
		};

		struct DefaultValues
		{
			static const int frequency = 44100;
			static const int channelCount = 2;
			static const int chunkSize = 1024;
			static const int format = MIX_DEFAULT_FORMAT;
			static const uint8_t maxVolume = 128;
		};

		enum class MusicType{
			none = MUS_NONE,
			cmd = MUS_CMD,
			wav = MUS_WAV,
			mod = MUS_MOD,
			mid = MUS_MID,
			ogg = MUS_OGG,
			mp3 = MUS_MP3,
			mp3Mad = MUS_MP3_MAD,
			flac = MUS_FLAC,
			modplug = MUS_MODPLUG
		};
	}
}