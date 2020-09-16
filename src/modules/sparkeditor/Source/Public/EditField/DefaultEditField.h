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
        const char* m_VarName;
    public:
        EditField() {};
        EditField(const char* varName, Type* type)
            : m_Type(type)
            , m_VarName(varName)
        {}

        virtual void OnGUI() {
            ImGui::Text(m_VarName);
        };
    };

    class TransformEditField : public EditField
    {
        TransformComponent& m_TransformComponent;
    public:
        TransformEditField(const char* varName, TransformComponent& transformComponent)
            : m_TransformComponent(transformComponent)
        {
            m_VarName = varName;
        }
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
        
        PrimitivePropertyEditField(const char* varName, void* primitivePtr, Type* type)
            : m_primitivePtr(primitivePtr)
        {
            m_Type = type;
            m_VarName = varName;
        }

        virtual void OnGUI() override
        {
            std::string type = m_Type->name;
            if(type == "float")
            {
                ImGui::InputFloat(m_VarName, (float*)m_primitivePtr);
            }
            else if(type == "int")
            {
                ImGui::InputInt(m_VarName, (int*)m_primitivePtr);
            }
            else if(type == "double")
            {
                ImGui::InputDouble(m_VarName, (double*)m_primitivePtr);
            }
            else if(type == "glm::vec3")
            {
                ImGui::InputFloat3(m_VarName, (float*)m_primitivePtr);
            }
            else
            {
                ImGui::Text(m_VarName);
            }
        }
    };

    class EditFieldFactory
    {
    public:
        static Ref<EditField> Create(const char* varName, void* memberPtr, Type* type)
        {
            std::string typeName = type->name;
            return std::make_shared<PrimitivePropertyEditField>(varName, memberPtr, type);
        }
    };
}