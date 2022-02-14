#pragma once

#include <string>

namespace ProjectEngine
{
    class RenderObject
    {
    public:
        virtual void Render();

    public:
        std::string GetName() { return mName; }
        void SetName(std::string& name) { mName = name; }

        bool IsVisible() { return mVisible; }
        void SetVisible(bool visible) { mVisible = visible; }
    private:
        std::string mName;
        bool mVisible;
    };
}