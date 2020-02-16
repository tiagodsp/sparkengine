#include "Spark/Layer.h"
#include "Spark/Events/KeyEvent.h"
#include "Spark/Log.h"

class LayerTest : public Spark::Layer
{
public:
    LayerTest();
    virtual ~LayerTest();

    // Spark::Layer interface implementation ---------
    virtual void OnAttach() override {}
    virtual void OnDetach() override {}
    virtual void OnUpdate() override {}
    virtual void OnEvent(Spark::Event& event) override
    {
        if(event.GetEventType() == Spark::EventType::KeyPressed)
        {
            Spark::KeyPressedEvent& kpe = static_cast<Spark::KeyPressedEvent&>(event);
            LOGI(MyLog, kpe.GetKeyCode());
        }
    }
    // ------------------------------------------------
};