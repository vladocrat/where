#include "HotKeyHandler.hpp"

#include <Windows.h>

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
    HWND fakeWindow {nullptr};
    std::atomic_bool running {false};
};

HotKeyHandler::HotKeyHandler()
    : _impl{std::make_unique<Impl>()}
{
    WNDCLASSA wc { 0 };
    wc.lpfnWndProc = DefWindowProcA;
    wc.hInstance = GetModuleHandle(nullptr);
    wc.lpszClassName = "HotkeyWindow";
    RegisterClassA(&wc);

    _impl->fakeWindow = CreateWindowA("HotkeyWindow", "hidden",
                                      0, 0, 0, 0, 0, HWND_MESSAGE, nullptr,
                                      wc.hInstance, nullptr);
}

HotKeyHandler::~HotKeyHandler() noexcept
{
    _impl->running = false;

    if (!_impl->fakeWindow) {

    }

    for (const auto& [id, _] : _impl->repository) {
        UnregisterHotKey(_impl->fakeWindow, id);
    }

    DestroyWindow(_impl->fakeWindow);
}

void HotKeyHandler::start() noexcept
{
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

    const auto mode = static_cast<UINT>(entry.mode);
    return RegisterHotKey(_impl->fakeWindow, id, mode, entry.key);;
}

}

}
