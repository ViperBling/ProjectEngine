#include <DirectXMath.h>

#include "CameraComponent.h"

using namespace ProjectEngine;
using namespace DirectX;

CameraComponent::CameraComponent() :
    mPosition(Vector3f(100, 100, 200)),
    mLookAt(Vector3f(0, 100, 0)),
    mUp(Vector3f(0, 1, 0)),
    mCamType(CameraType::Perspective),
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

Matrix4f CameraComponent::GetViewMatrix() {

    return BuildViewLookatLH(mPosition, mLookAt, mUp);
}

Matrix4f CameraComponent::GetPerspectiveMatrix() {

    float width = 1280.0f;
    float height = 720.0f;

    if (mCamType == CameraType::Orth) {
        return BuildOrthoLH(width, height, mNearClip, mFarClip);
    }
    else {
        return BuildPerspectiveFovLH(mFov, width / height, mNearClip, mFarClip);
    }
}
