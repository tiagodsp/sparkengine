#include "sparkengine.PCH.h"

#include "Spark/LayerStack.h"

namespace Spark
{
    LayerStack::LayerStack()
    {
        m_LayerInsert = m_Layers.begin();
    }
    
    LayerStack::~LayerStack()
    {
        for(Layer* layer : m_Layers)
            delete layer;
    }

    void LayerStack::PushLayer(Layer* layer)
    {
        m_LayerInsert = m_Layers.emplace(m_LayerInsert, m_Layers);
    }

    void LayerStack::PushOverlay(Layer* overlayer)
    {
        m_Layers.emplace_back(overlayer);
    }
    
    void LayerStack::PopLayer(Layer* layer)
    {
        auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
        if(it != m_Layers.end())
        {
            m_Layers.erase(it);
            m_LayerInsert--;
        }
    }
    
    void LayerStack::PopOverlay(Layer* overlay)
    {
        auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
        if(it != m_Layers.end())
        {
            m_Layers.erase(it);
        }
    }
}