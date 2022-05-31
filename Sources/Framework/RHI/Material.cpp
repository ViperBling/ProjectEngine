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

}

void Material::SetShaderParameter(std::string&& name, Vector4f&& value) noexcept {

    mParameters[name] = value;
}

void Material::SetTexture(std::string &&name, std::shared_ptr<Texture> tex) noexcept {

    mTexture[name] = tex;
}

void Material::SetSampler(std::string &&name, std::shared_ptr<SamplerState> sampler) noexcept {

    mSamplerState[name] = sampler;
}
