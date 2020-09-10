#pragma once
#include "Spark/Core/CoreTypes.h"
#include "CRC.h"
#include <map>
#include <string>
#include "sparkengine.api.gen.h"

namespace rflt
{
    
    struct SPARKENGINE_API Type
    {
        const char* name;
        size_t size;

        Type(const char* name, size_t size)
            : name(name), size(size)
            {}
        virtual ~Type() {}
        virtual std::string getFullName() const { return name; }
    };

    template <typename T>
    SPARKENGINE_API Type* GetPrimitiveType();

    
    struct SPARKENGINE_API DefaultTypeResolver
    {
        template<typename T> static char Func(decltype(&T::Reflection));
        template<typename T> static int Func(...);
        template<typename T>
        struct IsReflected
        {
            enum
            {
                value = (sizeof(Func<T>(nullptr)) == sizeof(char))
            };
        };

        template <typename T, typename std::enable_if<IsReflected<T>::value, int>::type = 0>
        static Type* Get()
        {
            return &T::Reflection;
        }
        
        template <typename T, typename std::enable_if<!IsReflected<T>::value, int>::type = 0>
        static Type* Get()
        {
            return GetPrimitiveType<T>();
        }
    };

    template<typename T>
    struct SPARKENGINE_API TypeResolver
    {
        static Type* Get()
        {
            return DefaultTypeResolver::Get<T>();
        }
    };
    
    // ---------------------------------------------------------
    struct SPARKENGINE_API TypeStruct : Type
    {
        struct Member
        {
            const char* name;
            size_t offset;
            Type* type;
        };
        std::vector<Member> members;

        TypeStruct(void(*init)(TypeStruct*))
            : Type(nullptr, 0)
        {
            init(this);
        }
        
    };

    // --------------------------------------------------------
    struct SPARKENGINE_API TypeInt : Type
    {
        TypeInt() : Type{"int", sizeof(int)} {}
    };
    template<>
    inline SPARKENGINE_API Type* GetPrimitiveType<int>()
    {
        static TypeInt type;
        return &type;
    }
    
    // --------------------------------------------------------
    struct SPARKENGINE_API TypeDouble : Type
    {
        TypeDouble() : Type{"double", sizeof(double)} {}
    };
    template<>
    inline SPARKENGINE_API Type* GetPrimitiveType<double>()
    {
        static TypeDouble type;
        return &type;
    }

    // --------------------------------------------------------
    struct SPARKENGINE_API TypeFloat : Type
    {
        TypeFloat() : Type{"float", sizeof(float)} {}
    };
    template<>
    inline SPARKENGINE_API Type* GetPrimitiveType<float>()
    {
        static TypeFloat type;
        return &type;
    }

} // namespace Spark

// Macro declaration --------------------------------------------------------------
#define REFLECT() \
    friend struct rflt::DefaultTypeResolver; \
    static rflt::TypeStruct Reflection; \
    static void InitReflection(rflt::TypeStruct*); \

#define REFLECTION_STRUCT_BEGIN(TYPE) \
    rflt::TypeStruct TYPE::Reflection{ TYPE::InitReflection }; \
    void TYPE::InitReflection(rflt::TypeStruct* typeStruct){ \
        using T = TYPE; \
        typeStruct->name = #TYPE; \
        typeStruct->size = sizeof(T); \
        typeStruct->members = {

#define REFLECTION_STRUCT_MEMBER(NAME) \
        {#NAME, offsetof(T, NAME), rflt::TypeResolver<decltype(T::NAME)>::Get() },
        
#define REFLECTION_STRUCT_END() \
        }; \
    }


