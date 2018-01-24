#pragma once
#include <SDL.h>
#include "../VASConfig.hpp"
#include "boolean_cast.hpp"

namespace sdl
{
	namespace rwops
	{
		struct VAS_DECLSPEC Type
		{
			static const uint32_t unknow; /* Unknown stream type */
			static const uint32_t winFile; /* Win32 file */
			static const uint32_t stdFile; /* Stdio file */
			static const uint32_t jniFile; /* Android asset */
			static const uint32_t memory; /* Memory stream */
			static const uint32_t readOnlyMemory; /* Read-Only memory stream */
		};

		struct VAS_DECLSPEC Whence
		{
			static const int set; /**< Seek from the beginning of data */
			static const int cur; /**< Seek relative to current read point */
			static const int end; /**< Seek relative to the end of data */
		};

		using RWops = SDL_RWops;

		/**
		*  Return the size of the file in this rwops, or -1 if unknown
		*/
		inline int64_t size(RWops* instance) { return SDL_RWsize(instance); };

		/**
		*  Seek to \c offset relative to \c whence, one of stdio's whence values:
		*  RW_SEEK_SET, RW_SEEK_CUR, RW_SEEK_END
		*
		*  \return the final offset in the data stream, or -1 on error.
		*/
		inline int64_t seek(RWops* instance, int64_t offset, int whence) { return SDL_RWseek(instance, offset, whence); };
		inline int64_t tell(RWops* instance, int64_t offset) { return sdl::rwops::seek(instance, 0, sdl::rwops::Whence::cur); };

		/**
		*  Read up to \c maxnum objects each of size \c size from the data
		*  stream to the area pointed at by \c ptr.
		*
		*  \return the number of objects read, or 0 at error or end of file.
		*/
		inline size_t read(RWops* instance, void* ptr, size_t size, size_t maxnum) { return SDL_RWread(instance, ptr, size, maxnum); };

		/**
		*  Write exactly \c num objects each of size \c size from the area
		*  pointed at by \c ptr to data stream.
		*
		*  \return the number of objects written, or 0 at error or end of file.
		*/
		inline size_t write(RWops* instance, const void* ptr, size_t size, size_t num) { return SDL_RWwrite(instance, ptr, size, num); };

		/**
		*  Close and free an allocated SDL_RWops structure.
		*
		*  \return 0 if successful or -1 on write error when flushing data.
		*/
		void VAS_DECLSPEC close(RWops* instance);

		inline RWops* fromFile(const std::string& name, const std::string& mode = u8"rb")
		{
			return SDL_RWFromFile(name.c_str(), mode.c_str());
		}

		inline RWops* fromFP(void* fp, bool autoClose)
		{
			return SDL_RWFromFP(fp, boolean_cast(autoClose));
		}

		inline RWops* fromMemory(void* data, int size)
		{
			return SDL_RWFromMem(data, size);
		}

		inline RWops* fromMemory(const void* data, int size)
		{
			return SDL_RWFromConstMem(data, size);
		}

		inline RWops* allocateRWops()
		{
			return SDL_AllocRW();
		}

		inline void freeRWops(RWops* area)
		{
			SDL_FreeRW(area);
		}

		/**
		*  \name Read endian functions
		*
		*  Read an item of the specified endianness and return in native format.
		*/
		/* @{ */
		inline uint8_t readU8(RWops * src)
		{
			return SDL_ReadU8(src);
		}
		inline uint16_t readLE16(RWops * src)
		{
			return SDL_ReadLE16(src);
		}
		inline uint16_t readBE16(RWops * src)
		{
			return SDL_ReadBE16(src);
		}
		inline uint32_t readLE32(RWops * src)
		{
			return SDL_ReadLE32(src);
		}
		inline uint32_t readBE32(RWops * src)
		{
			return SDL_ReadBE32(src);
		}
		inline uint64_t readLE64(RWops * src)
		{
			return SDL_ReadLE64(src);
		}
		inline uint64_t readBE64(RWops * src)
		{
			return SDL_ReadLE64(src);
		}
		/* @} *//* Read endian functions */

		/**
		*  \name Write endian functions
		*
		*  Write an item of native format to the specified endianness.
		*/
		/* @{ */
		inline size_t writeU8(RWops * dst, uint8_t value)
		{
			return SDL_WriteU8(dst, value);
		}
		inline size_t writeLE16(RWops * dst, uint16_t value)
		{
			return SDL_WriteLE16(dst, value);
		}
		inline size_t writeBE16(RWops * dst, uint16_t value)
		{
			return SDL_WriteBE16(dst, value);
		}
		inline size_t writeLE32(RWops * dst, uint32_t value)
		{
			return SDL_WriteLE32(dst, value);
		}
		inline size_t writeBE32(RWops * dst, uint32_t value)
		{
			return SDL_WriteBE32(dst, value);
		}
		inline size_t writeLE64(RWops * dst, uint64_t value)
		{
			return SDL_WriteLE64(dst, value);
		}
		inline size_t writeBE64(RWops * dst, uint64_t value)
		{
			return SDL_WriteBE64(dst, value);
		}
		/* @} *//* Write endian functions */
	}
}