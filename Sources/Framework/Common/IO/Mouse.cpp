#include "Mouse.h"
#include "Framework/Common/Utils/Logging.h"

using namespace ProjectEngine;


int MouseManager::Initialize() noexcept {

    PROJECTENGINE_LOG(info) << "Mouse Manager Initialize OK.";
    return 0;
}

void MouseManager::Finalize() noexcept {

}

std::pair<int, int> MouseManager::GetPos() const noexcept {

    return {x, y};
}

int MouseManager::GetPosX() const noexcept {

    return x;
}

int MouseManager::GetPosY() const noexcept {

    return y;
}

bool MouseManager::IsInWindow() const noexcept {

    return bIsInWindow;
}

bool MouseManager::LeftIsPressed() const noexcept {

    return bLeftIsPressed;
}

bool MouseManager::RightIsPressed() const noexcept {

    return bRightIsPressed;
}

std::optional<MouseManager::MouseEvent> MouseManager::Read() noexcept {

    if (!buffer.empty())
    {
        MouseManager::MouseEvent event = buffer.front();
        buffer.pop();
        return event;
    }
    return {};
}

void MouseManager::Flush() noexcept {

    buffer = std::queue<MouseEvent>();
}

void MouseManager::OnMouseMove(int newX, int newY) noexcept {

    x = newX;
    y = newY;

    buffer.push(MouseEvent(MouseEvent::Type::Move, *this));
    TrimBuffer();
}

void MouseManager::OnMouseLeave() noexcept {

    bIsInWindow = false;
    buffer.push(MouseEvent(MouseEvent::Type::Leave, *this));
    TrimBuffer();
}

void MouseManager::OnMouseEnter() noexcept {

    bIsInWindow = true;
    buffer.push(MouseEvent(MouseEvent::Type::Enter, *this));
    TrimBuffer();
}

void MouseManager::OnLeftPressed(int newX, int newY) noexcept {

    bLeftIsPressed = true;
    buffer.push(MouseEvent(MouseEvent::Type::LPress, *this));
    TrimBuffer();
}

void MouseManager::OnLeftReleased(int newX, int newY) noexcept {

    bLeftIsPressed = false;
    buffer.push(MouseEvent(MouseEvent::Type::LRelease, *this));
    TrimBuffer();
}

void MouseManager::OnRightPressed(int newX, int newY) noexcept {

    bRightIsPressed = true;
    buffer.push(MouseEvent(MouseEvent::Type::RPress, *this));
    TrimBuffer();
}

void MouseManager::OnRightReleased(int newX, int newY) noexcept {

    bRightIsPressed = false;
    buffer.push(MouseEvent(MouseEvent::Type::RRelease, *this));
    TrimBuffer();
}

void MouseManager::OnWheelUp(int newX, int newY) noexcept {

    buffer.push(MouseEvent(MouseEvent::Type::WheelUp, *this));
    TrimBuffer();
}

void MouseManager::OnWheelDown(int newX, int newY) noexcept {

    buffer.push(MouseEvent(MouseEvent::Type::WheelDown, *this));
    TrimBuffer();
}

void MouseManager::TrimBuffer() noexcept {

    while (buffer.size() > bufferSize) {
        buffer.pop();
    }
}

void MouseManager::OnWheelDelta(int newX, int newY, int delta) noexcept {

    wheelDeltaCarry += delta;
    // generate events for every 120

    while(wheelDeltaCarry >= 120) {
        wheelDeltaCarry -= 120;
        OnWheelUp(newX, newY);
    }

    while(wheelDeltaCarry <= -120) {
        wheelDeltaCarry += 120;
        OnWheelDown(newX, newY);
    }
}