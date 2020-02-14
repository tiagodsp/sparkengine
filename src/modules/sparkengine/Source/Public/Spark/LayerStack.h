#pragma once

#include "Spark/CoreTypes.h"
#include "Spark/Layer.h"
#include <vector>

#include "sparkengine.api.gen.h"

namespace Spark
{
    class SPARKENGINE_API LayerStack
    {
    public:
        LayerStack();
        ~LayerStack();

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlayer);
        void PopLayer(Layer* layer);
        void PopOverlay(Layer* overlay);

        std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
        std::vector<Layer*>::iterator end() { return m_Layers.end(); }
    private:
        std::vector<Layer*> m_Layers;
        uint32 m_LayerInsertIndex = 0;
    };
} // namespace Spark

