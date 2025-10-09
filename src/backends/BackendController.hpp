#pragma once

#include <memory>

#include "Backend.hpp"

namespace Where
{

struct BackendInfo;

class BackendController
{
    BackendController(const BackendController&) = delete;
    BackendController& operator=(const BackendController&) = delete;
    BackendController(BackendController&&) = delete;
    BackendController& operator=(BackendController&&) = delete;

public:
    BackendController();
    ~BackendController() noexcept;

    void setCurrentBackend(const size_t ix) noexcept;
    bool loadBackends() noexcept;
    size_t backendsCount() const noexcept;
    std::optional<Backend::SearchResult> search(const std::string&) noexcept;

private:
    struct Impl;
    std::unique_ptr<Impl> _impl;
};

}
