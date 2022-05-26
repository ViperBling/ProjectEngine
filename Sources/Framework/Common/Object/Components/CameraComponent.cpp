#include "CameraComponent.h"

using namespace ProjectEngine;

CameraComponent::CameraComponent() :
    mPosition(Vector3f(0, 100, -100)),
    mLookAt(Vector3f(0, 0, 0)),
    mUp(Vector3f(0, 1, 0)),
    mCamType(CameraType::Perspective),
    mNearClip(1.0f),
    mFarClip(1000.0f),
    mFov(PI / 2)
{

}

int CameraComponent::Initialize() noexcept {

    return 0;
}

void CameraComponent::Finalize() noexcept {

}

Matrix4f CameraComponent::GetViewMatrix() {

    return BuildViewLookatRH(mPosition, mLookAt, mUp);
}

Matrix4f CameraComponent::GetPerspectiveMatrix() {

    float width = 1280.0f;
    float height = 720.0f;

    if (mCamType == CameraType::Orth) {
        return BuildOrthoRH(width, height, mNearClip, mFarClip);
    }
    else {
        return BuildPerspectiveFovRH(mFov, width / height, mNearClip, mFarClip);
    }
}
