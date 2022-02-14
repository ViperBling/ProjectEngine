#include "TransformComponent.h"

using namespace ProjectEngine;

TransformComponent::TransformComponent() :
        mPosition(0.0f, 0.0f, 0.0f),
        mRotation(0.0f, 0.0f, 0.0f),
        mScale(1.0f, 1.0f, 1.0f)
{}

int TransformComponent::Initialize() noexcept
{
    return 0;
}


void TransformComponent::Finalize() noexcept
{
}