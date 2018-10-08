/** @addtogroup graphics
	  @{
*/
/** @defgroup scene Scene
	  
	  @brief The Scene is the stage of the elements that preform their story.
*/

/** @addtogroup scene
	  @{
*/

/** @defgroup render_assistance Render Assistance

	  @brief A helper feature of Scene's children to manage all vas::DrawAble object

	  Defined at vas::Scene, Render Assistance is the main instance of vas::Layers provided by the scene object to help to
	  handle DrawAble object.

	  The macro #CallRenderAssistance must be called before using RenderAssistance to draw anything.

	  @note Don't forget the semicolon ';' must be added after the call of all macro.
	  @{
*/
/** Return the main instance of RenderAssistance
	  
	  Defined in: vasframework/graphics/scene/Scene.hpp
*/
#define RenderAssistance
/** Call RenderAssistance to work
	  
	  Defined in: vasframework/graphics/scene/Scene.hpp
*/
#define CallRenderAssistance
/** Send back RenderAssistance
	  
	  Defined in: vasframework/graphics/scene/Scene.hpp
*/
#define SendBackRenderAssistance
/** Check if RenderAssistance is allowed to render
	  
	  Defined in: vasframework/graphics/scene/Scene.hpp
*/
#define IsRenderAssistanceEnabled
/** Check if RenderAssistance is called
	  
	  Defined in: vasframework/graphics/scene/Scene.hpp
*/
#define IsRenderAssistanceCalled
/** Check if RenderAssistance is ready to work
	  
	  Defined in: vasframework/graphics/scene/Scene.hpp
*/
#define IsRenderAssistanceReady
/** Allow RenderAssistance to render it's contents to scene
	  
	  Defined in: vasframework/graphics/scene/Scene.hpp
*/
#define EnableRenderAssistance
/** Not allow RenderAssistance to render it's contents to scene
	  
	  Defined in: vasframework/graphics/scene/Scene.hpp
*/
#define DisableRenderAssistance
/** @} */

/** @} */
/** @} */