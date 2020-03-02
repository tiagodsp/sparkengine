#pragma once
#include "sparkengine.api.gen.h"

namespace Spark
{

class SPARKENGINE_API Timestep
{
private:
    float m_Time;

public:
    Timestep(float time = .0f)
        : m_Time(time)
    {
    }

    inline float GetTimeSeconds(){ return m_Time; }
    inline float GetTimeMilis() { return m_Time * 1000; }

    // Operators -----------
    inline operator float() const{ return m_Time;}

    inline Timestep& operator+=(const Timestep& rhs)
    {
        this->m_Time += rhs.m_Time;
        return *this;
    }
    
    inline Timestep operator+(const Timestep& rhs)
    {
        return Timestep(m_Time + rhs.m_Time);
    }
    
    inline Timestep& operator-=(const Timestep& rhs)
    {
        this->m_Time -= rhs.m_Time;
        return *this;
    }
    
    inline Timestep operator-(const Timestep& rhs)
    {
        return Timestep(m_Time - rhs.m_Time);
    }
};

} // namespace Spark