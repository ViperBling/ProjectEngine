#pragma once
#include "IModule.h"
#include "Math/MathLib.h"
#include "assimp/scene.h"

namespace ProjectEngine
{
    class GraphicsManager;
    class World;

    class IRenderResource
    {
    };

    enum VertexFormat
    {
        None = 0,
        VF_T2F,
        VF_P3F,
        VF_N3F,
        VF_C4B,
    };

    enum IndexFormat
    {
        IF_None = 0,
        IF_UINT16,
        IF_UINT32,
    };

    enum PrimitiveType
    {
        PT_POINT = 1,
        PT_LINE,
        PT_TRIANGLE,
    };

    class IVertexBuffer : public IRenderResource
    {
        virtual void Initialize(void* data, unsigned int count, VertexFormat vf) noexcept = 0;
        virtual unsigned int GetVertexSize(VertexFormat vf) noexcept = 0;
        virtual void Finialize() noexcept = 0;
    };

    class IIndexBuffer : public IRenderResource
    {
        virtual void Initialize(void* data, unsigned int count, IndexFormat iformat) noexcept = 0;
        virtual void Finialize() noexcept = 0;
    };

    class IMesh : public IRenderResource
    {
    public:
        virtual void		Initialize(aiMesh* mesh) noexcept = 0;
        virtual int			GetVaildVertexBufferCount() noexcept = 0;
        virtual void		Render(World* world, const Matrix4f& worldMatrix) noexcept = 0;
        virtual void		Finialize() noexcept = 0;
    };
}