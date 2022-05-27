#pragma once

#include <d3d11.h>

#include "Framework/RHI/RenderMesh.h"

namespace ProjectEngine
{
    class RenderMeshD3D11 : public RenderMesh
    {
    public:
        virtual void Initialize(GraphicsManager* gfxManager, aiMesh* mesh) noexcept;
        virtual void Initialize(GraphicsManager* gfxManager, std::shared_ptr<VertexBuffer> vb) noexcept;
        virtual void Render(GraphicsManager* gfxManager, World* world, const Matrix4f& worldMatrix) noexcept;

    private:
        std::vector<unsigned int>  stride;
        std::vector<unsigned int>  offset;
        std::vector<ID3D11Buffer*> vBuffers;
        unsigned int vbcount;
    };
}

