#pragma once

namespace Spark
{

enum class RendererAPI
{
    None = 0,
    OpenGL = 1
};

class Renderer
{
private:
    static RendererAPI s_RendererAPI;
public:
    inline static RendererAPI GetAPI() {return s_RendererAPI; }
};


} // namespace Spark
