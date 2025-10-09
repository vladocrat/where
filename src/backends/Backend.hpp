#pragma once

#ifdef BUILDING_DLL
#  define API_EXPORT __declspec(dllexport)
#else
#  define API_EXPORT __declspec(dllimport)
#endif

class API_EXPORT Backend
{
public:
    Backend();
};

extern "C" API_EXPORT Backend* create_instance();
