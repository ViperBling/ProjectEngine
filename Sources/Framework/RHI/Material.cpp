#include "Material.h"

using namespace ProjectEngine;


void Material::Initialize() noexcept {

}

void Material::Finalize() noexcept {

}

void Material::SetShader(std::shared_ptr<Shader> shader) {

    mShader = shader;
}

std::shared_ptr<Shader> Material::GetShader() {
    return mShader;
}
