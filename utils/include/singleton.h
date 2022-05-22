#ifndef SINGLETON_H
#define SINGLETON_H

#include <type_traits>


template<typename T>
class PublicSingleton
{
protected:
    PublicSingleton() {}

public:
    static T& getInstance() noexcept(std::is_nothrow_constructible<T>::value)
    {
        static T instance;
        return instance;
    }
    virtual ~PublicSingleton() noexcept {}
    PublicSingleton(const PublicSingleton&) = delete;
    PublicSingleton& operator=(const PublicSingleton&) = delete;
};

#endif //SINGLETON_H