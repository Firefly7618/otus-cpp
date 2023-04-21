#pragma once

#include "IWriter.h"

#include <memory>

class IObservable
{
public:

    virtual ~IObservable() = default;

    virtual void add_observer(const std::shared_ptr<IWriter>& obs) = 0;

private:

    virtual void notify_writer() = 0;
};