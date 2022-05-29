#include "Keyboard.h"

using namespace ProjectEngine;

int KeyboardManager::Initialize() noexcept {

    return 0;
}

void KeyboardManager::Finalize() noexcept {

}

bool KeyboardManager::KeyIsPressed(unsigned char keyCode) const noexcept {

    return keystates[keyCode];
}

std::optional<KeyboardManager::KeybaordEvent> KeyboardManager::ReadKey() noexcept {

    if (!keybuffer.empty()) {
        KeybaordEvent event = keybuffer.front();
        keybuffer.pop();
        return event;
    }
    return {};
}

bool KeyboardManager::KeyIsEmpty() const noexcept {

    return keybuffer.empty();
}

void KeyboardManager::FlushKey() noexcept {

    keybuffer = std::queue<KeybaordEvent>();
}

std::optional<char> KeyboardManager::ReadChar() noexcept {

    if (!charbuffer.empty()) {
        unsigned char charCode = charbuffer.front();
        charbuffer.pop();
        return charCode;
    }
    return {};
}

bool KeyboardManager::CharIsEmpty() const noexcept {

    return charbuffer.empty();
}

void ProjectEngine::KeyboardManager::FlushChar() noexcept {

    charbuffer = std::queue<char>();
}

void KeyboardManager::Flush() noexcept {

    FlushKey();
    FlushChar();
}

void KeyboardManager::EnableAutoRepeat() noexcept {

    bAutorepeatEnabled = true;
}

void KeyboardManager::DisableAutoRepeat() noexcept {

    bAutorepeatEnabled = false;
}

bool KeyboardManager::AutoRepeatIsEnabled() const noexcept {

    return bAutorepeatEnabled;
}

void KeyboardManager::OnKeyPressed(unsigned char keyCode) noexcept {

    keystates[keyCode] = true;
    keybuffer.push(KeybaordEvent(KeybaordEvent::Type::Press, keyCode));
    TrimBuffer(keybuffer);
}

void KeyboardManager::OnKeyReleased(unsigned char keyCode) noexcept {

    keystates[keyCode] = false;
    keybuffer.push(KeybaordEvent(KeybaordEvent::Type::Release, keyCode));
    TrimBuffer(keybuffer);
}

void KeyboardManager::OnChar(char character) noexcept {

    charbuffer.push(character);
    TrimBuffer(charbuffer);
}

void KeyboardManager::ClearState() noexcept {

    keystates.reset();
}

template<typename T>
void KeyboardManager::TrimBuffer(std::queue<T> &buffer) noexcept {

    while (buffer.size() > bufferSize) {
        buffer.pop();
    }
}