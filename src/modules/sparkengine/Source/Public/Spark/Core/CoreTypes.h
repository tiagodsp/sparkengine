#pragma once

#include <type_traits> 
#include "Spark/Core/Log.h"
#include <memory>

#ifdef SPARKENGINE_ENABLE_ASSERTS
    #define ASSERT(x, ...) { if(!(x)) {LOGF(Core, "Assertion Failed: {0}", __VA_ARGS__); __debugbreak();} }
    #define CORE_ASSERT(x, ...) { if(!(x)) {CORE_LOGF("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();} }
#else
    #define ASSERT(x, ...) 
    #define CORE_ASSERT(x, ...)
#endif


#define BIT(x) (1 << x)

//typedef unsigned char       BYTE;
//typedef unsigned short      WORD;
//typedef unsigned int        DWORD;
//typedef int                 BOOL;

typedef signed char         int8_t;
typedef signed short int    int16_t;
typedef signed int          int32_t;
typedef signed long long    int64_t;

typedef unsigned char       uint8_t;
typedef unsigned short int  uint16_t;
typedef unsigned int        uint32_t;
typedef unsigned long long  uint64_t;

typedef int8_t              int8;
typedef int16_t             int16;
typedef int32_t             int32;
typedef int64_t             int64;

typedef uint8_t             uint8;
typedef uint16_t            uint16;
typedef uint32_t            uint32;
typedef uint64_t            uint64;

namespace Spark
{

    template<typename Enum>
    struct EnableBitMaskOperators
    {
        static const bool enable = false;
    };

    #define ENUM_ENABLE_BITMASK_OPERATORS(x)        \
    template<>                                      \
    struct EnableBitMaskOperators<x>                \
    {                                               \
        static const bool enable = true;            \
    };

    template<typename Enum>
    typename std::enable_if_t<EnableBitMaskOperators<Enum>::enable, Enum>
    operator |(Enum lhs, Enum rhs)  
    {
        using underlying = typename std::underlying_type<Enum>::type;
        return static_cast<Enum> (
            static_cast<underlying>(lhs) |
            static_cast<underlying>(rhs)
        );
    }
    
    template<typename Enum>
    typename std::enable_if_t<EnableBitMaskOperators<Enum>::enable, Enum>
    operator &(Enum lhs, Enum rhs)  
    {
        using underlying = typename std::underlying_type<Enum>::type;
        return static_cast<Enum> (
            static_cast<underlying>(lhs) &
            static_cast<underlying>(rhs)
        );
    }

    template<typename Enum>
    typename std::enable_if_t<EnableBitMaskOperators<Enum>::enable, Enum>
    operator ^(Enum lhs, Enum rhs)  
    {
        using underlying = typename std::underlying_type<Enum>::type;
        return static_cast<Enum> (
            static_cast<underlying>(lhs) ^
            static_cast<underlying>(rhs)
        );
    }

    template<typename Enum>
    typename std::enable_if_t<EnableBitMaskOperators<Enum>::enable, Enum>
    operator ~(Enum rhs)  
    {
        using underlying = typename std::underlying_type<Enum>::type;
        return static_cast<Enum> (
            static_cast<underlying>(rhs)
        );
    }

    template<typename Enum>
    typename std::enable_if_t<EnableBitMaskOperators<Enum>::enable, Enum>&
    operator |=(Enum &lhs, Enum rhs)  
    {
        using underlying = typename std::underlying_type<Enum>::type;
        lhs = static_cast<Enum> (
            static_cast<underlying>(lhs) |
            static_cast<underlying>(rhs)           
        );

        return lhs;
    }

    template<typename Enum>
    typename std::enable_if_t<EnableBitMaskOperators<Enum>::enable, Enum>&
    operator &=(Enum &lhs, Enum rhs)  
    {
        using underlying = typename std::underlying_type<Enum>::type;
        lhs = static_cast<Enum> (
            static_cast<underlying>(lhs) &
            static_cast<underlying>(rhs)           
        );

        return lhs;
    }

    template<typename Enum>
    typename std::enable_if_t<EnableBitMaskOperators<Enum>::enable, Enum>&
    operator ^=(Enum &lhs, Enum rhs)  
    {
        using underlying = typename std::underlying_type<Enum>::type;
        lhs = static_cast<Enum> (
            static_cast<underlying>(lhs) ^
            static_cast<underlying>(rhs)           
        );

        return lhs;
    }


    template<typename T>
    using Scope = std::unique_ptr<T>;

    template<typename T>
    using Ref = std::shared_ptr<T>;

}