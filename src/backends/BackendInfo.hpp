#pragma once

#include <filesystem>

#include <nlohmann/json_fwd.hpp>

namespace Where
{

struct BackendInfo
{
    std::filesystem::path dllLocation;
    std::string name;

    nlohmann::json toJson() const noexcept;

    static BackendInfo fromJson(const nlohmann::json& json) noexcept;
};

}
