//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
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
		/** @addtogroup sdl_mixer
			  @{
		*/
		/** @brief The internal format for a music chunk. */
		class VAS_DECLSPEC Music
		{ /** @} */
		public:
			Music(); /**< Create empty Music. */
			Music(const std::string& file); /**< Load Music from file. */

			/** Reference to a Mix_Music.
				  @param other Instance of raw component.
				  @param owner Determine if this instance is an owner of @p other.
			*/
			explicit Music(Mix_Music* other, bool owner = false);

			MusicType getMusicType(); /**< Get the music format of the music. */

			void load(const std::string& file); /**< Load music from file. */
			void loadRaw(sdl::rwops::RWops* src, bool freeSrc = true); /**< Load music from memory. */
			void loadRawTyped(sdl::rwops::RWops* src, MusicType type, bool freeSrc = true); /**< Load music from memory by type. */

			void fadeIn(int duration, int loops = -1); /**< fade in music with milliseconds. loop if @p loops < 0. */
			void fadeInAt(double position, int duration, int loops = -1); /**< Fade in music with miliseconds at position. loop if @p loops < 0 */
			void play(int loops = -1); /**< play the music. loop if @p loops < 0. */

			static void fadeOut(int duration); /**< Fade out in milliseconds. */
			static Fading fading(); /**< Get fading state. */
			static void pause(); /**< Pause the music. */
			static void resume(); /**< Resume the music. */
			static void rewind(); /**< Rewind music. */
			static bool isPlaying(); /**< Check if music is playing. */
			static bool isPaused(); /**< Check if music is paused. */
			static void stop(); /**< Stop the music. */

			/** Set the current position in the music stream.
			This returns 0 if successful, or -1 if it failed or isn't implemented.
			This function is only implemented for MOD music formats (set pattern
			order number) and for OGG, FLAC, MP3_MAD, and MODPLUG music (set
			position in seconds), at the moment.
			*/
			static bool setPosition(double position);

			/** Set the volume in the range of 0-128 of a specific channel or chunk.
			If the specified channel is -1, set volume for all channels.
			Returns the original volume.
			If the specified volume is -1, just return the current volume.
			*/
			static int volume(int volume);

			void destroy(); /**< Destroy instance. */
			bool isNull(); /**< Determine if instance is nullcomponent. */

			/** @name Overloaded operators
				  @{
			*/
			operator Mix_Music*(); /**< Cast to raw component. */
			Music& operator=(NullComponent_t); /**< Destroy instance by assigning it to nullcomponent. */

			bool operator==(const Music& rhs); /**< Compare if two instances are equal. */
			bool operator==(NullComponent_t); /**< Determine if instance is nullcomponent. */
			bool operator!=(const Music& rhs); /**< Compare if two instances are not equal. */
			bool operator!=(NullComponent_t); /**< Determine if instance is not nullcomponent. */
			/** @} */
		private:
			std::shared_ptr<Mix_Music> componentInstance;
		};
	}
}
#endif // VAS_USE_MIXER
