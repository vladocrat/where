#include "BackendEnumerator.hpp"

#include <fstream>

#include <nlohmann/json.hpp>

#include "BackendInfo.hpp"

namespace Where
{

std::optional<BackendEnumerator::BackEnds> BackendEnumerator::enumerate(const std::filesystem::path& configurationFile) noexcept
{
    std::ifstream file(configurationFile);

    if (!file.is_open()) {
        return std::nullopt;
    }

    const auto json = nlohmann::json::parse(file);

    BackEnds backends;
    backends.reserve(json.size());

    for (const auto& obj : json) {
        backends.emplace_back(BackendInfo::fromJson(obj));
    }

    return backends;
}

}
