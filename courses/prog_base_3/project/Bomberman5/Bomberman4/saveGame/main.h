#ifndef __MAIN_H__
#define __MAIN_H__

#include <windows.h>


#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif


#ifdef __cplusplus
extern "C"
{
#endif

#include <sqlite3.h>

void DLL_EXPORT pl_insert(char *name, int lvl, int life, double speed, int boomb);

#ifdef __cplusplus
}
#endif

#endif // __MAIN_H__
