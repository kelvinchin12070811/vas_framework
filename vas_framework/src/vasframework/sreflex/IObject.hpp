#pragma once
#include "../VASConfig.hpp"

/*
	Interface for sreflex libary's instance
*/
namespace vas
{
	namespace sreflex
	{
		/** @addtogroup sreflex
		@{ */
		/*! \brief The interface that all reflectable object need to inherit.

			 | Header | Namespace |
			 | : --- : | : --- : |
			 | vasframework/sreflex/IObject.hpp | vas::sreflex |

			 IObject is the interface that all object that need to support reflection to inherit.
		*/
		class IObject
		{
		public:
			IObject() {}
			virtual ~IObject() = 0 {}
		};
		/*! @} */
	}
}