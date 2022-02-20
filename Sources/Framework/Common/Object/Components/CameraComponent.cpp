#include <DirectXMath.h>
#include "CameraComponent.h"

using namespace DirectX;
using namespace ProjectEngine;

CameraComponent::CameraComponent() :
    mCameraType(CameraType::Perspective),
    mPosition(Vector3f(-10, 10, -20)),
    mLookat(Vector3f(0, 1, 0)),
    mUp(Vector3f(0, 1, 0)),
    mNearClip(0.01f),
    mFarClip(1000.0f),
    mFov(PI / 3),
    mViewDirty(true),
    mProjectionDirty(true)
{}

int CameraComponent::Initialize() noexcept
{
    return 0;
}

void CameraComponent::Finalize() noexcept
{
}

const Matrix4f& CameraComponent::GetViewMatrix()
{
    if (mViewDirty) {
        mViewMatrix = BuildViewLookatLH(mPosition, mLookat, mUp);
        mViewDirty = false;
    }

    return mViewMatrix;
}

const Matrix4f& CameraComponent::GetPerspectiveMatrix()
{
    float width = 1280.0f;
    float height = 720.0f;

    if (mProjectionDirty)
    {
        if (mCameraType == CameraType::Orth)
        {
            mProjectionMatrix = BuildOrthoLH(width, height, mNearClip, mFarClip);
        }
        else
        {
            mProjectionMatrix = BuildPerspectiveFovLH(mFov, width / height, mNearClip, mFarClip);
        }
    }
    return mProjectionMatrix;
}
