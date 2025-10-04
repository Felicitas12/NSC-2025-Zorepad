#pragma once

#if defined(_WIN32)
    #if defined(ENGINE_SHARED)   // когда собираем DLL
        #if defined(ENGINE_BUILD)
            #define ENGINE_API __declspec(dllexport)
        #else
            #define ENGINE_API __declspec(dllimport)
        #endif
    #else                        // когда собираем STATIC
        #define ENGINE_API
    #endif
#else
    #define ENGINE_API
#endif
