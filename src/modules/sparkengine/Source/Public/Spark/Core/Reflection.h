#pragma once
#include "Spark/Core/CoreTypes.h"
#include "CRC.h"
#include <map>
#include <string>

namespace rflt
{
    
    struct Type
    {
        const char* name;
        size_t size;

        Type(const char* name, size_t size)
            : name(name), size(size)
            {}
        virtual ~Type() {}
        virtual std::string getFullName() const { return name; }
    };

    struct TypeStruct : Type
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


} // namespace Spark
