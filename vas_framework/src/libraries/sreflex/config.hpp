#pragma once

#define SREFLEX_CONFIG_GENDLL

#ifdef SREFLEX_CONFIG_GENDLL
#define SREFLEX_DLLEXPORT __declspec(dllexport)
#else
#define SRESREFLEX_DLLEXPORT
#endif // !SREFLEX_CONFIG_GENDLL