#pragma once

#include "assimp/Importer.hpp"
#include "assimp/scene.h"

#include "Framework/Interface/IResource.h"
#include "Framework/RHI/VertexBuffer.h"

#include <memory>

//using namespace std;

namespace ProjectEngine
{
    class GraphicsManager;

    class RenderMesh : public IMesh
    {
    public:
        RenderMesh();
        virtual ~RenderMesh();

        std::shared_ptr<VertexBuffer>    mPositions;
        std::shared_ptr<VertexBuffer>    mNormals;
        std::shared_ptr<VertexBuffer>    mTexCoords;
    };
}