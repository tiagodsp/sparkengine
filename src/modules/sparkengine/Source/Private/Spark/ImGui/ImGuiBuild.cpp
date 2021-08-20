#include "sparkengine.PCH.h"


#ifdef SPARKENGINE_ENABLE_RENDERER_OPENGL
#include "examples/imgui_impl_opengl3.cpp"
#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include "examples/imgui_impl_glfw.cpp"
#endif //SPARKENGINE_ENABLE_RENDERER_OPENGL

#ifdef SPARKENGINE_ENABLE_RENDERER_METAL
#include "examples/imgui_impl_metal.mm"
#endif //SPARKENGINE_ENABLE_RENDERER_METAL