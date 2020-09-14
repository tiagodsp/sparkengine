#pragma once

#include "Spark/Core/Reflection.h"
#include "sparkengine.api.gen.h"

namespace Spark
{
    class SPARKENGINE_API Object
    {
        REFLECT_BASE_CLASS()
    public:
        Object() {}
        virtual ~Object() {}
        //virtual Spark::TypeClass& GetStaticType();
        /** Called by a future Hot-Reload system.*/
        virtual void OnChanged() {};
    };


    SPARKENGINE_API Object* NewObject(const char* typeName);
    SPARKENGINE_API Object* NewObject(const char* name, const char* typeName);
    SPARKENGINE_API Object* NewObject(const char* name, Type* type);
    
    template<typename TYPE>
    TYPE* CreateObject(const char* name)
    {
        return dynamic_cast<TYPE*>(NewObject(name, TypeResolver<TYPE>::Get()));
    }
} // namespace Spark
