/**
 * @addtogroup util
 * @{
 */
/**
 * @defgroup txt_tool Text Tools
 * @brief UTF-8 console stream IO.
 * 
 * TextTools proide tools that read and write to console with UTF-8 encoding. This class is also designed to
 * be protable. The macro #VAS_WINDOWS_MODE must not defined for non windows platform to work.
 * 	  
 * Since the windows use UTF-16 as unicode strings, the tools must convert all UTF-8 strings to UTF-16 before
 * calling all native IO function. This is the reason that the macro #VAS_WINDOWS_MODE must be defined on
 * Windows platform. However, this macro must not defined on other not Windows operating system since most of
 * them support UTF-8 natively.
 */

/**
 * @addtogroup txt_tool
 * @{
 */

/**
 * @name Compile time configuratins
 * @{
 */
#define VAS_TEXTTOOLS_INDIE_MODE /**< Define this macro to make TextTools work indipendently. Default is not
																	  *defined. */
#define VAS_WINDOWS_MODE /**< Make the tools platform specifily to windows only. This macro must be defined in
														  * order that it will work on windows. On non windows platform, this must be undefend.
														  * Default is defined. */
/** @} */
/** @} */

/**
 * @addtogroup txt_tool
 * @{
 */
/**
 * @defgroup txt_helper Helper stream
 * @brief The helper stream is the alternative to std's cin, cout and ceer.
 * 
 * The helper stream use the advantage of operator
 * overloading to provide std's console IO stream feature. The helper stream currently only support output
 * (operator<<) and input (operator>>). For other function, use the member function getWrapedStream() to get
 * the native IO stream on user's platform.
 * 
 * - vas::Cout (include <vasframework/util/TextTools.hpp>)
 * - vas::Ceer (include <vasframework/util/TextTools.hpp>)
 * - vas::Cin (include <vasframework/util/TextTools.hpp>)
 * 
 * @note The user must create an instance of the helper class with rvalue. This is because it will only dump
 * the stream to the native stream when its' destructor get called.
 * 
 * For examples of TextTools helper class, refer [Helper stream examples page](helper_stream_exp.html).
 * @{
 */

/**
 * @name Common member functions
 * @{
 */

/** Get the native stream type of the helper class. */
inline static STREAM_TYPE& getWrapedStream();
/** Set manipulator to the stream, only work on ostream such as Cout and Ceer. */
STREAM_TYPE& operator<<(std::ostream& (*manipulator)(std::ostream& o));
/** Output to stream, only work on ostream such as Cout and Ceer. */
STREAM_TYPE& operator<<(const Type& rhs);
/** Input from stream, only work on istream such as Cin. */
STREAM_TYPE& operator>>(Type& rhs);
/** Input string from stream, only work on istream such as Cin. */
STREAM_TYPE& operator>>(std::string& rhs);

/** Get the gobla internal buffer for ostream type (Cout & Ceer). */
static std::stringstream& getBuffer();

/** @} */
/** @} */
/** @} */
/** @} */