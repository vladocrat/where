#pragma once

#include <memory>
#include <functional>

class Backend;

namespace Where
{

struct BackendInfo;

class BackendLibrary
{
    BackendLibrary(const BackendLibrary&) = delete;
    BackendLibrary& operator=(const BackendLibrary&) = delete;
    BackendLibrary(BackendLibrary&&) = delete;
    BackendLibrary& operator=(BackendLibrary&&) = delete;
public:
    using CreateFunc = std::function<Backend*()>;
    using DestoryFunc = std::function<void(Backend*)>;
    using BackendPtr = std::unique_ptr<Backend, DestoryFunc>;

    BackendLibrary();
    ~BackendLibrary() noexcept;

    bool load(const BackendInfo& info) noexcept;
    BackendPtr create() noexcept;

private:
    struct Impl;
    std::unique_ptr<Impl> _impl;
};

}
