/*! \defgroup macro All Macros in this library*/

/*! \brief All macros that used in the library
	 
	 This page listed all of the macros that definde and used in this library.
*/

/*! \addtogroup macro
		@{
*/

/*! Dll export symbol used in the class. If `#VAS_GEN_DLL` is defined, it will have a value of `__declspec(__dllexport)` which
	 is Microsoft specific dll export symbol.

	 Defined in: vasframework/VASConfig.hpp
*/
#define VAS_DECLSPEC

/*! Class loader that load the main class, only avaliable if `#VAS_SDL_ENTRY` is not defined.
	 This macro generate main function accroding to the settings.
	 
	 Defined in: vasframework/base/Base.hpp
*/
#define VAS_CLASSLOADER_LOAD(launcher)
/*! @} */