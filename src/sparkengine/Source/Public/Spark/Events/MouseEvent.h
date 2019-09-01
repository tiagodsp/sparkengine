#pragma once

#include "Event.h"
#include <sstream>

#include "sparkengine.api.gen.h"

namespace Spark
{
    class SPARKENGINE_API MouseMovedEvent : public Event
    {
    public:
        MouseMovedEvent(float x, float y)
            : m_MouseX(x), m_MouseY(y) {}
        
        inline float GetX() const { return m_MouseX; }
        inline float GetY() const { return m_MouseY; }
        inline void GetXY(float& x, float& y)
        {
            x = m_MouseX;
            y = m_MouseY;
        };

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
            return ss.str();
        }

        EVENT_CLASS_TYPE(EventType::MouseMoved)
        EVENT_CLASS_CATEGORY(EventCategory::Mouse | EventCategory::Input)

    private:
        float m_MouseX, m_MouseY;
    };

    class SPARKENGINE_API MouseScrollEvent : public Event
    {
    public:
        MouseScrollEvent(float xOffset, float yOffset)
            : m_XOffset(xOffset), m_YOffset(yOffset) {}
        
        inline float GetXOffset() const { return m_XOffset; }
        inline float GetYOffset() const { return m_YOffset; }
        inline void GetXYOffset(float& x, float& y)
        {
            x = m_XOffset;
            y = m_YOffset;
        };

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseScrollEvent: " << m_XOffset << ", " << m_YOffset;
            return ss.str();
        }

        EVENT_CLASS_TYPE(EventType::MouseScrolled)
        EVENT_CLASS_CATEGORY(EventCategory::Mouse | EventCategory::Input)

    private:
        float m_XOffset, m_YOffset;
    };

    class SPARKENGINE_API MouseButtonEvent : public Event
    {
    public:
        inline int GetMouseButton() const { return m_Button; }
        
        EVENT_CLASS_CATEGORY(EventCategory::Mouse | EventCategory::Input)
    protected:
        MouseButtonEvent(int button)
            : m_Button(button) {}

        int m_Button;        
    };

    class SPARKENGINE_API MouseButtonPressedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonPressedEvent(int button)
            : MouseButtonEvent(button) {}
        
        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: " << m_Button;
            return ss.str();
        }
        
        EVENT_CLASS_TYPE(EventType::MouseButtonPressed)    
    };

    class SPARKENGINE_API MouseButtonReleasedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonReleasedEvent(int button)
            : MouseButtonEvent(button) {}
        
        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonReleasedEvent: " << m_Button;
            return ss.str();
        }
        
        EVENT_CLASS_TYPE(EventType::MouseButtonReleased)    
    };


} // namespace Spark
