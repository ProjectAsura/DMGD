//-----------------------------------------------------------------------------
// File   : renderer.h
// Desc   : Renderer
// Author : Pocol.
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <cstdint>

bool InitRenderer(uint32_t w, uint32_t h, void* hInstance, void* hWindow);
void TermRenderer();
void RenderPixels(const void* pBuffer);

