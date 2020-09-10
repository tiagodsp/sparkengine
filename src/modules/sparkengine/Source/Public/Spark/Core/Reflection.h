#pragma once
#include "Spark/Core/CoreTypes.h"
#include "CRC.h"
#include <map>
namespace rflt
{
    
    // template<typename TYPE>
    // const char* GetTypeName()
    // {
    //     CORE_ASSERT(false, "Type not implemented!");
    //     return nullptr;
    // }

    // template<typename TYPE>
    // uint32 GetTypeID()
    // {
    //     const char* type_name = GetTypeName<Type>();
    //     static int type_id = CRC::Calculate(type_name, sizeof(type_name), CRC::CRC_32());
    // }

    // struct Name
    // {
    //     unsigned int hash;
    //     const char* text;
    // };

    // using ConstructObjectFunction = std::function<void(void*)>;
    // using DestructObjectFunction = std::function<void(void*)>;    
    
    // struct Type
    // {
    //     class TypeDB* typeDB;
    //     Name name;
    //     ConstructObjectFunction constructor;
    //     DestructObjectFunction destructor;
    //     size_t size;
    // };

    // struct Field
    // {

    // };

    // struct Method
    // {
        
    // };
    

    // class TypeDB
    // {
    // public:
    //     Type& CreateType(Name name);
    //     Type& GetType(Name name);
    // private:
    //     typedef std::map<Name, Type*> TypeMap;
    //     TypeMap m_Types;
    // };


} // namespace Spark

