#pragma once

namespace ProjectEngine
{
    template <typename T>
    class Singleton
    {
    public:
        static T* GetInstance() {
            if (nullptr == pInstance) {
                pInstance = new T();
            }
            return pInstance;
        }

    private:
        static T* pInstance;
    };

    template <typename T>
    T* Singleton<T>::pInstance = nullptr;
}
