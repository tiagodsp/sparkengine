#pragma once

#include "Spark/Core/CoreTypes.h"
#include "Spark/Core/PlatformWindow.h"
#include "Spark/Renderer/IGraphicsContext.h"

struct GLFWwindow;

namespace Spark
{
    class WindowsPlatformWindow : public IPlatformWindow
    {
    public:
        WindowsPlatformWindow(const WindowProps& props);
        virtual ~WindowsPlatformWindow();

        void OnUpdate() override;

        inline uint32 GetWidth() const override { return m_Data.Width; };
        inline uint32 GetHeight() const override { return m_Data.Height; };

        //Window attributes --------
        inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
        void SetVSync(bool enabled) override;
        bool IsVSync() const override;

        inline virtual void* GetNativeWindow() const override { return m_Window; };
    
    private:
        virtual void Init(const WindowProps& props);
        virtual void Shutdown();

    private:
        GLFWwindow* m_Window;
        IGraphicsContext* m_GraphicsContext;
        
        struct WindowData
        {
            std::string Title;
            uint32 Width, Height;
            bool VSync;

            EventCallbackFn EventCallback;

        } m_Data;
    };
}
