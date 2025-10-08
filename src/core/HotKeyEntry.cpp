#include "HotKeyEntry.hpp"

#include <nlohmann/json.hpp>

namespace Where
{

namespace HotKey
{

nlohmann::json HotKeyEntry::toJson() const noexcept
{
    nlohmann::json json;
    json["key"] = key;
    // json["mode"] = mode;
    // json["action"] = action;

    return json;
}

HotKeyEntry HotKeyEntry::fromJson(const nlohmann::json& json) noexcept
{
    HotKeyEntry entry {
        json["key"].template get<uint32_t>(),
        //json["mode"].template get<Mode>(),
       // json["action"].template get<Action>()
    };

    return entry;
}

}

}
