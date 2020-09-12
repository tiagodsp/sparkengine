#include "sparkengine.PCH.h"
#include "Spark/Engine/Object/Object.h"

REFLECTION_CLASS_BEGIN(Spark::Object)
REFLECTION_STRUCT_END()

namespace Spark
{    
    Object* NewObject(const char*, Type* type)
    {
        Object* obj = (Object*)malloc(type->size);
        ((TypeClass*)type)->constructor(obj);
        return obj;
    }
} // namespace Spark


