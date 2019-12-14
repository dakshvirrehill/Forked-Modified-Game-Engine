#include "Core.h"
#include "IRenderable.h"
#include "RenderSystem.h"

IRenderable::IRenderable()
{
	RenderSystem::instance().addRenderable(this);
}

IRenderable::~IRenderable()
{
	RenderSystem::instance().removeRenderable(this);
}

void IRenderable::loadLayer(json::JSON& pRenderNode)
{
	if (pRenderNode.hasKey("layer"))
	{
		RenderSystem::instance().setRenderLayer(this, (RenderSystem::RenderLayer)pRenderNode["layer"].ToInt());

	}
}
