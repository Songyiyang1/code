/*
Must be included on any file to be compiled (i.e., on each bla_test.c) as the very first thing,
before any standard library imports!
*/

/*
This file ensures that you can compile without warnings on 32-bit windows. And when using clang on windows.
Because we sure love adding clumsy workarounds so that people can refuse to use the WSL =D 
*/

#ifdef _WIN32
    #if defined(__MINGW32__) || defined(__MINGW64__)
        #ifndef __USE_MINGW_ANSI_STDIO
        #define __USE_MINGW_ANSI_STDIO 1
        #endif
    #endif
    #ifdef __clang__
        #ifndef _CRT_SECURE_NO_WARNINGS
        #define _CRT_SECURE_NO_WARNINGS
        #endif
    #endif
#endif

