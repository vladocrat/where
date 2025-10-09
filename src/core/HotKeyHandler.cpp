#include "HotKeyHandler.hpp"

#ifdef WIN32
#include <Windows.h>
#endif

#include <mutex>
#include <thread>

#include <QDebug>

namespace Where
{

namespace HotKey
{

struct HotKeyHandler::Impl
{
    std::mutex mutex;
    std::map<uint32_t, std::pair<HotKeyEntry, Handler>> repository;
    std::atomic_bool running {false};

#ifdef WIN32
    HWND fakeWindow {nullptr};
#else
    void* fakeWindow {nullptr};
#endif
};

HotKeyHandler::HotKeyHandler()
    : _impl{std::make_unique<Impl>()}
{
#ifdef WIN32
    WNDCLASSA wc { 0 };
    wc.lpfnWndProc = DefWindowProcA;
    wc.hInstance = GetModuleHandle(nullptr);
    wc.lpszClassName = "HotkeyWindow";
    RegisterClassA(&wc);

    _impl->fakeWindow = CreateWindowA("HotkeyWindow", "hidden",
                                      0, 0, 0, 0, 0, HWND_MESSAGE, nullptr,
                                      wc.hInstance, nullptr);
#endif
}

HotKeyHandler::~HotKeyHandler() noexcept
{
    _impl->running = false;
    if (!_impl->fakeWindow) {
        return;
    }

#ifdef WIN32
    for (const auto& [id, _] : _impl->repository) {
        UnregisterHotKey(_impl->fakeWindow, id);
    }

    DestroyWindow(_impl->fakeWindow);
#endif
}

void HotKeyHandler::start() noexcept
{
#ifdef WIN32
    _impl->running = true;

    MSG msg;
    while (_impl->running && GetMessage(&msg, nullptr, 0, 0)) {
        if (msg.message == WM_HOTKEY) {
            const auto id = msg.wParam;
            {
                std::unique_lock lock(_impl->mutex);
                const auto it = _impl->repository.find(id);
                if (it != std::end(_impl->repository)) {
                    it->second.second();
                }
            }
        }
    }
#endif
}

void HotKeyHandler::stop() noexcept
{
    _impl->running = false;
}

bool HotKeyHandler::setHandler(const HotKeyEntry& entry, Handler handler) noexcept
{
    if (!_impl->fakeWindow) {
        return false;
    }

    std::unique_lock lock(_impl->mutex);
    const auto id = _impl->repository.size();
    _impl->repository[id] = std::make_pair(entry, handler);

    const auto mode = static_cast<uint32_t>(entry.mode);

#ifdef WIN32
    return RegisterHotKey(_impl->fakeWindow, id, mode, entry.key);
#else
    return false;
#endif
}

}

}
