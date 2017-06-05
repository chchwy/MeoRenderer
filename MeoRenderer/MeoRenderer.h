#pragma once

#include "resource.h"
#include <memory>

class RenderSystem;


class MeoRenderer
{
public:
	MeoRenderer();
	~MeoRenderer();

	void Initialize(HWND hWnd);
	void Shutdown();

	void UpdateScene();
	void DrawScene();

private:
	HWND m_hWnd = 0;
	std::unique_ptr< RenderSystem > m_spRenderSystem;
};