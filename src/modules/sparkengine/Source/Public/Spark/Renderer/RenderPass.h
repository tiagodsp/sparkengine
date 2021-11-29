#pragma once
#include "Spark/Core/CoreTypes.h"
#include "Spark/Renderer/Framebuffer.h"
#include "Spark/Renderer/IShader.h"
#include "sparkengine.api.gen.h"

namespace Spark
{
	/**
	 * @brief Render Pass properties
	 * @param Size Size of the render pass
	 * @param Framebuffers Dictionary with Tuple with Framebuffers to be used by the render pass and its shaders
	 * @param RenderCommandsCallback Callback to be called when the render pass is executed
	 */
	struct SPARKENGINE_API RenderPassProperties
	{
		glm::vec2 Size;
		std::unordered_map<std::string, std::tuple<Ref<IFramebuffer>, Ref<IShader>>> Framebuffers;
		std::function<void()> RenderCommandsCallback;
	};

	/**
	 * @brief Render Pass class
	 */
	class SPARKENGINE_API RenderPass
	{
	  private:
		RenderPassProperties m_Properties;

	  public:
		virtual ~RenderPass();

		/**
		 * @brief Construct a new Render Pass with properties
		 */
		RenderPass(const RenderPassProperties &Properties);

		/**
		 * @brief Render this render pass
		 */
		void Render();

		/**
		 * @brief Invalidates the Render Pass
		 */
		void Invalidate();

		/**
		 * @brief Get framebuffers by name
		 */
		Ref<IFramebuffer> GetFramebuffersByName(const std::string &Name) const
		{
			return std::get<0>(m_Properties.Framebuffers.at(Name));
		}
	};
}; // namespace Spark