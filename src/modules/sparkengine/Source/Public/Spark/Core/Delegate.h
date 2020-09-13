#pragma once

#include <tuple>
#include <functional>

namespace Spark
{
    template<typename... Args>
    class Delegate
    {
    private:
        std::vector<std::function<void(Args...)>> m_Functions;
    public:
        template<typename C>
        void Add(C* obj, void(C::*func)(Args...))
        {
            m_Functions.push_back([=](Args... args){ (obj->*func)(args...); });
        }
        
        template<typename... Args>
        void operator() (Args&&... args)
        {
            for(auto& fn : m_Functions)
            {
                //auto boundFunction = std::bind(fn.first, fn.second, std::placeholders::_1);
                //boundFunction(std::forward<Args>(args)...);
                //fn(std::forward<Args>(args)...);
                fn(args...);
            }
        }
    };
} // namespace Spark
