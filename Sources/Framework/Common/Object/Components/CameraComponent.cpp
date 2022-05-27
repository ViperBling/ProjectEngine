#include <DirectXMath.h>

#include "CameraComponent.h"

using namespace ProjectEngine;
using namespace DirectX;

CameraComponent::CameraComponent() :
    mCamType(CameraType::Perspective),
    mViewDirty(true),
    mPosition(Vector3f(100, 100, 200)),
    mLookAt(Vector3f(0, 100, 0)),
    mUp(Vector3f(0, 1, 0)),
    mProjectionDirty(true),
    mNearClip(0.01f),
    mFarClip(1000.0f),
    mFov(PI / 3)
{

}

int CameraComponent::Initialize() noexcept {

    return 0;
}

void CameraComponent::Finalize() noexcept {

}

const Matrix4f& CameraComponent::GetViewMatrix() {

    if (mViewDirty) {
        mViewMatrix = BuildViewLookatLH(mPosition, mLookAt, mUp);
        mViewDirty = false;
    }
    return mViewMatrix;
}

const Matrix4f& CameraComponent::GetPerspectiveMatrix() {

    float width = 1280.0f;
    float height = 720.0f;

    if (mProjectionDirty) {
        if (mCamType == CameraType::Orth) {
            mProjectionMatrix = BuildOrthoLH(width, height, mNearClip, mFarClip);
        }
        else {
            mProjectionMatrix = BuildPerspectiveFovLH(mFov, width / height, mNearClip, mFarClip);
        }
//        mProjectionDirty = false;
    }

    return mProjectionMatrix;
}
