#pragma once

#include "Spark/CoreTypes.h"

#include "sparkengine.api.gen.h"

namespace Spark
{
    class SPARKENGINE_API Layer
    {
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer();

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate() {}
        virtual void OnEvent(Event& event) {}

        inline const std::string& GetName() const { return m_DebugName; }
    protected:
        const std::string& m_DebugName;
    };
}
