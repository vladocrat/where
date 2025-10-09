#pragma once

#include "BackendInfo.hpp"
#include "BackendLibrary.hpp"

namespace Where
{

struct BackendInstance
{
    BackendLibrary lib;
    BackendInfo info;
    BackendLibrary::BackendPtr ptr;
};

}
