#include <DirectXMath.h>

#include "CameraComponent.h"

using namespace ProjectEngine;
using namespace DirectX;

CameraComponent::CameraComponent() 
    : mCamType(CameraType::Perspective)
    , mViewDirty(true)
    , mPosition(Vector3f(-10, 10, -20))
    , mLookAt(Vector3f(0, 1, 0))
    , mUp(Vector3f(0, 1, 0))
    , mProjectionDirty(true)
    , mNearClip(0.01f)
    , mFarClip(1000.0f)
    , mFov(PI / 3)
    , mWidth(1280)
    , mHeight(720)
    , mMoveSpeed(1.0f)
{

}

int CameraComponent::Initialize() noexcept {

    return 0;
}

void CameraComponent::Finalize() noexcept {

}

void ProjectEngine::CameraComponent::Update(float deltaTime)
{
    mViewDirty = false;
    
}

const Matrix4f& CameraComponent::GetViewMatrix() {

    if (mViewDirty) {
        mViewMatrix = BuildViewLookatLH(mPosition, mLookAt, mUp);
        mViewDirty = false;
    }
    return mViewMatrix;
}

const Matrix4f& CameraComponent::GetPerspectiveMatrix() {

    if (mProjectionDirty) {
        if (mCamType == CameraType::Orth) {
            mProjectionMatrix = BuildOrthoLH(mWidth, mHeight, mNearClip, mFarClip);
        }
        else {
            mProjectionMatrix = BuildPerspectiveFovLH(mFov, mWidth / mHeight, mNearClip, mFarClip);
        }
//        mProjectionDirty = false;
    }

    return mProjectionMatrix;
}
