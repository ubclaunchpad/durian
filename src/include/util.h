#pragma once

namespace util {

    // Hack implementation of C++14 make_unique
    // See https://stackoverflow.com/a/24609331
    template<typename T, typename... Args>
    std::unique_ptr<T> make_unique(Args&&... args) {
        return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    }
    
}
