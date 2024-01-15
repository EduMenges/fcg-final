#pragma once

#include <memory>
#include <string_view>

template<typename T, size_t identifier = 0>
class Singleton {
public:
    Singleton(const Singleton &other) = delete;

    Singleton(Singleton &&other) = delete;

    static const T &Get() {
        return *instance_;
    }

    static T &GetMut() {
        return *instance_;
    }

protected:
    Singleton() = default;

    template<class ...Args>
    static void InitSingleton(Args &&... args) { instance_ = std::make_unique<T>(std::forward<Args>(args)...); }

private:
    static std::unique_ptr<T> instance_;
};