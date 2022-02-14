#include "RenderMesh.h"
#include "GraphicsManager.h"

using namespace ProjectEngine;

RenderMesh::RenderMesh() :
    mPositions(nullptr),
    mNormals(nullptr),
    mTexCoords(nullptr)
{}

RenderMesh::~RenderMesh() {}