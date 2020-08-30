#pragma once

#include "Spark/Core/CoreTypes.h"
#include "Spark/Engine/GameFramework/Actor.h"
#include "Spark/Engine/World.h"
#include "Spark/Core/Layer.h"
#include "Spark/Renderer/Renderer.h"
#include "Spark/Renderer/Texture.h"

#include "sandbox.api.gen.h"

namespace Sandbox
{
    class LayerTest2D : public Spark::Layer
    {
    private:
        Spark::Ref<Spark::Actor> m_CameraActor;
        Spark::Ref<Spark::World> m_World;
        Spark::Ref<Spark::Texture> m_Texture;

    public:
        LayerTest2D(/* args */);
        ~LayerTest2D();

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnUpdate(Spark::Timestep delta) override;
        virtual void OnEvent(Spark::Event& event) override;

    };
    
} // namespace Sandbox
