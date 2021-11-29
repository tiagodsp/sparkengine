#include "Spark/Renderer/RenderPass.h"

namespace Spark
{
	RenderPass::~RenderPass()
	{
		Invalidate();
	}

	RenderPass::RenderPass(const RenderPassProperties &Properties)
	{
		m_Properties = Properties;
	}

	void RenderPass::Render()
	{
		for (auto &Framebuffer : m_Properties.Framebuffers)
		{
			std::get<0>(Framebuffer.second)->Bind();
			m_Properties.RenderCommandsCallback();
			std::get<0>(Framebuffer.second)->Unbind();
		}
	}

	void RenderPass::Invalidate()
	{
		for (auto &Framebuffer : m_Properties.Framebuffers)
		{
			std::get<0>(Framebuffer.second)->Invalidate();
		}
	}
} // namespace Spark