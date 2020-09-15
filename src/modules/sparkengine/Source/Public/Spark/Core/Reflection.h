#pragma once
#include "Spark/Core/CoreTypes.h"
#include "CRC.h"
#include <map>
#include <string>
#include "sparkengine.api.gen.h"

namespace Spark
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

    struct Member
    {
        const char* name;
        size_t offset;
        Type* type;
        
        void* GetPtr(void* object)
        {
            return (char*)object + offset;
        }
    };

    template <typename T>
    SPARKENGINE_API Type* GetPrimitiveType();

    
    struct SPARKENGINE_API DefaultTypeResolver
    {
        static std::map<std::string, Type*> DB;
        
        template<typename T> static char Func(decltype(&T::StaticType));
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
            return &T::StaticType;
        }
        
        template <typename T, typename std::enable_if<!IsReflected<T>::value, int>::type = 0>
        static Type* Get()
        {
            return GetPrimitiveType<T>();
        }

        static Type* Get(const char* name)
        {
            auto it = DB.find(name);            
            if(it != DB.end())
            {
                return it->second;
            }
            else
            {
                CORE_ASSERT(false, "Type does not exist!");
                return nullptr;
            }
        }
    };

    class TypeResolver
    {
    public:
        template<typename T>
        static Type* Get()
        {
            return DefaultTypeResolver::Get<T>();
        }
        
        static Type* Get(const char* name)
        {
            return DefaultTypeResolver::Get(name);
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
    
    // ---------------------------------------------------------
    
    template<typename TYPE>
    inline SPARKENGINE_API void ConstructObject(void* object)
    {
        new (object) TYPE;
    }
    
    template<typename TYPE>
    inline SPARKENGINE_API void DestroyObject(void* object)
    {
        ((TYPE*)object)->TYPE::~TYPE();
    }
    
    struct SPARKENGINE_API TypeClass : Type
    {
        std::vector<Member> members;
        std::function<void(void*)> constructor;
        std::function<void(void*)> destructor;

        TypeClass(void(*init)(TypeClass*))
            : Type(nullptr, 0), members(std::vector<Member>())
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
    
    // --------------------------------------------------------
    // struct SPARKENGINE_API Vec3Float : Type
    // {
    //     TypeFloat() : Type{"float", sizeof(float)} {}
    // };
    // template<>
    // inline SPARKENGINE_API Type* GetPrimitiveType<float>()
    // {
    //     static TypeFloat type;
    //     return &type;
    // }



} // namespace Spark

// Macro declaration --------------------------------------------------------------
#define REFLECT_STRUCT() \
        friend struct Spark::DefaultTypeResolver; \
        static Spark::TypeStruct StaticType; \
        static void InitReflection(Spark::TypeStruct*); \

#define REFLECT_BASE_CLASS() \
        friend struct Spark::DefaultTypeResolver; \
        public: static Spark::TypeClass StaticType; \
        private: static void InitReflection(Spark::TypeClass*); \
        public: virtual Spark::TypeClass& GetDerivedType() { return StaticType; }; \

#define REFLECT_CLASS() \
        friend struct Spark::DefaultTypeResolver; \
        public: static Spark::TypeClass StaticType; \
        private: static void InitReflection(Spark::TypeClass*); \
        public: virtual Spark::TypeClass& GetDerivedType() override { return StaticType; }; \

#define REFLECTION_STRUCT_BEGIN(TYPE) \
    Spark::TypeStruct TYPE::StaticType{ TYPE::InitReflection }; \
    void TYPE::InitReflection(Spark::TypeStruct* typeStruct){ \
        DefaultTypeResolver::DB.insert({#TYPE, typeClass}); \
        using T = TYPE; \
        typeStruct->name = #TYPE; \
        typeStruct->size = sizeof(T); \
        typeStruct->members = {

#define REFLECTION_CLASS_BEGIN(TYPE) \
    Spark::TypeClass TYPE::StaticType{ TYPE::InitReflection }; \
    void TYPE::InitReflection(Spark::TypeClass* typeClass){ \
        using T = TYPE; \
        DefaultTypeResolver::DB.insert({#TYPE, typeClass}); \
        typeClass->name = #TYPE; \
        typeClass->size = sizeof(T); \
        typeClass->constructor =ConstructObject<T>; \
        typeClass->destructor = DestroyObject<T>; \
        typeClass->members.empty(); \
        typeClass->members = { \

#define REFLECTION_STRUCT_MEMBER(NAME) \
        {#NAME, offsetof(T, NAME), Spark::TypeResolver::Get<decltype(T::NAME)>() },
        
#define REFLECTION_STRUCT_END() \
        }; \
    }

#define REFLECTION_CLASS_MEMBER(NAME) REFLECTION_STRUCT_MEMBER(NAME)
#define REFLECTION_CLASS_END() REFLECTION_STRUCT_END()


