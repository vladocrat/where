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
    using Files = std::vector<Backend::File>;

    BackendController();
    ~BackendController() noexcept;

    void setCurrentBackend(const size_t ix) noexcept;
    bool loadBackends() noexcept;
    size_t backendsCount() const noexcept;
    std::optional<Files> search(const std::string&) noexcept;

private:
    struct Impl;
    std::unique_ptr<Impl> _impl;
};

}
