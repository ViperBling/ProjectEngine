#pragma once

#include "Framework/Common/Math/MathLib.h"
#include "Framework/Interface/IComponent.h"

namespace ProjectEngine
{
    enum CameraType
    {
        Orth = 1,
        Perspective = 2
    };

    class CameraComponent : public IComponent
    {
    public:

        CameraComponent();
        virtual int Initialize() noexcept;
        virtual void Finalize() noexcept;

        Matrix4f	GetViewMatrix();
        Matrix4f	GetPerspectiveMatrix();

    public:

        Vector3f mPosition;
        Vector3f mLookAt;
        Vector3f mUp;

        CameraType mCamType;
        float mNearClip;
        float mFarClip;
        float mFov;
    };
}