#pragma once

#include "Framework/Interface/IResource.h"
#include "Framework/RHI/Shader.h"
#include "Framework/RHI/Texture.h"
#include "Framework/RHI/SamplerState.h"

namespace ProjectEngine
{
    class Material : public IRenderResource
    {
    public:
        virtual void Initialize() noexcept;
        virtual void Finalize() noexcept;
        virtual void SetShader(std::shared_ptr<Shader> shader);
        virtual std::shared_ptr<Shader> GetShader();

        virtual void Apply(ConstantBuffer cb) noexcept;
        virtual void SetShaderParameter(std::string&& name, Vector4f&& value) noexcept;

        virtual void SetTexture(std::string&& name, std::shared_ptr<Texture> tex) noexcept;
        virtual void SetSampler(std::string&& name, std::shared_ptr<SamplerState> sampler) noexcept;

    protected:
        std::shared_ptr<Shader> mShader;
        std::unordered_map<std::string, Vector4f> mParameters;
        std::unordered_map<std::string, std::shared_ptr<Texture>> mTexture;
        std::unordered_map<std::string, std::shared_ptr<SamplerState>> mSamplerState;
    };
}