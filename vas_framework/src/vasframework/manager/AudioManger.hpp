#pragma once
#include "../VASConfig.hpp"

#ifdef VAS_USE_MIXER
#include <array>
#include <thread>
#include <string>
#include <chrono>
#include "../sdlcore/audio/MixCore.hpp"

namespace vas
{
	/** @addtogroup managers
		  @{
	*/
	/** @brief Managing multichannel audio with only one object.
		  
		  | Header | Namespace |
		  | : --- : | : --- : |
		  | vasframework/manager/AudioManager.hpp | vas |

		  AudioManager is a simple audio playback library that build on top of sdl_mixer. AudioManager are able to perform
		  lots of simple and common ways to manage audio playback and audio streaming. For more advance usage,
		  use sdl::mixer::Music and sdl::mixer::channel directly.
	*/
	class VAS_DECLSPEC AudioManger
	{ /** @} */
	public:
		/** @brief The default value of AudioManager */
		struct DefValue
		{
			static const float MAX_AUDIO; /**< Highest value of volume in AudioManager, default is SDL_mixer's 128*/
		};
		//enum class FadingState : uint8_t { none, bgm2me, me2bgm };

		/** Get the singletone instance of AudioManager
		*/
		static AudioManger& getInstance();

		/** Start streaming bgm from file.
			  @param file File name of the audio.
			  @param fadeInTime Duration for audio fading in.
			  @param loop Times for the audio stream repeat, if it is less than or equal to 0, the playback will be looping endless.
		*/
		void playBGM(const std::string& file, const std::chrono::milliseconds& fadeInTime = std::chrono::milliseconds(0), int loop = -1);
		/** Start BGS playback from file.
			  @param file File name of the audio.
			  @param fadeInTime Duration for audio fading in.
			  @param loop Times for the audio stream repeat, looping endlessly if less than or equal to 0.
		*/
		void playBGS(const std::string& file, const std::chrono::milliseconds& fadeInTime = std::chrono::milliseconds(0), int loop = 1);
		void playME(const std::string& file, const std::chrono::milliseconds& fadeInTime = std::chrono::milliseconds(0), int loop = 1);
		void playSE(const std::string& file, const std::chrono::milliseconds& fadeInTime = std::chrono::milliseconds(0), int loop = 1);

		void stopBGM(const std::chrono::milliseconds& fadeOutTime = std::chrono::milliseconds(0));
		void stopBGS(const std::chrono::milliseconds& fadeOutTime = std::chrono::milliseconds(0));
		void stopME(const std::chrono::milliseconds& fadeOutTime = std::chrono::milliseconds(0));
		void stopSE(const std::chrono::milliseconds& fadeOutTime = std::chrono::milliseconds(0));

		void pauseBGM(const std::chrono::milliseconds& fadeOutTime = std::chrono::milliseconds(0));

		void resumeBGM(const std::chrono::milliseconds& fadeInTime = std::chrono::milliseconds(0));

		sdl::mixer::Music BGM();
		sdl::mixer::Chunk BGS();
		sdl::mixer::Chunk ME();
		sdl::mixer::Chunk SE();

		float getBGMVolume();
		float getBGSVolume();
		float getMEVolume();
		float getSEVolume();

		void setBGMVolume(float value);
		void setBGSVolume(float value);
		void setMEVolume(float value);
		void setSEVolume(float value);

		void clear();
		void tick();

		/*std::array<float, 1>& getLastVolume();
		std::array<float, 4>& getVolume();*/
	private:
		AudioManger();
		~AudioManger();

		std::array<std::string, 4> lastFileName;
		std::array<float, 4> volume{ 128.0f, 128.0f, 128.0f, 128.0f };
		std::array<float, 1> lastVolume{ 0 };

		sdl::mixer::Music bgm;
		sdl::mixer::Chunk bgs{ 0 };
		sdl::mixer::Chunk me{ 1 };
		sdl::mixer::Chunk se{ 2 };

		//std::thread fadeWorker;
	};
}
#endif // VAS_USE_MIXER
