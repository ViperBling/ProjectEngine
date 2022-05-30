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

void Material::Apply(ConstantBuffer cb) noexcept {

    mShader->Use();
    for (auto pair : mParameters) {
        if (pair.first == "color") {
            cb.debugColor = pair.second;
        }
    }
    mShader->SetConstantBuffer(cb);
}

void Material::SetShaderParameter(std::string&& name, Vector4f&& value) noexcept {

    mParameters[name] = value;
}
