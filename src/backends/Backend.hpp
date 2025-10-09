#pragma once

class Backend
{
public:
    virtual void executeTask() = 0;
    virtual ~Backend() = default;
};

