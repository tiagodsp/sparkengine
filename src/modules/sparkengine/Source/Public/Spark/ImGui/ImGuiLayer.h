#include "sparkengine.PCH.h"
#include "Spark/Layer.h"
#include "sparkengine.api.gen.h"

namespace Spark
{
    class SPARKENGINE_API ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        virtual ~ImGuiLayer();

        // Layer interface implementation ---------
        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnUpdate() override;
        virtual void OnEvent(Event& event) override;
    private:
        float m_Time = 0.0f;
    };
}