#pragma once

#include <queue>
#include <optional>

#include "Framework/Interface/IModule.h"

namespace ProjectEngine
{
    class MouseManager : public IModule
    {
        friend class WindowsApplication;

    public:
        class MouseEvent
        {
        public:
            enum class Type
            {
                LPress,
                LRelease,
                RPress,
                RRelease,
                WheelUp,
                WheelDown,
                Move,
                Enter,
                Leave
            };
        private:
            Type type;
            bool bLeftIsPressed;
            bool bRightIsPressed;
            int x;
            int y;
        public:
            MouseEvent(Type type, const MouseManager& parent) noexcept :
                type(type),
                bLeftIsPressed(parent.bLeftIsPressed),
                bRightIsPressed(parent.bRightIsPressed),
                x(parent.x),
                y(parent.y)
            {}

            Type GetType() const noexcept { return type; }
            std::pair<int, int> GetPos() const noexcept { return{x, y}; }
            int GetPosX() const noexcept { return x; }
            int GetPosY() const noexcept { return y; }
            bool LeftIsPressed() const noexcept { return bLeftIsPressed; }
            bool RightIsPressed() const noexcept { return bRightIsPressed; }
        };

    public:
        virtual int Initialize() noexcept;
        virtual void Finalize() noexcept;


        std::pair<int, int> GetPos() const noexcept;
        int GetPosX() const noexcept;
        int GetPosY() const noexcept;
        bool IsInWindow() const noexcept;
        bool LeftIsPressed() const noexcept;
        bool RightIsPressed() const noexcept;
        std::optional<MouseManager::MouseEvent> Read() noexcept;
        bool IsEmpty() const noexcept { return buffer.empty(); }
        void Flush() noexcept;

    private:
        void OnMouseMove(int newX, int newY) noexcept;
        void OnMouseLeave() noexcept;
        void OnMouseEnter() noexcept;
        void OnLeftPressed(int newX, int newY) noexcept;
        void OnLeftReleased(int newX, int newY) noexcept;
        void OnRightPressed(int newX, int newY) noexcept;
        void OnRightReleased(int newX, int newY) noexcept;
        void OnWheelUp(int newX, int newY) noexcept;
        void OnWheelDown(int newX, int newY) noexcept;
        void TrimBuffer() noexcept;
        void OnWheelDelta(int newX, int newY, int delta) noexcept;

    private:
        static constexpr unsigned int bufferSize = 16u;
        int x = 0;
        int y = 0;
        bool bLeftIsPressed = false;
        bool bRightIsPressed = false;
        bool bIsInWindow = false;
        int wheelDeltaCarry = 0;
        std::queue<MouseEvent> buffer;
    };
}
