#pragma once

#include <memory>
#include <vector>
#include <filesystem>

namespace Where
{

namespace HotKey
{

struct HotKeyEntry;

class HotKeyRepository
{
    HotKeyRepository(const HotKeyRepository&) = delete;
    HotKeyRepository& operator=(const HotKeyRepository&) = delete;
    HotKeyRepository(HotKeyRepository&&) = delete;
    HotKeyRepository& operator=(HotKeyRepository&&) = delete;
public:
    HotKeyRepository();
    ~HotKeyRepository() noexcept;

    bool registerHotKey(const HotKeyEntry& entry) noexcept;
    bool load(const std::filesystem::path& storage) noexcept;
    const std::vector<HotKeyEntry>& entries() const noexcept;

private:
    struct Impl;
    std::unique_ptr<Impl> _impl;
};

}

}
