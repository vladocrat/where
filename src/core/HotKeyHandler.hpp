#pragma once

#include <functional>

#include "HotKeyEntry.hpp"

namespace Where
{

namespace HotKey
{

struct HotKeyEvent
{
    Action action;
};

class HotKeyHandler
{
public:
    using Handler = std::function<void()>;

    HotKeyHandler();
    ~HotKeyHandler() noexcept;

    void start() noexcept;
    void stop() noexcept;
    bool setHandler(const HotKeyEntry& entry, Handler handler) noexcept;

private:
    struct Impl;
    std::unique_ptr<Impl> _impl;
};

}

}
