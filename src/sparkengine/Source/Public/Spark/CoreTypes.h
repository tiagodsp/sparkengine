#pragma once

#ifdef SPARKENGINE_ENABLE_ASSERTS
    #define S_ASSERT(x, ...) { if(!(x)) {S_LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();} }
    #define SC_ASSERT(x, ...) { if(!(x)) {SC_LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();} }
#else
    #define S_ASSERT(x, ...) 
    #define SC_ASSERT(x, ...)
#endif


#define BIT(x) (1 << x)

typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef unsigned int        DWORD;
typedef int                 BOOL;

typedef signed char         int8_t;
typedef signed short int    int16_t;
typedef signed int          int32_t;
//typedef signed long long    int64_t;

typedef unsigned char       uint8_t;
typedef unsigned short int  uint16_t;
typedef unsigned int        uint32_t;
//typedef unsigned long long  uint64_t;

typedef int8_t              int8;
typedef int16_t             int16;
typedef int32_t             int32;
//typedef int64_t             int64;

typedef uint8_t             uint8;
typedef uint16_t            uint16;
typedef uint32_t            uint32;
//typedef uint64_t            uint64;