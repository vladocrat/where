#include "BackendInfo.hpp"

#include <nlohmann/json.hpp>

namespace Where
{

nlohmann::json BackendInfo::toJson() const noexcept
{
    nlohmann::json json;
    json["name"] = name;
    json["dll"] = dllLocation;

    return json;
}

BackendInfo Where::BackendInfo::fromJson(const nlohmann::json& json) noexcept
{
    return {
        json["name"].template get<std::string>(),
        json["dll"].template get<std::string>()
    };
}

bool BackendInfo::operator<(const BackendInfo& other) const noexcept
{
    if (name != other.name) {
        return other.name < name;
    }

    return false;
}

}
