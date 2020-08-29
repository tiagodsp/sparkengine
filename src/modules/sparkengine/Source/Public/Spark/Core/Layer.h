#pragma once

#include "Spark/Core/CoreTypes.h"
#include "Spark/Core/Timestep.h"
#include "Spark/Events/Event.h"

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
        virtual void OnUpdate(Timestep delta) {}
        virtual void OnEvent(Event& event) {}

        inline const std::string& GetName() const { return m_DebugName; }
    protected:
        const std::string& m_DebugName;
    };
}
