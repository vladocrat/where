#include "BackendLibrary.hpp"

#ifdef WIN32
#include <Windows.h>
#endif

#include "BackendInfo.hpp"
#include "Backend.hpp"


namespace Where
{

struct BackendLibrary::Impl
{
#ifdef WIN32
    HMODULE dll;
#endif

    CreateFunc createFunc;
    DestoryFunc destroyFunc;
};

BackendLibrary::BackendLibrary()
    : _impl{std::make_unique<Impl>()}
{

}

BackendLibrary::~BackendLibrary() noexcept
{
    if (!_impl->dll) {
        return;
    }

    FreeLibrary(_impl->dll);
}

BackendLibrary::BackendLibrary(BackendLibrary&& other)
    : _impl{std::move(other._impl)}
{
    if (_impl && _impl->dll) {
        other._impl = std::make_unique<Impl>();
        other._impl->dll = nullptr;
        other._impl->createFunc = nullptr;
        other._impl->destroyFunc = nullptr;
    }
}

BackendLibrary& BackendLibrary::operator=(BackendLibrary&& other)
{
    if (this == &other) {
        return *this;
    }

    _impl = std::move(other._impl);

    if (_impl && _impl->dll) {
        other._impl = std::make_unique<Impl>();
        other._impl->dll = nullptr;
        other._impl->createFunc = nullptr;
        other._impl->destroyFunc = nullptr;
    }

    return *this;
}

bool BackendLibrary::load(const BackendInfo& info) noexcept
{
#ifdef WIN32
    //! std::filesystem::path::c_str returns w_char_t* instead of c_char_t...
    _impl->dll = LoadLibraryA(info.dllLocation.string().c_str());

    if (!_impl->dll) {
        return false;
    }

    _impl->createFunc = reinterpret_cast<Backend*(*)()>(GetProcAddress(_impl->dll, "create_plugin"));
    _impl->destroyFunc = reinterpret_cast<void(*)(Backend*)>(GetProcAddress(_impl->dll, "destroy_plugin"));

    if (!_impl->createFunc || !_impl->destroyFunc) {
        FreeLibrary(_impl->dll);
        return false;
    }
#else
    return false;
#endif

    return true;
}

BackendLibrary::BackendPtr BackendLibrary::create() noexcept
{
    return std::move(BackendPtr(_impl->createFunc(), _impl->destroyFunc));
}

std::string BackendLibrary::error() const noexcept
{
#ifdef WIN32
    const auto errorCode = GetLastError();

    LPSTR messageBuffer = nullptr;
    size_t size = FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        errorCode,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPSTR)&messageBuffer,
        0, NULL
        );

    std::string message(messageBuffer, size);
    LocalFree(messageBuffer);
    return std::move(message);
#endif
}

}
