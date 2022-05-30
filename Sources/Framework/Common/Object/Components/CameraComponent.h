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

        const Matrix4f&	GetViewMatrix();
        const Matrix4f&	GetPerspectiveMatrix();

        CameraType GetType() const { return mCamType; }
        void SetType(CameraType type) { mCamType = type; }

        Vector3f GetPosition() const { return mPosition; }
        Vector3f GetLookAt() const { return mLookAt; }
        Vector3f GetUp() const { return mUp; }
        void SetPosition(const Vector3f& position) { mPosition = position; mViewDirty = true; }
        void SetLookAt(const Vector3f& lookAt) { mLookAt = lookAt; mViewDirty = true; }
        void SetUp(const Vector3f& up) { mUp = up; mViewDirty = true; }

        float GetNearClip() const { return mNearClip; }
        float GetFarClip() const { return mFarClip; }
        float GetFov() const { return mFov; }
        void SetNearClip(float n) { mNearClip = n; mProjectionDirty = true; }
        void SetFarClip(float f) { mFarClip= f; mProjectionDirty = true; }
        void SetFov(float fov) { mFov = fov; mProjectionDirty = true; }

        float GetViewWidth() const { return mWidth; }
        float GetViewHeight() const { return mHeight; }
        void SetViewWidth(float w) { mWidth = w; }
        void SetViewHeight(float h) { mHeight = h; }

    private:
        CameraType mCamType;

        bool mViewDirty;
        Matrix4f mViewMatrix;
        Vector3f mPosition;
        Vector3f mLookAt;
        Vector3f mUp;

        bool mProjectionDirty;
        Matrix4f mProjectionMatrix;
        float mNearClip;
        float mFarClip;
        float mFov;

        float mWidth;
        float mHeight;
    };
}