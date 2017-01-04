#ifndef _SINGLETON
#define _SINGLETON

#ifdef WIN32
#ifndef DLL_EXPORT
#define DLL_EXPORT __declspec(dllexport)
#endif
#endif

#ifdef WIN32
DLL_EXPORT struct Math
#else
struct Math
#endif
{
};

#endif

