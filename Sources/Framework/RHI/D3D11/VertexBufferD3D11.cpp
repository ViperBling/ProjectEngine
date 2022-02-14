#include <d3d11.h>

#include "Platform/Assert.h"
#include "VertexBufferD3D11.h"

using namespace ProjectEngine;

VertexBufferD3D11::VertexBufferD3D11(unsigned int count, VertexFormat vf) :
    VertexBuffer(count, vf),
    mVertexBuffer(nullptr)
{}