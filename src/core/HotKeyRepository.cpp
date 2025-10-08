#include "HotKeyRepository.hpp"

#include <fstream>

#include <nlohmann/json.hpp>

#include "HotKeyEntry.hpp"

namespace Where
{

namespace HotKey
{

struct HotKeyRepository::Impl
{
    std::vector<HotKeyEntry> repository;
    std::filesystem::path storage;
};

HotKeyRepository::HotKeyRepository()
    : _impl{std::make_unique<Impl>()}
{

}

HotKeyRepository::~HotKeyRepository() noexcept
{

}

bool HotKeyRepository::registerHotKey(const HotKeyEntry& entry) noexcept
{
    std::ofstream file(_impl->storage, std::ios_base::app | std::ios_base::binary);

    if (!file.is_open()) {
        return false;
    }

    const auto json = entry.toJson();
    file << json;

    return {};
}

bool HotKeyRepository::load(const std::filesystem::path& storage) noexcept
{
    std::ifstream file(storage);

    if (!file.is_open()) {
        return false;
    }

    _impl->storage = storage;
    const auto json = nlohmann::json::parse(file);

    if (_impl->repository.empty()) {
        _impl->repository.reserve(10);
    }

    for (const auto& obj : json) {
        const auto entry = HotKeyEntry::fromJson(obj);
        _impl->repository.emplace_back(entry);
    }

    return true;
}

const std::vector<HotKeyEntry>& HotKeyRepository::entries() const noexcept
{
    return _impl->repository;
}

}

}
