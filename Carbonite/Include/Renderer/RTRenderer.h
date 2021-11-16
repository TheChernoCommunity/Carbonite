#pragma once

#include "Renderer.h"

class RTRenderer : public Renderer
{
private:
	virtual void initImpl() override;
	virtual void deinitImpl() override;
	virtual void renderImpl() override;
};