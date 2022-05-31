#pragma once

#include "Framework/Interface/IModule.h"
#include "Framework/Common/Math/MathLib.h"
#include "assimp/scene.h"

namespace ProjectEngine
{
    class GraphicsManager;
    class World;

    class IRenderResource{};

    enum VertexFormat
    {
        None = 0,
        VF_P3F,
        VF_T2F,
        VF_N3F,
        VF_C4B,
    };

    class IVertexBuffer : public IRenderResource
    {
    public:

        virtual void Initialize(void* data, unsigned int count, VertexFormat vf) noexcept = 0;
        virtual unsigned int GetVertexSize(VertexFormat vf) noexcept = 0;
        virtual void Finalize() noexcept = 0;
    };

    enum IndexFormat
    {
        IF_None = 0,
        IF_UINT16,
        IF_UINT32,
    };

    class IIndexBuffer : public IRenderResource
    {
    public:
        virtual void Initialize(void* data, unsigned int count, IndexFormat iformat) noexcept = 0;
        virtual void Finalize() noexcept = 0;
    };

    enum PrimitiveType
    {
        PT_POINT = 1,
        PT_LINE,
        PT_TRIANGLE,
    };

    struct ConstantBuffer
    {
        Matrix4f world;
        Matrix4f view;
        Matrix4f projection;
        Vector4f debugColor;
    };

    class IMesh : public IRenderResource
    {
    public:
        virtual void Initialize(aiMesh* mesh) noexcept = 0;
        virtual void Render(World* world, const Matrix4f& worldMatrix) noexcept = 0;
        virtual int	 GetValidVertexBufferCount() noexcept = 0;
        virtual void Finalize() noexcept = 0;
    };

    class IMaterial : public IRenderResource
    {
    public:
        virtual void Initialize() noexcept = 0;
        virtual void Finalize() noexcept = 0;
    };

    class ITexture : public IRenderResource
    {
    public:
        virtual void Initialize(const std::string&) noexcept = 0;
        virtual void Finalize() noexcept = 0;
    };

    class ISamplerState : public IRenderResource
    {
    public:
        virtual void Initialize() noexcept = 0;
        virtual void Finalize() noexcept = 0;
    };
}