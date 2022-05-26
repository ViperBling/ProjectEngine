#pragma once

#include <string>

using namespace std;

namespace ProjectEngine
{
    class RenderObject
    {
    public:
        virtual void Render();

        bool IsVisible() const { return mVisible; }
        void SetVisible(bool visible) { mVisible = visible; }

        string GetName() { return mName; }
        void SetName(string&& name) { mName = name; }

    private:
        bool mVisible = false;
        string mName;
    };
}