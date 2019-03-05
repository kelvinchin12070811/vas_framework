#pragma once
#include <map>
#include <optional>
#include <string>
#include "../sdlcore/ttf/TTFCore.hpp"
#include "../VASConfig.hpp"

#ifdef VAS_USE_TTF
namespace vas
{
	/** @addtogroup managers
		  @{
	*/
	/** @brief Basic cache implementation for fonts.
	
		  FontCacheManager is a manager that cache the used font and try to reduce memory allocation.
	*/
	class FontCacheManager
	{ /** @} */
	public:
		static FontCacheManager& getInstance(); /**< Get singletone instance of FontCacheManager. */

		/** Determine if a font is cached.
			  @param id Id of the font.
			  @param size Size variant of the font.
			  @return true if font is cached.
		*/
		bool hasFont(const std::string& id, uint32_t size);
		/** Load and cache a new font if not esixt.
			  @param id Id of the font, also file name of the ttf font file.
			  @param size Size of the font.
			  @return true if success.
		*/
		bool insertFont(const std::string& id, uint32_t size);
		/** Cached a esixted font.
			  @param id Id of the font.
			  @param size Size of the font.
			  @param font Font to cache.
			  @return true if success.
		*/
		bool insertFont(const std::string& id, uint32_t size, sdl::ttf::Font font);
		/** Retrive a font from cache.
			  @param id Id of the font.
			  @param size Size of the font.
			  @return std::nullopt if font not cached.
		*/
		std::optional<sdl::ttf::Font> getFont(const std::string& id, uint32_t size);
		/** Clear a specific font.
			  @param id Id of the font.
			  @param size size of the font.
		*/
		void clearFont(const std::string& id, uint32_t size);
		void clearFont(); /**< Clear all font cache. */
		bool isFontCacheEmpty(); /**< Determine if cache is empty. */
		size_t fontCacheSize(); /**< Get the number of fonts cached. */
	private:
		std::map<std::pair<std::string, uint32_t>, sdl::ttf::Font> fonts;
	};
}
#endif