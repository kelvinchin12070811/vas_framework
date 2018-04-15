#pragma once
#include "../../VASConfig.hpp"

#ifdef VAS_USE_MIXER
#include <boost/signals2.hpp>
#include <SDL_mixer.h>
#include "Flags.hpp"
#include "Music.hpp"
#include "Chunk.hpp"

namespace sdl
{
	namespace mixer
	{
		class VAS_DECLSPEC Signals
		{
		public:
			static boost::signals2::signal<void()> onMusicFinished;
			static boost::signals2::signal<void(int)> onChannelFinished;
		};

		VAS_DECLSPEC int init(int flags);
		VAS_DECLSPEC bool init();
		VAS_DECLSPEC void quit();
		VAS_DECLSPEC bool openAudio(int frequency = DefaultValues::frequency, uint16_t format = DefaultValues::format,
			int channels = DefaultValues::channelCount, int chunckSize = DefaultValues::chunkSize);
		VAS_DECLSPEC void closeAudio();
		VAS_DECLSPEC int allocateChannels(int numChannels);
		VAS_DECLSPEC bool querySpec(int *frequency, uint16_t *format, int* channels);
		VAS_DECLSPEC bool setChannelPosition(int channel, int16_t angle, uint8_t distance);
		VAS_DECLSPEC bool setChannelDistance(int channel, int8_t distance);

		/* Set the panning of a channel. The left and right channels are specified
		*  as integers between 0 and 255, quietest to loudest, respectively.
		*
		* Technically, this is just individual volume control for a sample with
		*  two (stereo) channels, so it can be used for more than just panning.
		*  If you want real panning, call it like this:
		*
		*   Mix_SetPanning(channel, left, 255 - left);
		*
		* ...which isn't so hard.
		*
		* Setting (channel) to MIX_CHANNEL_POST registers this as a posteffect, and
		*  the panning will be done to the final mixed stream before passing it on
		*  to the audio device.
		*
		* This uses the Mix_RegisterEffect() API internally, and returns without
		*  registering the effect function if the audio device is not configured
		*  for stereo output. Setting both (left) and (right) to 255 causes this
		*  effect to be unregistered, since that is the data's normal state.
		*
		* returns zero if error (no such channel or Mix_RegisterEffect() fails),
		*  nonzero if panning effect enabled. Note that an audio device in mono
		*  mode is a no-op, but this call will return successful in that case.
		*  Error messages can be retrieved from Mix_GetError().
		*/
		VAS_DECLSPEC bool setPanning(int channel, uint8_t left, uint8_t right);

		/* Causes a channel to reverse its stereo. This is handy if the user has his
		*  speakers hooked up backwards, or you would like to have a minor bit of
		*  psychedelia in your sound code.  :)  Calling this function with (flip)
		*  set to non-zero reverses the chunks's usual channels. If (flip) is zero,
		*  the effect is unregistered.
		*
		* This uses the Mix_RegisterEffect() API internally, and thus is probably
		*  more CPU intensive than having the user just plug in his speakers
		*  correctly. Mix_SetReverseStereo() returns without registering the effect
		*  function if the audio device is not configured for stereo output.
		*
		* If you specify MIX_CHANNEL_POST for (channel), then this the effect is used
		*  on the final mixed stream before sending it on to the audio device (a
		*  posteffect).
		*
		* returns zero if error (no such channel or Mix_RegisterEffect() fails),
		*  nonzero if reversing effect is enabled. Note that an audio device in mono
		*  mode is a no-op, but this call will return successful in that case.
		*  Error messages can be retrieved from Mix_GetError().
		*/
		VAS_DECLSPEC bool setReverseStereo(int channel, bool flip);

		/* Reserve the first channels (0 -> n-1) for the application, i.e. don't allocate
		them dynamically to the next sample if requested with a -1 value below.
		Returns the number of reserved channels.
		*/
		VAS_DECLSPEC int reserveChannels(int num);

		/* Attach a tag to a channel. A tag can be assigned to several mixer
		channels, to form groups of channels.
		If 'tag' is -1, the tag is removed (actually -1 is the tag used to
		represent the group of all the channels).
		Returns true if everything was OK.
		*/
		VAS_DECLSPEC bool groupChannel(int which, int tag);
		VAS_DECLSPEC int groupChannels(int from, int to, int tag);

		/* Finds the first available channel in a group of channels,
		returning -1 if none are available.
		*/
		VAS_DECLSPEC int groupAvailable(int tag);

		/* Returns the number of channels in a group. This is also a subtle
		way to get the total number of channels when 'tag' is -1
		*/
		VAS_DECLSPEC int groupCount(int tag);

		/* Finds the "oldest" sample playing in a group of channels */
		VAS_DECLSPEC int groupOldest(int tag);

		/* Finds the "most recent" (i.e. last) sample playing in a group of channels */
		VAS_DECLSPEC int groupNewer(int tag);

		/* Set the volume in the range of 0-128 of a specific channel or chunk.
		If the specified channel is -1, set volume for all channels.
		Returns the original volume.
		If the specified volume is -1, just return the current volume.
		*/
		VAS_DECLSPEC int volume(int channel, int volume);
	}
}

void __INNER_ON_MUSIC_END();
void __INNER_ON_CHANNEL_END(int channel);
#endif // VAS_USE_MIXER