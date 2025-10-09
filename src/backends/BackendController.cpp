#include "BackendController.hpp"

#include "BackendEnumerator.hpp"
#include "BackendLibrary.hpp"
#include "BackendInstance.hpp"

namespace Where
{

struct BackendController::Impl
{
    std::vector<BackendInstance> backends;
    size_t currentIx {0};
};

BackendController::BackendController()
    : _impl{std::make_unique<Impl>()}
{
    loadBackends();
}

BackendController::~BackendController() noexcept
{

}

void BackendController::setCurrentBackend(const size_t ix) noexcept
{
    if (ix < _impl->backends.size()) {
        _impl->currentIx = ix;
    }
}

bool BackendController::loadBackends() noexcept
{
    if (!_impl->backends.empty()) {
        _impl->backends.clear();
    }

    const auto backends = BackendEnumerator::enumerate(std::filesystem::current_path() / "backends.json");

    if (!backends) {
        return false;
    }

    _impl->backends.reserve(backends->size());

    for (const auto& info : backends.value()) {
        BackendInstance instance;

        if (!instance.lib.load(info)) {
            continue;
        }

        instance.ptr = std::move(instance.lib.create());

        _impl->backends.emplace_back(std::move(instance));
    }

    return true;
}

size_t BackendController::backendsCount() const noexcept
{
    return _impl->backends.size();
}

std::optional<BackendController::Files> BackendController::search(const std::string& query) noexcept
{
    if (_impl->backends.empty() && !(_impl->currentIx > _impl->backends.size())) {
        return std::nullopt;
    }

    const auto searchResult = _impl->backends[_impl->currentIx].ptr->search(query);

    Files files;
    files.reserve(searchResult.size);

    for (size_t i = 0; i < searchResult.size; i++) {
        files.emplace_back(searchResult.files[i]);
    }

    return files;
}

}
