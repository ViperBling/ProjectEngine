#pragma once

<<<<<<< HEAD
#include <string>

=======
>>>>>>> remotes/origin/Branch_Rebase
namespace ProjectEngine
{
    class RenderObject
    {
    public:
        virtual void Render();

<<<<<<< HEAD
    public:
        std::string GetName() { return mName; }
        void SetName(std::string& name) { mName = name; }

        bool IsVisible() { return mVisible; }
        void SetVisible(bool visible) { mVisible = visible; }

    private:
        std::string mName;
        bool mVisible;
=======
        bool IsVisible() const { return mVisible; }
        void SetVisible(bool visible) { mVisible = visible; }

    private:
        bool mVisible = false;
>>>>>>> remotes/origin/Branch_Rebase
    };
}