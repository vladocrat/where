#pragma once

#include <cstdint>

#include <nlohmann/json_fwd.hpp>

namespace Where
{

namespace HotKey
{

enum class Mode
{
    NONE = 0,
    ALT = 0x0001,
    CTRL = 0x0002,
    NO_REPEAT = 0x4000,
    SHIFT = 0x0004,
    WIN = 0x0008
};

enum class Action
{
    NONE = 0,
    SHOW_SEARCH_BAR
};

struct HotKeyEntry
{
    uint32_t key;
    Mode mode;
    Action action;

    nlohmann::json toJson() const noexcept;
    static HotKeyEntry fromJson(const nlohmann::json& json) noexcept;
};

}

}
