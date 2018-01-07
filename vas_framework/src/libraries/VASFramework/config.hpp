#pragma once

//#define VAS_FRAMEWORK_CONFIG_GENDLL

/*
Note! The following library need to toggle settings by them self because they are seperated with core framework
 - Simple Reflection Library (sreflex)
 - vas::TextTools (utility/TextTools)
 - vas::Boolean (containers/Boolean)
*/

#ifdef VAS_FRAMEWORK_CONFIG_GENDLL
#define VAS_FRAMEWORK_DLLEXPORT __declspec(dllexport)
#else
#define VAS_FRAMEWORK_DLLEXPORT
#endif // !VAS_FRAMEWORK_CONFIG_GENDLL