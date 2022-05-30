#pragma once

#include "Framework/Interface/IResource.h"
#include "Framework/RHI/Shader.h"

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

    private:
        std::shared_ptr<Shader> mShader;
        std::unordered_map<std::string, Vector4f> mParameters;
    };
}