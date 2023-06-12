#pragma once

#include <string>

//using namespace std;

namespace ProjectEngine
{
    class RenderObject
    {
    public:
        virtual void Render();

        [[nodiscard]] bool IsVisible() const { return mVisible; }
        void SetVisible(bool visible) { mVisible = visible; }

        std::string GetName() { return mName; }
        void SetName(std::string&& name) { mName = name; }

    private:
        bool mVisible = false;
        std::string mName;
    };
}