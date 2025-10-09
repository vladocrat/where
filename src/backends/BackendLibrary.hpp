#pragma once

#include <memory>
#include <functional>
#include <string>

class Backend;

namespace Where
{

struct BackendInfo;

class BackendLibrary
{
    BackendLibrary(const BackendLibrary&) = delete;
    BackendLibrary& operator=(const BackendLibrary&) = delete;

public:
    using CreateFunc = std::function<Backend*()>;
    using DestoryFunc = std::function<void(Backend*)>;
    using BackendPtr = std::unique_ptr<Backend, DestoryFunc>;

    BackendLibrary();
    ~BackendLibrary() noexcept;
    BackendLibrary(BackendLibrary&&);
    BackendLibrary& operator=(BackendLibrary&&);

    bool load(const BackendInfo& info) noexcept;
    BackendPtr create() noexcept;
    std::string error() const noexcept;

private:
    struct Impl;
    std::unique_ptr<Impl> _impl;
};

}
