#include "SparkEditor.h"
#include "SparkEditorLayer.h"

namespace Spark
{
    SparkEditor::SparkEditor()
        : Application("Spark Editor")
    {
        this->PushLayer(new SparkEditorLayer());
        //this->PushLayer(new LayerTest());
    }

    SparkEditor::~SparkEditor()
    {

    }

    Application* CreateApplication()
    {
        return new SparkEditor();
    }
}
