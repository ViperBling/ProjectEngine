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

    private:
        std::shared_ptr<Shader> mShader;
    };
}