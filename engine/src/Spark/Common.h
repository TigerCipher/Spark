#ifndef SPARK_COMMON_H
#define SPARK_COMMON_H

#include <stdint.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef float f32;
typedef double f64;

typedef s8 b8;
typedef s32 b32;
typedef u8 byte;

#if defined(__clang__) || defined(__gcc__)
    #define STATIC_ASSERT _Static_assert
#else
    #define STATIC_ASSERT static_assert
#endif

#define TRUE 1
#define FALSE 0

// Platform detection
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
    #define SPLATFORM_WINDOWS 1
    #ifndef _WIN64
        #error "64-bit is required on Windows!"
    #endif
#elif defined(__linux__) || defined(__gnu_linux__)
    // Linux OS
    #define SPLATFORM_LINUX 1
    #if defined(__ANDROID__)
        #define SPLATFORM_ANDROID 1
    #endif
#elif defined(__unix__)
    // Catch anything not caught by the above.
    #define SPLATFORM_UNIX 1
#elif defined(_POSIX_VERSION)
    // Posix
    #define SPLATFORM_POSIX 1
#elif __APPLE__
    // Apple platforms
    #define SPLATFORM_APPLE 1
    #include <TargetConditionals.h>
    #if TARGET_IPHONE_SIMULATOR
        // iOS Simulator
        #define SPLATFORM_IOS 1
        #define SPLATFORM_IOS_SIMULATOR 1
    #elif TARGET_OS_IPHONE
        #define SPLATFORM_IOS 1
    // iOS device
    #elif TARGET_OS_MAC
    // Other kinds of Mac OS
    #else
        #error "Unknown Apple platform"
    #endif
#else
    #error "Unknown platform!"
#endif

#ifdef SEXPORT
    // Exports
    #ifdef _MSC_VER
        #define SAPI __declspec(dllexport)
    #else
        #define SAPI __attribute__((visibility("default")))
    #endif
#else
    // Imports
    #ifdef _MSC_VER
        #define SAPI __declspec(dllimport)
    #else
        #define SAPI
    #endif
#endif

#endif //SPARK_COMMON_H
