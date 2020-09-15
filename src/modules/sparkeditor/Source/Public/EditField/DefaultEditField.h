#pragma once

#include "imgui.h"
#include "glm/glm.hpp"
#include "Spark/Engine/Object/Object.h"
#include "Spark/Engine/GameFramework/Actor.h"

namespace Spark
{
    class EditField
    {
    protected:
        Type* m_Type;
    public:
        EditField() {};
        EditField(Type* type) : m_Type(m_Type) {}

        virtual void OnGUI() {
            ImGui::Text(m_Type->name);
        };
    };

    class TransformEditField : public EditField
    {
        TransformComponent& m_TransformComponent;
    public:
        TransformEditField(TransformComponent& transformComponent) : m_TransformComponent(transformComponent) {}
        virtual void OnGUI() override
        {
            ImGui::InputFloat3("Position", (float*)&m_TransformComponent.Position, 3);
            ImGui::InputFloat3("Rotation", (float*)&m_TransformComponent.Rotation, 3);
            ImGui::InputFloat3("Scale", (float*)&m_TransformComponent.Scale, 3);
        }
    };

    class PrimitivePropertyEditField : public EditField
    {
        void* m_primitivePtr;
    public:
        
        PrimitivePropertyEditField(void* primitivePtr, Type* type)
            : m_primitivePtr(primitivePtr)
        {
            m_Type = type;
        }

        virtual void OnGUI() override
        {

        }
    };

    class EditFieldFactory
    {
    public:
        static Ref<EditField> Create(void* memberPtr, Type* type)
        {
            std::string typeName = type->name;
            // Check if the type is a Class.
            if(dynamic_cast<TypeClass*>(type))
            {
                if(typeName == "Spark::TransformComponent")
                {
                    return std::make_shared<TransformEditField>(*(TransformComponent*)memberPtr);
                }
            }
            else if(
                typeName == "float" ||
                typeName == "int" ||
                typeName == "double"
            )
            {
                //return std::make_shared<PrimitivePropertyEditField>(memberPtr, type);
                return std::make_shared<EditField>(type);
            }
            else
            {
                return std::make_shared<EditField>(type);
            }
        }
    };
}