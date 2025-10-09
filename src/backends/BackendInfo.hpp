#pragma once

#include <filesystem>

#include <nlohmann/json_fwd.hpp>

namespace Where
{

struct BackendInfo
{
    std::string name;
    std::filesystem::path dllLocation;

    nlohmann::json toJson() const noexcept;

    static BackendInfo fromJson(const nlohmann::json& json) noexcept;
};

}
