//#include <d3d11.h>

#include "VertexBufferD3D11.h"
#include "Platform/Assert.h"


ProjectEngine::VertexBufferD3D11::VertexBufferD3D11(unsigned int count, ProjectEngine::VertexFormat vf) :
    VertexBuffer(count, vf),
    mVertexBuffer(nullptr)
{

}
