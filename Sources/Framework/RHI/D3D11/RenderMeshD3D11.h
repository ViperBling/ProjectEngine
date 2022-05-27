#pragma once

#include <d3d11.h>

#include "Framework/RHI/RenderMesh.h"

namespace ProjectEngine
{
    class RenderMeshD3D11 : public RenderMesh
    {
    public:
        RenderMeshD3D11(aiMesh* mesh);
        RenderMeshD3D11(std::shared_ptr<VertexBuffer> vb);
        virtual ~RenderMeshD3D11();

        virtual void Initialize(aiMesh* mesh) noexcept;
        virtual void Initialize(std::shared_ptr<VertexBuffer> vb) noexcept;
        virtual void Render(World* world, const Matrix4f& worldMatrix) noexcept;
        virtual void Finalize() noexcept;

    private:
        std::vector<unsigned int>  stride;
        std::vector<unsigned int>  offset;
        std::vector<ID3D11Buffer*> vBuffers;
        unsigned int vbcount;
    };
}

