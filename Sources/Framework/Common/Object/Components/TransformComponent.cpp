#include "TransformComponent.h"


ProjectEngine::TransformComponent::TransformComponent() :
    mWorldMatrixDirty(true),
    mPosition(0.0f, 0.0f, 0.0f),
    mRotation(0.0f, 0.0f, 0.0f),
    mScale(1.0f, 1.0f, 1.0f)
{
}

int ProjectEngine::TransformComponent::Initialize() noexcept {
    return 0;
}

void ProjectEngine::TransformComponent::Finalize() noexcept {

}

Matrix4f ProjectEngine::TransformComponent::GetWorldMatrix() {

    if (mWorldMatrixDirty) {
        auto position = GetPosition();
        auto scale = GetScale();
        auto rotation = GetRotation();
        auto translation = BuildTranslationMatrix(position);
        auto scaling = BuildScaleMatrix(scale);

        auto rx = BuildRotationMatrix(Vector3f(1, 0, 0), rotation.x());
        auto ry = BuildRotationMatrix(Vector3f(0, 1, 0), rotation.y());
        auto rz = BuildRotationMatrix(Vector3f(0, 0, 1), rotation.z());
        mWorldMatrix = translation * rz * ry * rx * scaling; // make sure translation matrix go first.
        mWorldMatrixDirty = false;
    }

    return mWorldMatrix;
}


