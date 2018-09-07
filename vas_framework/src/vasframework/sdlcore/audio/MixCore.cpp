#include "MixCore.hpp"

#ifdef VAS_USE_MIXER
boost::signals2::signal<void()> vas::sdl::mixer::Signals::MusicFinished{};
boost::signals2::signal<void(int)> vas::sdl::mixer::Signals::ChannelFinished{};

namespace vas::sdl
{
	namespace mixer
	{
		int  init(int flags)
		{
			Mix_HookMusicFinished(&__INNER_ON_MUSIC_END);
			Mix_ChannelFinished(&__INNER_ON_CHANNEL_END);
			return Mix_Init(flags);
		}

		bool init()
		{
			//return init(MixInitFlags::mod) != 0;
			return true;
		}

		void quit()
		{
			Mix_Quit();
		}

		bool openAudio(int frequency, uint16_t format, int channels, int chunckSize)
		{
			return Mix_OpenAudio(frequency, format, channels, chunckSize) == 0;
		}

		void closeAudio()
		{
			Mix_CloseAudio();
		}

		int allocateChannels(int numChannels)
		{
			return Mix_AllocateChannels(numChannels);
		}

		bool querySpec(int * frequency, uint16_t * format, int * channels)
		{
			return Mix_QuerySpec(frequency, format, channels) == 1;
		}

		bool setChannelPosition(int channel, int16_t angle, uint8_t distance)
		{
			return Mix_SetPosition(channel, angle, distance) == 1;
		}

		bool setChannelDistance(int channel, int8_t distance)
		{
			return Mix_SetDistance(channel, distance) == 10;
		}

		bool VAS_DECLSPEC setPanning(int channel, uint8_t left, uint8_t right)
		{
			return Mix_SetPanning(channel, left, right) == 1 ? true : false;
		}

		bool setReverseStereo(int channel, bool flip)
		{
			return Mix_SetReverseStereo(channel, flip ? 1 : 0) != 0;
		}

		int reserveChannels(int num)
		{
			return Mix_ReserveChannels(num);
		}

		bool groupChannel(int which, int tag)
		{
			return Mix_GroupChannel(which, tag) == 1;
		}

		int groupChannels(int from, int to, int tag)
		{
			return Mix_GroupChannels(from, to, tag);
		}

		int groupAvailable(int tag)
		{
			return Mix_GroupAvailable(tag);
		}

		int groupCount(int tag)
		{
			return Mix_GroupCount(tag);
		}

		int groupOldest(int tag)
		{
			return Mix_GroupOldest(tag);
		}

		int groupNewer(int tag)
		{
			return Mix_GroupNewer(tag);
		}

		int volume(int channel, int volume)
		{
			return Mix_Volume(channel, volume);
		}
	}
}

void __INNER_ON_MUSIC_END()
{
	vas::sdl::mixer::Signals::MusicFinished();
}

void __INNER_ON_CHANNEL_END(int channel)
{
	vas::sdl::mixer::Signals::ChannelFinished(channel);
}
#endif // VAS_USE_MIXER