#pragma once

#include <string>
#include <filesystem>

class Backend
{
public:
    struct File
    {
        std::wstring fileName;
        std::filesystem::path fullFilePath;
    };

    struct SearchResult
    {
        size_t size;
        File* files;
    };

    virtual SearchResult search(const std::wstring&) = 0;
    virtual ~Backend() = default;
};

