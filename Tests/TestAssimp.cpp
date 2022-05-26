#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include <iostream>

int main()
{
    const std::string& pFile = "Asset/Scene/aili_cycle.fbx";

    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(
        pFile,
        aiProcess_CalcTangentSpace |
        aiProcess_Triangulate |
        aiProcess_JoinIdenticalVertices |
        aiProcess_SortByPType);

    auto root = scene->mRootNode;
    for (unsigned int i = 0; i < root->mNumChildren; ++i) {
        auto node = root->mChildren[i];
        std::cout << "node name: " << node->mName.C_Str() << std::endl;
        std::cout << "mesh cout: " << node->mNumMeshes << std::endl;
        if (node->mNumMeshes > 0) {
            auto mesh = scene->mMeshes[node->mMeshes[0]];
            std::cout << "primitives type: " << mesh->mPrimitiveTypes << std::endl;
            std::cout << "has position" << mesh->HasPositions() << std::endl;
            std::cout << "position vertex count: " << mesh->mNumVertices << std::endl;
            std::cout << "has normal" << mesh->HasNormals() << std::endl;
            auto first = mesh->mNormals[0];
            std::cout << "first normal" << first.x << "," << first.y << "," << first.z << std::endl;
            std::cout << "faces: " << mesh->mNumFaces << std::endl;
            std::cout << "uv channels: " << mesh->GetNumUVChannels() << std::endl;
            std::cout << "has uvcoord: " << mesh->HasTextureCoords(0) << std::endl;

            std::cout << "uv components: " << mesh->mNumUVComponents[0] << std::endl;
            auto uv = mesh->mTextureCoords[0];
            if (uv) {
                std::cout << "first uv" << uv->x << "," << uv->y << std::endl;
            }
        }
        std::cout << std::endl;
    }

    if (scene) {
        return 0;
    }

    return 1;
}