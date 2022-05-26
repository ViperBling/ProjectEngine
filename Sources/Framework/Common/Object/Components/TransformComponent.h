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
        void SetPosition(Vector3f&& position) { mPosition = position; }
        void SetRotation(Vector3f&& rotation) { mRotation = rotation; }
        void SetScale(Vector3f&& scale) { mScale = scale; }

    private:
        Vector3f mPosition;
        Vector3f mRotation;
        Vector3f mScale;
    };
}