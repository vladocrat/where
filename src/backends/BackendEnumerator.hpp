#pragma once

#include <vector>
#include <filesystem>
#include <optional>

namespace Where
{

struct BackendInfo;

class BackendEnumerator
{
public:
    using BackEnds = std::vector<BackendInfo>;

    static std::optional<BackEnds> enumerate(const std::filesystem::path& configurationFile) noexcept;
};

}
