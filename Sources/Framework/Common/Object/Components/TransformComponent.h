#pragma once

#include "Framework/Interface/IComponent.h"
#include "Framework/Common/Math/MathLib.h"

namespace ProjectEngine
{
    class TransformComponent : public IComponent
    {
    public:
        int Initialize() noexcept override;
        void Finalize() noexcept override;

        TransformComponent();
        Vector3f GetPosition() { return mPosition; }
        Vector3f GetRotation() { return mRotation; }
        Vector3f GetScale() { return mScale; }
        void SetPosition(Vector3f&& position) { mPosition = position; mWorldMatrixDirty = true; }
        void SetRotation(Vector3f&& rotation) { mRotation = rotation; mWorldMatrixDirty = true; }
        void SetScale(Vector3f&& scale) { mScale = scale; mWorldMatrixDirty = true; }

        Matrix4f GetWorldMatrix();

    private:
        bool mWorldMatrixDirty;
        Matrix4f mWorldMatrix;

        Vector3f mPosition;
        Vector3f mRotation;
        Vector3f mScale;
    };
}