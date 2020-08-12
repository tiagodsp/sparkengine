#include "sparkengine.PCH.h"
#include "OpenGLTexture2D.h"

#include "GL/GL.h"
#include "stb_image.h"

namespace Spark
{
    OpenGLTexture2D::OpenGLTexture2D(const std::string& filepath)
        : m_FilePath(filepath)
    {
    }

    OpenGLTexture2D::~OpenGLTexture2D()
    {
    }

    void OpenGLTexture2D::Bind() const
    {

    }
}
