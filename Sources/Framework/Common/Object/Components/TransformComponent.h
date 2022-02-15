#pragma once

#include "IComponent.h"
#include "Math/MathLib.h"

namespace ProjectEngine
{
    class TransformComponent : public IComponent
    {
    public:
        virtual int Initialize() noexcept;
        virtual void Finalize() noexcept;

    public:
        TransformComponent();
        Vector3f GetPosition() noexcept { return mPosition; }
        Vector3f GetRotation() noexcept { return mRotation; }
        Vector3f GetScale() noexcept { return mScale; }
        void     SetPosition(Vector3f position) noexcept { mPosition = position; }
        void     SetRotation(Vector3f rotation) noexcept { mRotation = rotation; }
        void     SetScale(Vector3f scale) noexcept { mScale = scale; }
        Matrix4f GetWorldMatrix();

    private:
        bool		mWorldMatrixDirty;
        Matrix4f	mWorldMatrix;
        Vector3f    mPosition;
        Vector3f    mRotation;
        Vector3f    mScale;
    };
}