#include "Shader.h"

using namespace ProjectEngine;

bool Shader::InitializeFromFile(
    GraphicsManager *gfxManager,
    const std::string &vsPath,
    const std::string &psPath) noexcept
{
    return true;
}

void Shader::Use(ProjectEngine::GraphicsManager *gfxManager) noexcept {

}

void Shader::Finalize(GraphicsManager *gfxManager) noexcept {

}

void Shader::SetConstantBuffer(GraphicsManager *gfxManager, const ConstantBuffer &cbuffer) noexcept {

}

