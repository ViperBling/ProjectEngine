#pragma once

#include <queue>
#include <bitset>
#include <optional>

#include "Framework/Interface/IModule.h"
//#include "Framework/Common/Application/WindowsApplication.h"

namespace ProjectEngine
{

    class KeyboardManager : public IModule
    {
        friend class WindowsApplication;

    public:
        class KeybaordEvent {
        public:
            enum class Type
            {
                Press,
                Release
            };
        private:
            Type type;
            unsigned char code;
        public:
            KeybaordEvent(Type type, unsigned char code) noexcept :
                type(type),
                code(code)
            {}
            bool IsPressed() const noexcept { return type == Type::Press; }
            bool IsRelease() const noexcept { return type == Type::Release; }
            unsigned char GetCode() const noexcept { return code; }
        };

    public:
        virtual int Initialize() noexcept;
        virtual void Finalize() noexcept;

        // Key event
        bool KeyIsPressed(unsigned char keyCode) const noexcept;
        std::optional<KeybaordEvent> ReadKey() noexcept;
        bool KeyIsEmpty() const noexcept;
        void FlushKey() noexcept;

        // char event;
        std::optional<char> ReadChar() noexcept;
        bool CharIsEmpty() const noexcept;
        void FlushChar() noexcept;
        void Flush() noexcept;

        // auto repeat control
        void EnableAutoRepeat() noexcept;
        void DisableAutoRepeat() noexcept;
        bool AutoRepeatIsEnabled() const noexcept;

    private:
        void OnKeyPressed(unsigned char keyCode) noexcept;
        void OnKeyReleased(unsigned char keyCode) noexcept;
        void OnChar(char character) noexcept;
        void ClearState() noexcept;

        template<typename T>
        static void TrimBuffer(std::queue<T>& buffer) noexcept;

    private:
        static constexpr unsigned int nKeys = 256u;
        static constexpr unsigned int bufferSize = 16u;
        bool bAutorepeatEnabled = false;
        std::bitset<nKeys> keystates;
        std::queue<KeybaordEvent> keybuffer;
        std::queue<char> charbuffer;

    };
}