#pragma once
#include "sparkengine.PCH.h"

#include "CoreTypes.h"
#include "Spark/Events/Event.h"


#include "sparkengine.api.gen.h"

namespace Spark
{
    struct WindowProps
    {
        std::string Title;
        uint32 Width;
        uint32 Height;

        WindowProps(
            const std::string& title = "Spark Engine",
            uint32 width = 1280,
            uint32 height = 720
        ) : Title(title), Width(width), Height(height) {}

    };
    
    //Interface representing a desktop system based window
    class SPARKENGINE_API IPlatformWindow
    {
    public:
        using EventCallbackFn = std::function<void(Event&)>;

        virtual ~IPlatformWindow() {}

        virtual void OnUpdate() = 0;

        virtual unsigned int GetWidth() const = 0;
        virtual unsigned int GetHeight() const = 0;

        // Window attributes -------------
        virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
        virtual void SetVSync(bool enabled) = 0;
        virtual bool IsVSync() const = 0;

        virtual void* GetNativeWindow() const = 0;

        static IPlatformWindow* Create(const WindowProps& props = WindowProps());
    };
}