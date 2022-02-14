#pragma once

#include <memory>

#include "assimp/Importer.hpp"      // C++ importer interface
#include "assimp/scene.h"           // Output data structure

#include "IResource.h"
#include "VertexBuffer.h"

using namespace std;

namespace ProjectEngine
{
    class GraphicsManager;

    class RenderMesh : public IMesh
    {
    public:
        RenderMesh();
        virtual ~RenderMesh();

    public:
        shared_ptr<VertexBuffer> mPositions;
        shared_ptr<VertexBuffer> mNormals;
        shared_ptr<VertexBuffer> mTexCoords;
    };
}