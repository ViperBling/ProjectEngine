#pragma once

namespace ProjectEngine
{
    class RenderObject
    {
    public:
        virtual void Render();

        bool IsVisible() const { return mVisible; }
        void SetVisible(bool visible) { mVisible = visible; }

    private:
        bool mVisible = false;
    };
}